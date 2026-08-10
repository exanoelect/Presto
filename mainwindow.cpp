#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontMetrics>
#include <QIcon>
#include <QShowEvent>
#include <QScreen>
#include <QWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getDisplayResolution(); //1920 x 1080

    //setGeometry(0, 0, widthScreen, heightScreen);

    setupRealtimeDataDemo(ui->plotmmgram);
    setupRealtimeDataDemoTs(ui->plottsgram);

    ui->plotmmgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plottsgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //setupPlot();

    timerClock = new QTimer(this);
    connect(timerClock, SIGNAL(timeout()), this, SLOT(slotTimerClock()));
    timerClock->start(1000);

    // Alur RX tanpa polling QTimer:
    // readyRead -> readData()/parsing -> serialDataParsed -> enqueueParsedData
    // -> queueDataAvailable -> processDataQueue() untuk plot, kalkulasi, logging, dan UI.
    connect(this, &MainWindow::serialDataParsed,this, &MainWindow::enqueueParsedData,Qt::DirectConnection);

    // Consumer queue dijadwalkan lewat event-loop Qt, bukan polling periodik.
    // Ini menjaga readData() tetap ringan walaupun plot/kalkulasi cukup berat.
    connect(this, &MainWindow::queueDataAvailable,this, &MainWindow::processDataQueue,Qt::QueuedConnection);

    timerStopWatch = new QTimer(this);
    connect(timerStopWatch, SIGNAL(timeout()), this, SLOT(updateStopwatch()));

    ui->sw->setCurrentIndex(0);

    //QRegExp rx("[0-9.,]+"); // hanya digit, titik, dan koma
    //QValidator *validator = new QRegExpValidator(rx, this);

    QDoubleValidator *validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setDecimals(6);   // maksimal 6 digit desimal
    validator->setBottom(0.0);   // minimal 0.0 (opsional)
    validator->setTop(1e9);      // maksimal 1 miliar (opsional)

    ui->labelTargetBebanVal->setValidator(validator);

    exePath = QCoreApplication::applicationDirPath();
    logDir = exePath + "/log";

    // Ensure folder exists
    if (!logDir.exists()) {
        QDir().mkpath(logDir.path());
    }

    setWidgetPosition();

    testRunning = false;
    setupPlotView = false;
    modeBegin();
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::setupPlotmm()
{
  // The following plot setup is taken from the sine demo:
  // add two new graphs and set their look:
  ui->plotmmgram->addGraph();
  ui->plotmmgram->graph(0)->setPen(QPen(Qt::yellow)); // line color blue for first graph
  ui->plotmmgram->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  ui->plotmmgram->addGraph();
  ui->plotmmgram->graph(1)->setPen(QPen(Qt::yellow)); // line color red for second graph

  // generate some points of data (y0 for first, y1 for second graph):
  //QVector<double> x(5000), y0(5000), y1(5000);
  //for (int i=0; i<5000; ++i)
  //{
  //  x[i] = i;
  //  y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
  //  y1[i] = qExp(-i/150.0); // exponential envelope
  //}
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  ui->plotmmgram->xAxis2->setVisible(true);
  ui->plotmmgram->xAxis2->setTickLabels(false);
  ui->plotmmgram->yAxis2->setVisible(true);
  ui->plotmmgram->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(ui->plotmmgram->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotmmgram->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->plotmmgram->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotmmgram->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  //ui->plotmmgram->graph(0)->setData(x, y0);
  //ui->plot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->plotmmgram->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  ui->plotmmgram->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  ui->plotmmgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  ui->plotmmgram->replot();      // Untuk memastikan plot di-render ulang
  ui->plotmmgram->update();      // Untuk memastikan UI di-refresh

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::setupPlotTs()
{
    // The following plot setup is taken from the sine demo:
    // add two new graphs and set their look:
    ui->plottsgram->addGraph();
    ui->plottsgram->graph(0)->setPen(QPen(Qt::yellow)); // line color blue for first graph
    ui->plottsgram->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->plottsgram->addGraph();
    ui->plottsgram->graph(1)->setPen(QPen(Qt::yellow)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    //QVector<double> x(5000), y0(5000), y1(5000);
    //for (int i=0; i<5000; ++i)
    //{
    //  x[i] = i;
    //  y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    //  y1[i] = qExp(-i/150.0); // exponential envelope
    //}
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plottsgram->xAxis2->setVisible(true);
    ui->plottsgram->xAxis2->setTickLabels(false);
    ui->plottsgram->yAxis2->setVisible(true);
    ui->plottsgram->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->plottsgram->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plottsgram->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plottsgram->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plottsgram->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    //ui->plottsgram->graph(0)->setData(x, y0);
    //ui->plot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plottsgram->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->plottsgram->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->plottsgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->plottsgram->replot();      // Untuk memastikan plot di-render ulang
    ui->plottsgram->update();      // Untuk memastikan UI di-refresh

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::testDraw()
{
    QVector<double> x, y;

    // Garis 1: dari (0, 0) ke (10, 20)
    x << 0 << 10;
    y << 0 << 20;

    // Garis 2: dari (10, 20) ke (20, 10)
    x << 10 << 20;
    y << 20 << 10;

    ui->plotmmgram->addGraph();
    ui->plotmmgram->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->plotmmgram->graph(0)->setData(x, y);
    ui->plotmmgram->rescaleAxes();
    ui->plotmmgram->replot();

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::appendLoadDisplacementPoint(double displacement, double mass)
{
    qDebug() << "in " << displacement << "-" << mass;

    if (!m_mmCurve) {
        m_mmCurve = new QCPCurve(
            ui->plotmmgram->xAxis,
            ui->plotmmgram->yAxis
        );

        m_mmCurve->setPen(QPen(QColor(40, 255, 255), 2));

        // Supaya satu titik pun langsung kelihatan
        m_mmCurve->setScatterStyle(
            QCPScatterStyle(QCPScatterStyle::ssCircle, 4)
        );

        m_mmCurve->data()->setAutoSqueeze(false);
    }

    // Abaikan hanya data yang benar-benar identik
    if (m_hasLastPlotPoint &&
        qFuzzyCompare(1.0 + m_lastPlotDisplacement,
                      1.0 + displacement) &&
        qFuzzyCompare(1.0 + m_lastPlotMass,
                      1.0 + mass))
    {
        return;
    }

    //--------------------------------------------------
    // Tambah data
    //--------------------------------------------------

    m_mmCurveSequence += 1.0;

    m_mmCurve->addData(
        m_mmCurveSequence,
        displacement,
        mass
    );

    //--------------------------------------------------
    // Sample pertama
    //--------------------------------------------------

    if (!m_hasLastPlotPoint)
    {
        const double yMargin = 1.0;

        // X SELALU dimulai dari 0
        // Minimal range awal = 0 ... 100 mm
        m_mmMaxX = qMax(100.0, displacement);

        ui->plotmmgram->xAxis->setRange(
            0.0,
            m_mmMaxX
        );

        ui->plotmmgram->yAxis->setRange(
            mass - yMargin,
            mass + yMargin
        );
    }

    m_lastPlotDisplacement = displacement;
    m_lastPlotMass = mass;
    m_hasLastPlotPoint = true;

    //--------------------------------------------------
    // Batasi jumlah point di RAM
    //--------------------------------------------------

    if (m_mmCurve->dataCount() > MAX_MM_PLOT_POINTS)
    {
        const double firstSequenceToKeep =
            m_mmCurveSequence
            - static_cast<double>(MAX_MM_PLOT_POINTS)
            + 1.0;

        m_mmCurve->data()->removeBefore(firstSequenceToKeep);
    }

    //--------------------------------------------------
    // Label axis
    //--------------------------------------------------

    ui->plotmmgram->xAxis->setLabel("Displacement (mm)");
    ui->plotmmgram->yAxis->setLabel("Load (kg)");

    //--------------------------------------------------
    // Perbesar axis hanya jika diperlukan
    //--------------------------------------------------

    QCPRange yRange = ui->plotmmgram->yAxis->range();

    bool rangeChanged = false;

    //--------------------------------------------------
    // X AXIS
    // Selalu mulai dari 0.
    // Upper range hanya boleh membesar.
    //--------------------------------------------------

    if (displacement > m_mmMaxX)
    {
        // Tambahkan margin 10% supaya titik tidak menempel
        // pada sisi kanan plot
        const double xMargin =
            qMax(0.5, m_mmMaxX * 0.1);

        m_mmMaxX = displacement + xMargin;

        ui->plotmmgram->xAxis->setRange(
            0.0,
            m_mmMaxX
        );
    }
    else
    {
        // Pastikan lower axis tetap 0
        QCPRange currentXRange =
            ui->plotmmgram->xAxis->range();

        if (currentXRange.lower < 0.0)
        {
            ui->plotmmgram->xAxis->setRange(
                0.0,
                m_mmMaxX
            );
        }
    }

    //--------------------------------------------------
    // Y AXIS
    //--------------------------------------------------

    const double yMargin =
        qMax(0.5, yRange.size() * 0.1);

    if (mass < yRange.lower)
    {
        yRange.lower = mass - yMargin;
        rangeChanged = true;
    }

    if (mass > yRange.upper)
    {
        yRange.upper = mass + yMargin;
        rangeChanged = true;
    }

    if (rangeChanged)
    {
        ui->plotmmgram->yAxis->setRange(yRange);
    }

    //--------------------------------------------------
    // Replot
    //--------------------------------------------------

    ui->plotmmgram->replot(
        QCustomPlot::rpQueuedReplot
    );
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::clearGraph()
{
    if (m_mmCurve)
        m_mmCurve->data()->clear();

    for (int i = 0; i < ui->plotmmgram->graphCount(); ++i) {
        ui->plotmmgram->graph(i)->data()->clear();
    }
    ui->plotmmgram->replot(QCustomPlot::rpQueuedReplot);

    for (int i = 0; i < ui->plottsgram->graphCount(); ++i) {
        ui->plottsgram->graph(i)->data()->clear();
    }
    ui->plottsgram->replot(QCustomPlot::rpQueuedReplot);

    m_mmCurveSequence = 0.0;
    m_hasLastPlotPoint = false;
    m_lastPlotDisplacement = 0.0;
    m_lastPlotMass = 0.0;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::loadCsvToPlot(const QString &fileName)
{


    //Entry data
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file";
        return;
    }

    QVector<double> x;
    QVector<double> massa;
    QVector<double> displacement;

    QTextStream in(&file);

    // Skip header
    if (!in.atEnd())
        in.readLine();

    int sample = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;

        QStringList cols = line.split(';');

        if (cols.size() != 3)
            continue;

        x.append(sample++);

        massa.append(cols[1].toDouble());
        displacement.append(cols[2].toDouble());
    }

    qDebug() << "end of file cuk";
    qDebug() << "Jumlah data =" << x.size();
    qDebug() << x.first() << x.last();
    qDebug() << massa.first() << massa.last();

    file.close();

    // Hapus data plot lama. QCPCurve real-time dipertahankan sebagai object,
    // tetapi datanya dikosongkan agar tidak menggandakan histori di RAM.
    if (m_mmCurve)
        m_mmCurve->data()->clear();
    ui->plottsgram->clearGraphs();
    ui->plotmmgram->clearGraphs();
    qDebug() << "end of file cuk";

    qDebug() << "plottsgram graphs =" << ui->plottsgram->graphCount();
    qDebug() << "plotmmgram graphs =" << ui->plotmmgram->graphCount();


    // x = displacement, y = Massa aka load
    ui->plottsgram->addGraph();
    ui->plottsgram->graph(0)->setPen(QPen(Qt::cyan,2));
    ui->plottsgram->graph(0)->setName("Load");
    ui->plottsgram->graph(0)->setData(displacement, massa);

    ui->plottsgram->xAxis->setLabel("Time (s)");
    ui->plottsgram->yAxis->setLabel("load (kg)");

    ui->plottsgram->xAxis->rescale();
    ui->plottsgram->yAxis->rescale();

    ui->plottsgram->replot();

    qDebug() << "321";

    // x = timestamps, y = massa aka load
    ui->plotmmgram->addGraph();
    ui->plotmmgram->graph(0)->setPen(QPen(Qt::yellow,2));
    ui->plotmmgram->graph(0)->setName("Displacement");
    ui->plotmmgram->graph(0)->setData(x, massa);

    qDebug() << "330";

    ui->plotmmgram->xAxis->setLabel("Displacement (mm)");
    ui->plotmmgram->yAxis->setLabel("Load (kg)");

    ui->plotmmgram->xAxis->rescale();
    ui->plotmmgram->yAxis->rescale();

    ui->plotmmgram->replot();
    qDebug() << "340";



}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::sendData(quint32 targetBeban,
                          quint8 perintahManual,
                          quint8 perintahAuto,
                          quint8 updateData)
{
    if (!m_serial || !m_serial->isOpen())
        return;

    QByteArray packet;
    packet.resize(10);

    packet[0] = char(0xCD);
    packet[1] = char(0xDE);

    // float -> int32 x1000
    qint32 target = qRound(targetBeban * 1000.0);

    // Big Endian
    packet[2] = char((target >> 24) & 0xFF);
    packet[3] = char((target >> 16) & 0xFF);
    packet[4] = char((target >> 8)  & 0xFF);
    packet[5] = char(target & 0xFF);

    packet[6] = char(perintahManual);
    packet[7] = char(perintahAuto);
    packet[8] = char(updateData);
    packet[9] = char(0x00);      // cadangan

    m_serial->write(packet);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::sendDataStruct(const MainWindow::DataTX &tx)
{
    if (!m_serial || !m_serial->isOpen())
         return;

     QByteArray packet(10, 0);

     packet[0] = char(0xCD);
     packet[1] = char(0xDE);

     qint32 target = qRound(tx.targetBeban * 1000.0f);

     packet[2] = char((target >> 24) & 0xFF);
     packet[3] = char((target >> 16) & 0xFF);
     packet[4] = char((target >> 8)  & 0xFF);
     packet[5] = char(target & 0xFF);

     packet[6] = char(tx.perintahManual);
     packet[7] = char(tx.perintahAuto);
     packet[8] = char(tx.updateData);
     packet[9] = 0x00;

     m_serial->write(packet);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::setPlotView()
{
    //Setup
    // create connection between axes and scroll bars:
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBar2Changed(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBar2Changed(int)));
    connect(ui->plotmmgram->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxis2Changed(QCPRange)));
    connect(ui->plotmmgram->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxis2Changed(QCPRange)));

    connect(ui->horizontalScrollBar2, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar2, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plottsgram->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plottsgram->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    // configure scroll bars:
    // Since scroll bars only support integer values, we'll set a high default range of -500..500 and
    // divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
    // axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
    // just increase the minimum/maximum values of the scroll bars as needed.
    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    ui->horizontalScrollBar2->setRange(-500, 500);
    ui->verticalScrollBar2->setRange(-500, 500);

     // initialize axis range (and scroll bar positions via signals we just connected):
    ui->plottsgram->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plottsgram->yAxis->setRange(0, 10, Qt::AlignCenter);

    ui->plotmmgram->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plotmmgram->yAxis->setRange(0, 10, Qt::AlignCenter);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::resetPlotView()
{
    // Reset Plot TS
    ui->plottsgram->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plottsgram->yAxis->setRange(0, 10, Qt::AlignCenter);
    ui->plottsgram->replot();

    // Reset Plot MM
    ui->plotmmgram->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plotmmgram->yAxis->setRange(0, 10, Qt::AlignCenter);
    ui->plotmmgram->replot();

    // Reset scrollbar range
    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    ui->horizontalScrollBar2->setRange(-500, 500);
    ui->verticalScrollBar2->setRange(-500, 500);

    // Reset posisi scrollbar ke tengah
    ui->horizontalScrollBar->setValue(0);
    ui->verticalScrollBar->setValue(0);

    ui->horizontalScrollBar2->setValue(0);
    ui->verticalScrollBar2->setValue(0);

    disconnect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)),
               this, SLOT(horzScrollBar2Changed(int)));
    disconnect(ui->verticalScrollBar, SIGNAL(valueChanged(int)),
               this, SLOT(vertScrollBar2Changed(int)));
    disconnect(ui->plotmmgram->xAxis, SIGNAL(rangeChanged(QCPRange)),
               this, SLOT(xAxis2Changed(QCPRange)));
    disconnect(ui->plotmmgram->yAxis, SIGNAL(rangeChanged(QCPRange)),
               this, SLOT(yAxis2Changed(QCPRange)));

    disconnect(ui->horizontalScrollBar2, SIGNAL(valueChanged(int)),
               this, SLOT(horzScrollBarChanged(int)));
    disconnect(ui->verticalScrollBar2, SIGNAL(valueChanged(int)),
               this, SLOT(vertScrollBarChanged(int)));
    disconnect(ui->plottsgram->xAxis, SIGNAL(rangeChanged(QCPRange)),
               this, SLOT(xAxisChanged(QCPRange)));
    disconnect(ui->plottsgram->yAxis, SIGNAL(rangeChanged(QCPRange)),
               this, SLOT(yAxisChanged(QCPRange)));
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeBegin()
{
    qDebug() << "mode begin";

    ui->btnPause->setVisible(false);
    ui->btnStart->setEnabled(false);
    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);
    ui->btnOpen->setEnabled(true);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);  //----->> cuma ini yg aktif dulu
    ui->btnRefreshSerialPort->setEnabled(true);  //----->> cuma ini yg aktif dulu

    ui->serialPortInfoListBox->setEnabled(true);

    ui->labelTargetBebanVal->setEnabled(true);   //----- untuk entry target beban
    ui->btnTargetBebanRefresh->setEnabled(false);
    ui->btnTera->setEnabled(false);
    ui->btnResetEncoder->setEnabled(false);

    ui->teNama->setEnabled(false);
    ui->btnAddNewMeasurement->setEnabled(true);  //---->> entry pengukuran baru

    ui->btnDown->setEnabled(false);
    ui->btnUp->setEnabled(false);
    ui->btnStop->setEnabled(false);

    ui->btnArrowLeftDL->setVisible(false);
    ui->btnArrowRight->setVisible(false);

    ui->verticalScrollBar->setVisible(false);
    ui->verticalScrollBar2->setVisible(false);
    ui->horizontalScrollBar->setVisible(false);
    ui->horizontalScrollBar2->setVisible(false);

    ui->btnExit->setEnabled(true);
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");

    clearGraph();
    m_dataQueue.clear();
    dataTerima = DataTerima{};
    m_rxBuffer.clear();
    ui->teNama->setText("");

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh4.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause4.png);""}");
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai4.png);""}");

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down4.png);""}");
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up4.png);""}");
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop5.png);""}");
    //ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add.png);""}");
    ui->btnSave->setStyleSheet("QPushButton {""border-image: url(:/save4.png);""}");
    ui->btnOpen->setStyleSheet("QPushButton {""border-image: url(:/open1.png);""}");

    ui->btnRefreshSerialPort->setStyleSheet("QPushButton {""border-image: url(:/refresh1.png);""}");

    ui->serialPortInfoListBox->clear();
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeLoadPort()
{
    qDebug() << "mode load";

    ui->btnPause->setVisible(false);
    ui->btnStart->setEnabled(false);
    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);  //----->> tetap aktif
    ui->serialPortInfoListBox->setEnabled(true); //----->> tetap aktif

    ui->labelTargetBebanVal->setEnabled(true);   //----- untuk entry target beban
    ui->btnTargetBebanRefresh->setEnabled(false);
    ui->btnTera->setEnabled(false);
    ui->btnResetEncoder->setEnabled(false);

    ui->teNama->setEnabled(true);                //----> entry nama file
    ui->btnAddNewMeasurement->setEnabled(true);  //generate nama file

    ui->btnDown->setEnabled(false);
    ui->btnUp->setEnabled(false);
    ui->btnStop->setEnabled(false);

    ui->btnArrowLeftDL->setVisible(false);
    ui->btnArrowRight->setVisible(false);

    ui->btnExit->setEnabled(true);

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh4.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause4.png);""}");
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai4.png);""}");

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down4.png);""}");
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up4.png);""}");
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop5.png);""}");
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add.png);""}");

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeStart()
{
    qDebug() << "mode start";

    ui->btnPause->setVisible(false);
    ui->btnStart->setEnabled(true);  //u/ start
    ui->btnStart->setVisible(true);   //u/ start
    ui->btnOpen->setEnabled(false);

    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true); //always enable
    ui->btnRefreshSerialPort->setEnabled(true); //always enable

    ui->serialPortInfoListBox->setEnabled(true); //always enable

    ui->labelTargetBebanVal->setEnabled(true);
    ui->btnTargetBebanRefresh->setEnabled(true);  //---->> untuk kirim target beban
    ui->btnTera->setEnabled(true);                //---->> untuk reset timbangan
    ui->btnResetEncoder->setEnabled(true);        //---->> untuk reset encoder

    ui->teNama->setEnabled(true);                 //---> utk entry file name
    ui->btnAddNewMeasurement->setEnabled(true);   //---> utk entry file name

    ui->btnDown->setEnabled(true);
    ui->btnUp->setEnabled(true);
    ui->btnStop->setEnabled(true);

    ui->btnArrowLeftDL->setVisible(false);
    ui->btnArrowRight->setVisible(false);

    ui->btnExit->setEnabled(true);

    clearGraph();
    m_dataQueue.clear();
    dataTerima = DataTerima{};
    m_rxBuffer.clear();

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh1.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause4.png);""}");
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai1.png);""}");   //--------------------

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");    //--------------------
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down1.png);""}");
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up1.png);""}");
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop3.png);""}");
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add.png);""}");
    ui->btnOpen->setStyleSheet("QPushButton {""border-image: url(:/open4.png);""}");
    ui->btnRefreshSerialPort->setStyleSheet("QPushButton {""border-image: url(:/refresh1.png);""}");

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeRunning()
{
    qDebug() << "mode running";

    ui->btnPause->setVisible(true);  //----> untuk menSTOP operasi
    ui->btnPause->setEnabled(true);  //----> untuk menSTOP operasi

    ui->btnStart->setEnabled(false);
    ui->btnStart->setVisible(false);

    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);
    ui->btnExit->setEnabled(false);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);
    ui->serialPortInfoListBox->setEnabled(false);

    ui->labelTargetBebanVal->setEnabled(false);
    ui->btnTargetBebanRefresh->setEnabled(false);
    ui->btnTera->setEnabled(false);    //-------------->> u/ meng-0-kan timbangan
    ui->btnResetEncoder->setEnabled(false); //----->> u/ reset encoder

    ui->teNama->setEnabled(false);
    ui->btnAddNewMeasurement->setEnabled(false);
    ui->btnExit->setEnabled(false);
    ui->btnOpen->setEnabled(false);

    ui->btnDown->setEnabled(false);  //--->>> kirim cmd down
    ui->btnUp->setEnabled(false);    //--->>> kirim cmd stop
    ui->btnStop->setEnabled(false);  //--->>> kirim cmd up

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh4.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause.png);""}");  //--------------------------
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai4.png);""}");   //--------------------

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");    //--------------------
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");  //--------------------
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down4.png);""}");
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up4.png);""}");
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop5.png);""}");
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit6.png);""}");
    ui->btnOpen->setStyleSheet("QPushButton {""border-image: url(:/open4.png);""}");


    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add4.png);""}");
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modePaused()
{
    qDebug() << "mode paused";

    ui->btnPause->setVisible(false);
    ui->btnPause->setEnabled(false);  //----> untuk menStart operasi

    ui->btnStart->setEnabled(false);
    ui->btnSelesai->setEnabled(true); //---->> untuk menyelesaikan operasi
    ui->btnResume->setVisible(true); //----> untuk menST operasi
    ui->btnResume->setEnabled(true); //----> untuk menStart operasi

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);
    ui->serialPortInfoListBox->setEnabled(false);

    ui->labelTargetBebanVal->setEnabled(true);   //---->> entry target beban
    ui->btnTargetBebanRefresh->setEnabled(true); //entry target beban
    ui->btnTera->setEnabled(true);               //-------------->> u/ meng-0-kan timbangan
    ui->btnResetEncoder->setEnabled(true);       //----->> u/ reset encoder

    ui->teNama->setEnabled(false);
    ui->btnAddNewMeasurement->setEnabled(false);

    ui->btnDown->setEnabled(true);  //--->>> kirim cmd down
    ui->btnUp->setEnabled(true);    //--->>> kirim cmd stop
    ui->btnStop->setEnabled(true);  //--->>> kirim cmd up
    ui->btnSelesai->setEnabled(true);
    ui->btnExit->setEnabled(true);
    //ui->btnExit->setEnabled(false);

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh1.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause4.png);""}");  //--------------------------
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai4.png);""}");   //--------------------
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai.png);""}");   //--------------------

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");    //--------------------
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");  //--------------------
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down1.png);""}");  //------------
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up1.png);""}"); //--------------
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop3.png);""}"); //---------------
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add4.png);""}");
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeResumed()
{
    qDebug() << "mode resumed";

    ui->btnPause->setVisible(true);
    ui->btnPause->setEnabled(true);  //----> untuk menSTOP operasi

    ui->btnStart->setEnabled(false);
    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);
    ui->btnResume->setEnabled(false);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);
    ui->serialPortInfoListBox->setEnabled(false);

    ui->labelTargetBebanVal->setEnabled(false);
    ui->btnTargetBebanRefresh->setEnabled(false);
    ui->btnTera->setEnabled(false);
    ui->btnResetEncoder->setEnabled(false);
    ui->btnExit->setEnabled(false);

    ui->teNama->setEnabled(false);
    ui->btnAddNewMeasurement->setEnabled(false);

    ui->btnDown->setEnabled(false);  //--->>> kirim cmd down
    ui->btnUp->setEnabled(false);    //--->>> kirim cmd stop
    ui->btnStop->setEnabled(false);  //--->>> kirim cmd up

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh4.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause.png);""}");  //--------------------------
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai4.png);""}");   //--------------------

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");    //--------------------
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");  //--------------------
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down4.png);""}");  //------------
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up4.png);""}"); //--------------
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop5.png);""}"); //---------------
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit6.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add4.png);""}");

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::modeEnd()
{
    qDebug() << "mode end";

    ui->btnPause->setVisible(false);
    ui->btnPause->setEnabled(false);

    ui->btnStart->setEnabled(true);
    ui->btnStart->setVisible(true);

    ui->btnSelesai->setEnabled(false);
    ui->btnResume->setVisible(false);
    ui->btnResume->setEnabled(false);

    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);  //--->> refresh port
    ui->serialPortInfoListBox->setEnabled(true); //--->> untuk memilih port

    ui->labelTargetBebanVal->setEnabled(false);
    ui->btnTargetBebanRefresh->setEnabled(true);
    ui->btnTera->setEnabled(true);
    ui->btnResetEncoder->setEnabled(true);

    ui->teNama->setEnabled(true);
    ui->btnAddNewMeasurement->setEnabled(true);

    ui->btnDown->setEnabled(true);
    ui->btnUp->setEnabled(true);
    ui->btnStop->setEnabled(true);

    ui->btnExit->setEnabled(true);
    ui->btnOpen->setEnabled(true);
    ui->btnSave->setEnabled(true);

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh1.png);""}");
    ui->btnPause->setStyleSheet("QPushButton {""border-image: url(:/pause4.png);""}");  //--------------------------
    ui->btnSelesai->setStyleSheet("QPushButton {""border-image: url(:/selesai4.png);""}");
    ui->btnResume->setStyleSheet("QPushButton {""border-image: url(:/resume4.png);""}");
    ui->btnStart->setStyleSheet("QPushButton {""border-image: url(:/mulai1.png);""}");   //--------------------

    ui->btnTera->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");    //--------------------
    ui->btnResetEncoder->setStyleSheet("QPushButton {""border-image: url(:/zero1.png);""}");  //--------------------
    //ui->teNama->setStyleSheet("QPushButton {""border-image: url(:/zero4.png);""}");
    ui->btnDown->setStyleSheet("QPushButton {""border-image: url(:/down1.png);""}");  //------------
    ui->btnUp->setStyleSheet("QPushButton {""border-image: url(:/up1.png);""}"); //--------------
    ui->btnStop->setStyleSheet("QPushButton {""border-image: url(:/stop3.png);""}"); //---------------
    ui->btnExit->setStyleSheet("QPushButton {""border-image: url(:/exit4.png);""}");
    ui->btnSave->setStyleSheet("QPushButton {""border-image: url(:/save1.png);""}");

    ui->btnAddNewMeasurement->setStyleSheet("QPushButton {""border-image: url(:/add.png);""}");
    ui->btnOpen->setStyleSheet("QPushButton {""border-image: url(:/open1.png);""}");
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::writeLog(const QString &text)
{
    // Path of executable
    //QString exePath = QCoreApplication::applicationDirPath();

    // Target folder: log2
    //QDir logDir(exePath + "/log");
    //logDir = exePath + "/log";

    // Ensure folder exists
    //if (!logDir.exists()) {
    //    QDir().mkpath(logDir.path());
    //}

    // Build log file path

    //Get current data time
    //QDateTime currentDateTime = QDateTime::currentDateTime();
    //QString strTanggal = currentDateTime.toString("dd");
    //QLocale indonesian(QLocale::Indonesian);
    //QString dayName = indonesian.toString(currentDateTime,"dddd");
    //QString namaBulan = indonesian.toString(currentDateTime, "MMMM");
    //strTanggal.append(" ");
    //strTanggal.append(namaBulan);
    //strTanggal.append(" ");

    //strTanggal.append(currentDateTime.toString("yyyy"));
    //strTanggal.append(currentDateTime.toString("hhmmss"));

    //QString logFilePath = logDir.filePath(strTanggal + "_log.txt");

    QFile file(logFilePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file:" << logFilePath;
        return;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
        << ";" << text << "\n";
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::writeLog2(const QString &path, const QString &text)
{
    QFile file(path);  // bisa kasih absolute path kalau mau
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Gagal buka file log";
        return;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
        << " | " << text << "\n";
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::getDisplayResolution()
{
    QDesktopWidget *desktop = QApplication::desktop();

    // Get primary screen resolution
    QRect primaryScreen =desktop->screenGeometry();
    widthScreen = primaryScreen.width();
    heightScreen = primaryScreen.height();

    qDebug() << "Primary screen resolution:" << widthScreen << "x" << heightScreen;

    // Get number of screens
    /*
    int screenCount = desktop->screenCount();
    qDebug() << "Number of screens:" << screenCount;

    // Get all screens resolution
    for (int i = 0; i < screenCount; ++i) {
        QRect screenGeometry = desktop->screenGeometry(i);
        qDebug() << "Screen" << i << ":" << screenGeometry.width() << "x" << screenGeometry.height();

        // Available geometry (excluding taskbars/docks)
        QRect availableGeometry = desktop->availableGeometry(i);
        qDebug() << "Available area:" << availableGeometry.width() << "x" << availableGeometry.height();
    }
    */
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::fillPortsInfo()
{
    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName();
             //<< (!description.isEmpty() ? description : blankString)
             //<< (!manufacturer.isEmpty() ? manufacturer : blankString)
             //<< (!serialNumber.isEmpty() ? serialNumber : blankString)
             //<< info.systemLocation()
             //<< (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             //<< (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

    ui->serialPortInfoListBox->addItem(tr("Custom"));
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::setWidgetPosition()
{
    if (!m_uiReady || !ui->centralWidget)
        return;

    /*
     * PENTING:
     * Jangan gunakan widthScreen/heightScreen untuk menata child widget.
     * Gunakan ukuran centralWidget yang BENAR-BENAR tersedia saat ini.
     * Dengan demikian layout ikut berubah saat window di-maximize, restore,
     * pindah monitor, atau resolusi desktop berubah.
     */
    const QRect area = ui->centralWidget->contentsRect();
    const int W = area.width();
    const int H = area.height();

    if (W < 640 || H < 480)
        return;

    // Skala hanya dipakai untuk margin/spacing kecil.
    // Qt sendiri sudah bekerja dalam device-independent pixel.
    const qreal scale = qBound<qreal>(0.65,
                                     qMin(W / 1920.0, H / 1040.0),
                                     1.50);

    const int margin = qMax(6, qRound(10 * scale));
    const int gap    = qMax(6, qRound(10 * scale));

    // -------------------------------------------------------------------------
    // 1. HEADER
    // -------------------------------------------------------------------------
    const int headerH = qBound(78, qRound(H * 0.115), 135);

    ui->frame0->setGeometry(margin,
                            0,
                            W - 2 * margin,
                            headerH);

    const int headPad = qMax(5, qRound(10 * scale));
    const int buttonH = qMax(48, headerH - 2 * headPad);
    const int buttonW = buttonH; // icon button tetap proporsional

    ui->btnOpen->setGeometry(headPad,
                             headPad,
                             buttonW,
                             buttonH);

    ui->btnSave->setGeometry(ui->btnOpen->geometry().right() + gap,
                             headPad,
                             buttonW,
                             buttonH);

    // ---------------------------------------------------------------------
    // EXIT: gunakan centralWidget sebagai parent agar TIDAK pernah ter-clip
    // oleh frame0 pada resolusi kecil. Posisi visualnya tetap berada di
    // sudut kanan frame0.
    // ---------------------------------------------------------------------
    const int exitSize = qBound(38,
                                qRound(buttonH * 0.68),
                                qMin(68, buttonH));

    // Koordinat lokal di frame0 diperlukan untuk menghitung ruang tanggal/jam.
    const int exitXInFrame = ui->frame0->width() - headPad - exitSize;
    const int exitYInFrame = (headerH - exitSize) / 2;

    Q_UNUSED(exitYInFrame);

    // Geometry btnExit tidak lagi ditentukan dalam koordinat frame0.
    // positionExitButton() akan menguncinya langsung ke MainWindow setelah
    // seluruh geometry header selesai dihitung.

    // Blok tanggal/jam (child frame0) berhenti sebelum posisi lokal btnExit.
    const int clockBlockW = qBound(190,
                                   qRound(ui->frame0->width() * 0.20),
                                   360);
    const int clockX = qMax(ui->btnSave->geometry().right() + 2 * gap,
                            exitXInFrame - gap - clockBlockW);
    const int actualClockW = qMax(80, exitXInFrame - gap - clockX);
    const int dateH  = qMax(24, qRound((headerH - 2 * headPad) * 0.34));

    ui->labelCurrentDate->setGeometry(clockX,
                                      headPad,
                                      actualClockW,
                                      dateH);

    ui->labelCurrentClock->setGeometry(clockX,
                                       headPad + dateH,
                                       actualClockW,
                                       headerH - 2 * headPad - dateH);

    const int titleX = ui->btnSave->geometry().right() + gap;
    const int titleW = qMax(50, clockX - gap - titleX);

    ui->labelJudul->setGeometry(titleX,
                                0,
                                titleW,
                                headerH);

    // -------------------------------------------------------------------------
    // 2. EMPAT PANEL RINGKAS DI BARIS ATAS
    // -------------------------------------------------------------------------
    const int summaryY = ui->frame0->geometry().bottom() + gap;
    const int summaryH = qBound(120, qRound(H * 0.185), 210);

    const int usableW = W - 2 * margin - 3 * gap;
    const int colW = usableW / 4;
    const int colWLast = usableW - (3 * colW);

    ui->frameLeft1->setGeometry(margin,
                                summaryY,
                                colW,
                                summaryH);

    ui->frameLeft2->setGeometry(margin + colW + gap,
                                summaryY,
                                colW,
                                summaryH);

    ui->frameLeft3->setGeometry(margin + 2 * (colW + gap),
                                summaryY,
                                colW,
                                summaryH);

    ui->frameLeft4->setGeometry(margin + 3 * (colW + gap),
                                summaryY,
                                colWLast,
                                summaryH);

    // Helper untuk isi panel 1..4.
    auto layoutSummaryPanel = [scale](QWidget *frame,
                                      QWidget *title,
                                      QWidget *value,
                                      QWidget *button)
    {
        const int fw = frame->width();
        const int fh = frame->height();
        const int p  = qMax(5, qRound(10 * scale));
        const int titleH = qRound(fh * 0.34);

        title->setGeometry(0, 0, fw, titleH);

        const int valueY = titleH;
        const int valueH = fh - titleH - p;

        if (button) {
            const int buttonW = qBound(56,
                                       qRound(fw * 0.26),
                                       qMax(56, fw / 3));
            const int buttonX = fw - p - buttonW;

            value->setGeometry(p,
                               valueY,
                               qMax(40, buttonX - 2 * p),
                               valueH);

            button->setGeometry(buttonX,
                                valueY,
                                buttonW,
                                valueH);
        } else {
            value->setGeometry(p,
                               valueY,
                               qMax(40, fw - 2 * p),
                               valueH);
        }
    };

    layoutSummaryPanel(ui->frameLeft1,
                       ui->labelTargetBebanKG,
                       ui->labelTargetBebanVal,
                       ui->btnTargetBebanRefresh);

    layoutSummaryPanel(ui->frameLeft2,
                       ui->labelLoadKg,
                       ui->labelLoadValue,
                       ui->btnTera);

    layoutSummaryPanel(ui->frameLeft3,
                       ui->labelDisplacementmm,
                       ui->labelDisplacementValue,
                       ui->btnResetEncoder);

    layoutSummaryPanel(ui->frameLeft4,
                       ui->labelWaktuClock,
                       ui->labelStopWatch,
                       nullptr);

    // -------------------------------------------------------------------------
    // 3. AREA BAWAH: 3/4 KIRI UNTUK GRAFIK, 1/4 KANAN UNTUK KONTROL
    // -------------------------------------------------------------------------
    const int bodyY = summaryY + summaryH + gap;
    const int bodyH = qMax(180, H - bodyY - margin);

    const int leftW = 3 * colW + 2 * gap;
    const int rightX = ui->frameLeft4->x();
    const int rightW = ui->frameLeft4->width();

    // Panel kontrol kanan memenuhi sisa tinggi layar.
    ui->frameLeft5->setGeometry(rightX,
                                bodyY,
                                rightW,
                                bodyH);

    // Di kiri: stacked graph + log serial di bawahnya.
    const int logH = qBound(42,
                            qRound(bodyH * 0.095),
                            90);
    const int stackH = qMax(120, bodyH - logH - gap);

    ui->sw->setGeometry(margin,
                        bodyY,
                        leftW,
                        stackH);

    // Penting untuk QStackedWidget: page yang tidak aktif kadang masih membawa
    // geometry lama dari Designer sampai event layout berikutnya. Sinkronkan
    // kedua page ke ukuran content SW sekarang agar plot tidak tertahan di
    // ukuran desain awal (mis. 1360x540).
    const QSize stackPageSize = ui->sw->contentsRect().size();
    ui->page->setMinimumSize(0, 0);
    ui->page_4->setMinimumSize(0, 0);
    ui->page->resize(stackPageSize);
    ui->page_4->resize(stackPageSize);

    ui->logSerialTextEdit->setGeometry(margin,
                                       bodyY + stackH + gap,
                                       leftW,
                                       logH);

    // -------------------------------------------------------------------------
    // 4. ISI PANEL KONTROL KANAN (frameLeft5)
    //    Semua posisi sekarang dihitung dari ukuran parent, bukan pixel desain.
    // -------------------------------------------------------------------------
    {
        const int fw = ui->frameLeft5->width();
        const int fh = ui->frameLeft5->height();
        const int p  = qMax(5, qRound(10 * scale));
        const int g  = qMax(5, qRound(9 * scale));

        // Bagi tinggi berdasarkan bobot desain asli. Total bobot = 88.
        // Cara ini menjamin seluruh kelompok SELALU muat di frameLeft5,
        // bahkan pada resolusi yang lebih rendah.
        const int contentH = qMax(60, fh - 2 * p - 5 * g);
        const int nameH    = qMax(1, qRound(contentH * 18.0 / 88.0));
        const int manualH  = qMax(1, qRound(contentH * 27.0 / 88.0));
        const int limitH   = qMax(1, qRound(contentH *  9.0 / 88.0));
        const int actionH  = qMax(1, qRound(contentH * 13.0 / 88.0));
        const int serialH  = qMax(1, contentH - nameH - manualH
                                             - 2 * limitH - actionH);

        int y = p;

        // Nama pengukuran
        ui->frameLeft_7->setGeometry(p, y, fw - 2 * p, nameH);
        ui->labelNama->setGeometry(0,
                                   0,
                                   ui->frameLeft_7->width(),
                                   qRound(nameH * 0.30));

        const int editY = ui->labelNama->height() + qMax(3, g / 2);
        const int addW  = qBound(44,
                                 qRound(ui->frameLeft_7->width() * 0.16),
                                 82);
        ui->btnAddNewMeasurement->setGeometry(ui->frameLeft_7->width() - addW,
                                               editY,
                                               addW,
                                               nameH - editY);
        ui->teNama->setGeometry(0,
                                editY,
                                ui->btnAddNewMeasurement->x() - g,
                                nameH - editY);

        y += nameH + g;

        // Manual movement
        ui->frameLeft_5->setGeometry(p, y, fw - 2 * p, manualH);

        const int manualW = ui->frameLeft_5->width();
        const int manualTitleH = qRound(manualH * 0.24);
        const int sideW = qMax(24, qRound(manualW * 0.21));
        const int stopW = qMax(36, qRound(manualW * 0.32));
        const int btnY = manualTitleH;
        const int btnH = manualH - manualTitleH;

        ui->labelLoadStr_8->setGeometry(0, 0, sideW, manualTitleH);
        ui->labelLoadStr_9->setGeometry(manualW - sideW, 0, sideW, manualTitleH);
        ui->labelLoadStr_4->setGeometry((manualW - stopW) / 2,
                                        0,
                                        stopW,
                                        manualTitleH);

        ui->btnDown->setGeometry(0, btnY, sideW, btnH);
        ui->btnStop->setGeometry((manualW - stopW) / 2, btnY, stopW, btnH);
        ui->btnUp->setGeometry(manualW - sideW, btnY, sideW, btnH);

        y += manualH + g;

        // Batas atas / bawah
        ui->labelBatasAtas->setGeometry(p, y, fw - 2 * p, limitH);
        y += limitH + g;
        ui->labelBatasBawah->setGeometry(p, y, fw - 2 * p, limitH);
        y += limitH + g;

        // Start/Pause/Resume + Selesai
        const int actionY = y;
        const int halfW = (fw - 2 * p - g) / 2;

        ui->btnStart->setGeometry(p, actionY, halfW, actionH);
        ui->btnPause->setGeometry(p, actionY, halfW, actionH);
        ui->btnResume->setGeometry(p, actionY, halfW, actionH);
        ui->btnSelesai->setGeometry(p + halfW + g,
                                    actionY,
                                    fw - (p + halfW + g) - p,
                                    actionH);

        y += actionH + g;
        const int serialY = y;

        // Serial port selector + refresh
        const int refreshW = qMax(34,
                                  qRound((fw - 2 * p) * 0.24));
        ui->btnRefreshSerialPort->setGeometry(fw - p - refreshW,
                                              serialY,
                                              refreshW,
                                              serialH);
        ui->serialPortInfoListBox->setGeometry(p,
                                               serialY,
                                               ui->btnRefreshSerialPort->x() - p - g,
                                               serialH);

        // Tombol test tidak dipakai pada mode normal; tetap beri posisi aman.
        ui->btnTest->setGeometry(qMax(p, fw - p - refreshW - 45),
                                 qMax(p, serialY - 45),
                                 40,
                                 40);
    }

    // -------------------------------------------------------------------------
    // 5. ISI KEDUA PAGE GRAFIK DI QStackedWidget
    // -------------------------------------------------------------------------
    auto layoutPlotPage = [this, scale](QWidget *page,
                                  QCustomPlot *plot,
                                  QLabel *head,
                                  QLabel *unitLabel,
                                  QPushButton *clearButton,
                                  QPushButton *leftButton,
                                  QPushButton *rightButton,
                                  QScrollBar *hScroll,
                                  QScrollBar *vScroll)
    {
        if (!page || !plot)
            return;

        /*
         * JANGAN membaca page->contentsRect() sebagai sumber utama di sini.
         * Tepat setelah sw di-resize, QStackedWidget dapat belum sempat
         * meng-update geometry page (terutama page yang hidden). Akibatnya
         * plot tetap memakai ukuran lama dari file .ui.
         *
         * Sumber ukuran yang benar adalah sw->contentsRect(). Karena child
         * plot memakai koordinat lokal page, origin dibuat (0,0).
         */
        const QSize swSize = ui->sw->contentsRect().size();
        const QRect r(0, 0, swSize.width(), swSize.height());

        // Pastikan page memiliki ukuran yang sama dengan area SW.
        page->resize(swSize);

        const int pw = r.width();
        const int ph = r.height();

        if (pw <= 0 || ph <= 0)
            return;

        const int p = qMax(4, qRound(7 * scale));
        const int g = qMax(3, qRound(5 * scale));

        // Header/footer dibuat tipis supaya area plot semaksimal mungkin.
        const int topH = qBound(28, qRound(ph * 0.055), 42);
        const int footerH = qBound(28, qRound(ph * 0.055), 42);
        const int navW = qBound(38, qRound(pw * 0.045), 68);

        // -----------------------------------------------------------------
        // Header: tombol navigasi + judul grafik
        // -----------------------------------------------------------------
        const int navH = qMax(24, topH - 2 * g);
        const int navY = r.y() + (topH - navH) / 2;

        leftButton->setGeometry(r.x() + p,
                                navY,
                                navW,
                                navH);

        rightButton->setGeometry(r.right() - p - navW + 1,
                                 navY,
                                 navW,
                                 navH);

        const int headX = leftButton->geometry().right() + g;
        const int headRight = rightButton->x() - g;
        head->setGeometry(headX,
                          r.y(),
                          qMax(20, headRight - headX),
                          topH);

        // -----------------------------------------------------------------
        // Scrollbar hanya memakan tempat jika memang TIDAK di-hide.
        // Pada mode normal scrollbar di-hide, jadi plot benar-benar melebar.
        // isHidden() dipakai (bukan isVisible()) agar page yang sedang tidak
        // aktif di QStackedWidget tidak salah dianggap scrollbar tersembunyi.
        // -----------------------------------------------------------------
        const bool useHScroll = hScroll && !hScroll->isHidden();
        const bool useVScroll = vScroll && !vScroll->isHidden();
        const int scrollSize = qBound(15, qRound(19 * scale), 22);
        const int reserveH = useHScroll ? (scrollSize + g) : 0;
        const int reserveV = useVScroll ? (scrollSize + g) : 0;

        const int plotX = r.x() + p;
        const int plotY = r.y() + topH + g;
        const int plotRight = r.right() - p - reserveV;
        const int plotBottom = r.bottom() - footerH - g - reserveH;

        const int plotW = qMax(1, plotRight - plotX + 1);
        const int plotH = qMax(1, plotBottom - plotY + 1);

        // QCustomPlot fit ke seluruh area isi page/sw yang tersisa.
        plot->setMinimumSize(0, 0);
        plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        plot->setGeometry(plotX, plotY, plotW, plotH);

        // Pastikan axis rect ikut memanfaatkan ukuran QCustomPlot.
        plot->axisRect()->setAutoMargins(QCP::msAll);
        plot->updateGeometry();

        // -----------------------------------------------------------------
        // Scrollbar mengikuti sisi plot bila suatu saat diaktifkan kembali.
        // -----------------------------------------------------------------
        if (hScroll) {
            if (useHScroll) {
                hScroll->setGeometry(plotX,
                                     plot->geometry().bottom() + g,
                                     plotW,
                                     scrollSize);
            } else {
                hScroll->setGeometry(0, 0, 0, 0);
            }
        }

        if (vScroll) {
            if (useVScroll) {
                vScroll->setGeometry(plot->geometry().right() + g,
                                     plotY,
                                     scrollSize,
                                     plotH);
            } else {
                vScroll->setGeometry(0, 0, 0, 0);
            }
        }

        // -----------------------------------------------------------------
        // Footer: Clear di kiri, satuan/keterangan di sisa lebar.
        // -----------------------------------------------------------------
        const int footerY = r.bottom() - footerH + 1;
        const int clearW = qBound(52, qRound(pw * 0.065), 90);

        clearButton->setGeometry(r.x() + p,
                                 footerY,
                                 clearW,
                                 qMax(24, footerH - p));

        const int unitX = clearButton->geometry().right() + g;
        unitLabel->setGeometry(unitX,
                               footerY,
                               qMax(20, r.right() - p - unitX + 1),
                               qMax(24, footerH - p));
    };

    layoutPlotPage(ui->page,
                   ui->plotmmgram,
                   ui->labelHeadmmGram,
                   ui->labelmm,
                   ui->btnClearGraphmmGram,
                   ui->btnArrowLeftDL,
                   ui->btnArrowRightDL,
                   ui->horizontalScrollBar2,
                   ui->verticalScrollBar2);

    layoutPlotPage(ui->page_4,
                   ui->plottsgram,
                   ui->labelHeadTsGram,
                   ui->labelts,
                   ui->btnClearGraphtsgram,
                   ui->btnArrowLeft,
                   ui->btnArrowRight,
                   ui->horizontalScrollBar,
                   ui->verticalScrollBar);

    // -------------------------------------------------------------------------
    // 6. ADAPTIVE FONT
    // -------------------------------------------------------------------------
    // Referensi desain utama = 1920x1080. Pada 1366x768 skala font menjadi
    // sekitar 0.71, lalu diperkecil lagi bila teks belum muat di widget.
    const qreal fontScale = qBound<qreal>(0.55,
                                          qMin(W / 1920.0, H / 1080.0),
                                          1.40);

    auto removeFixedFontCss = [](QWidget *w)
    {
        if (!w)
            return;

        QString css = w->styleSheet();
        if (css.isEmpty())
            return;

        // Font dari .ui (mis. font: 32pt / font-size: 36px) akan
        // mengalahkan QWidget::setFont(). Hapus hanya deklarasi font,
        // background/border/radius tetap dipertahankan.
        css.remove(QRegularExpression(
            R"((?i)\bfont(?:-size|-family|-weight|-style)?\s*:[^;}]*;?)"));
        w->setStyleSheet(css);
    };

    auto fitFont = [&](QWidget *w,
                       const QString &sampleText,
                       int basePx,
                       int minPx,
                       bool bold = false,
                       qreal widthUsage = 0.94,
                       qreal heightUsage = 0.88)
    {
        if (!w)
            return;

        removeFixedFontCss(w);

        const int maxPx = qMax(minPx, qRound(basePx * 1.40));
        int px = qBound(minPx, qRound(basePx * fontScale), maxPx);

        QFont f = w->font();
        f.setPixelSize(px);
        f.setBold(bold);

        const int maxW = qMax(1, qRound(w->contentsRect().width()  * widthUsage));
        const int maxH = qMax(1, qRound(w->contentsRect().height() * heightUsage));
        QString text = sampleText;
        if (text.isEmpty())
            text = QStringLiteral("0");

        // Fit-to-widget: jika teks masih overflow, turunkan pixel size
        // satu per satu sampai muat. Ini menangani teks panjang seperti
        // "Displacement (mm)" dan tanggal pada layar 1366x768.
        while (px > minPx) {
            QFontMetrics fm(f);
            const QRect br = fm.boundingRect(QRect(0, 0, maxW, maxH),
                                             Qt::AlignCenter | Qt::TextSingleLine,
                                             text);
            if (br.width() <= maxW && br.height() <= maxH)
                break;

            --px;
            f.setPixelSize(px);
        }

        w->setFont(f);
    };

    // Header
    fitFont(ui->labelJudul,       QStringLiteral("MESIN UJI TEKAN"), 64, 24, false);
    fitFont(ui->labelCurrentDate, ui->labelCurrentDate->text(),       30, 12, false, 0.98);
    fitFont(ui->labelCurrentClock,ui->labelCurrentClock->text(),      48, 16, false, 0.98);

    // Empat panel ringkas
    fitFont(ui->labelTargetBebanKG,  QStringLiteral("Target Beban (kg)"), 43, 15);
    fitFont(ui->labelLoadKg,         QStringLiteral("Load (kg)"),         43, 15);
    fitFont(ui->labelDisplacementmm, QStringLiteral("Displacement (mm)"), 43, 14);
    fitFont(ui->labelWaktuClock,     QStringLiteral("Waktu"),             43, 15);

    fitFont(ui->labelTargetBebanVal, ui->labelTargetBebanVal->text(), 64, 20, false, 0.90, 0.82);
    fitFont(ui->labelLoadValue,      ui->labelLoadValue->text(),      64, 20, false, 0.92, 0.82);
    fitFont(ui->labelDisplacementValue,
            ui->labelDisplacementValue->text(),                       64, 20, false, 0.92, 0.82);
    fitFont(ui->labelStopWatch,      QStringLiteral("00:00.00"),      64, 20, false, 0.94, 0.82);

    // Panel kanan
    fitFont(ui->labelNama,      QStringLiteral("NAMA PENGUJIAN"), 32, 12, false);
    fitFont(ui->teNama,         ui->teNama->toPlainText(),         32, 12, false, 0.95, 0.82);
    fitFont(ui->labelLoadStr_8, QStringLiteral("TURUN"),           24, 10, false);
    fitFont(ui->labelLoadStr_4, QStringLiteral("MANUAL"),          37, 11, false);
    fitFont(ui->labelLoadStr_9, QStringLiteral("NAIK"),            24, 10, false);
    fitFont(ui->labelBatasAtas,  QStringLiteral("BATAS ATAS"),     48, 14, true);
    fitFont(ui->labelBatasBawah, QStringLiteral("BATAS BAWAH"),    48, 14, true);
    fitFont(ui->serialPortInfoListBox,
            ui->serialPortInfoListBox->currentText().isEmpty()
                ? QStringLiteral("COM99")
                : ui->serialPortInfoListBox->currentText(),         48, 13, false, 0.90, 0.80);

    // Log dan judul/footer grafik
    fitFont(ui->logSerialTextEdit, ui->logSerialTextEdit->text(), 37, 11, false, 0.98, 0.85);
    fitFont(ui->labelHeadmmGram, QStringLiteral("Displacement (mm) vs Load (gram)"), 16, 9);
    fitFont(ui->labelHeadTsGram, QStringLiteral("timeStamps vs Gram"),                 16, 9);
    fitFont(ui->labelmm,         QStringLiteral("Displacement mm"),                    14, 8);
    fitFont(ui->labelts,         QStringLiteral("timestamps ms"),                      14, 8);

    // Font QCustomPlot tidak mengikuti QWidget stylesheet, jadi atur langsung.
    auto adaptPlotFont = [fontScale](QCustomPlot *plot)
    {
        if (!plot)
            return;

        const int tickPx  = qBound(8, qRound(14 * fontScale), 18);
        const int labelPx = qBound(9, qRound(16 * fontScale), 21);

        QFont tickFont = plot->xAxis->tickLabelFont();
        tickFont.setPixelSize(tickPx);
        plot->xAxis->setTickLabelFont(tickFont);
        plot->yAxis->setTickLabelFont(tickFont);

        QFont labelFont = plot->xAxis->labelFont();
        labelFont.setPixelSize(labelPx);
        plot->xAxis->setLabelFont(labelFont);
        plot->yAxis->setLabelFont(labelFont);

        plot->replot();
    };

    adaptPlotFont(ui->plotmmgram);
    adaptPlotFont(ui->plottsgram);

    // Terakhir: kunci tombol Exit ke area window yang BENAR-BENAR terlihat.
    positionExitButton();
}

//---------------------------------------------------------------------------------------
// btnExit overlay: tidak memakai widthScreen dan tidak bergantung pada parent frame0.
//---------------------------------------------------------------------------------------
void MainWindow::positionExitButton()
{
    if (!m_uiReady || !ui || !ui->btnExit || !ui->centralWidget)
        return;

    // btnExit adalah child centralWidget. Ambil area centralWidget yang benar-benar
    // berada pada monitor aktif. Ini tetap benar apabila MainWindow/Designer masih
    // membawa ukuran 1920x1080 sementara monitor hanya 1366x768.
    QRect visible = ui->centralWidget->rect();

    QScreen *screen = nullptr;
    if (windowHandle())
        screen = windowHandle()->screen();
    if (!screen)
        screen = QGuiApplication::primaryScreen();

    if (screen) {
        const QRect sg = screen->availableGeometry(); // global coordinates
        const QPoint tl = ui->centralWidget->mapFromGlobal(sg.topLeft());
        const QPoint br = ui->centralWidget->mapFromGlobal(sg.bottomRight());
        QRect screenInCentral(tl, br);
        screenInCentral = screenInCentral.normalized();
        visible = visible.intersected(screenInCentral);
    }

    // Fallback apabila mapping monitor belum valid saat startup.
    if (!visible.isValid() || visible.width() < 80 || visible.height() < 80)
        visible = ui->centralWidget->rect();

    const int frameH = qMax(1, ui->frame0->height());
    const qreal scale = qBound<qreal>(0.55,
                                     qMin(visible.width() / 1920.0,
                                          visible.height() / 1080.0),
                                     1.50);

    const int pad  = qMax(6, qRound(10 * scale));
    const int size = qBound(42, qRound(frameH * 0.58), 68);

    // Kunci ke pojok kanan area monitor yang TERLIHAT, bukan ke widthScreen
    // maupun lebar desain 1920 px.
    int x = visible.right() - pad - size + 1;

    // Secara vertikal tetap berada di tengah header.
    int y = ui->frame0->y() + (frameH - size) / 2;

    x = qBound(visible.left() + pad,
               x,
               qMax(visible.left() + pad, visible.right() - pad - size + 1));
    y = qBound(visible.top() + pad,
               y,
               qMax(visible.top() + pad, visible.bottom() - pad - size + 1));

    ui->btnExit->setMinimumSize(0, 0);
    ui->btnExit->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    ui->btnExit->setGeometry(x, y, size, size);

    // Tidak memakai border-image/resource sama sekali: selalu ada tombol merah X.
    ui->btnExit->setIcon(QIcon());
    ui->btnExit->setText(QStringLiteral("X"));

    QFont f = ui->btnExit->font();
    f.setBold(true);
    f.setPixelSize(qMax(18, qRound(size * 0.48)));
    ui->btnExit->setFont(f);

    const QString style = QStringLiteral(
        "QPushButton {"
        "background-color: #D71920;"
        "color: white;"
        "border: 3px solid white;"
        "border-radius: %1px;"
        "padding: 0px;"
        "}"
        "QPushButton:hover {"
        "background-color: #FF3038;"
        "}"
        "QPushButton:pressed {"
        "background-color: #9F1015;"
        "}"
        "QPushButton:disabled {"
        "background-color: #777777;"
        "color: #EEEEEE;"
        "border: 3px solid #DDDDDD;"
        "}"
    ).arg(size / 8);

    ui->btnExit->setStyleSheet(style);

    // Paksa tetap ada di atas semua sibling centralWidget.
    ui->btnExit->show();
    ui->btnExit->raise();

    qDebug() << "btnExit visible=" << ui->btnExit->isVisible()
             << "enabled=" << ui->btnExit->isEnabled()
             << "geometry=" << ui->btnExit->geometry()
             << "visibleArea=" << visible
             << "central=" << ui->centralWidget->rect();
}


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
bool MainWindow::parsePacket(const QByteArray &packet, DataTerima &parsedData) const
{
    static constexpr int PACKET_SIZE = 10;

    if (packet.size() != PACKET_SIZE)
        return false;

    const uchar *p = reinterpret_cast<const uchar*>(packet.constData());

    // Validasi header 0xED 0xDC.
    if (p[0] != 0xED || p[1] != 0xDC)
        return false;

    parsedData = DataTerima{};
    parsedData.rawPacket = packet;

    //------------------------------------
    // Beban Aktual (int32 Big Endian)
    //------------------------------------
    const quint32 bebanRaw =
            (quint32(p[2]) << 24) |
            (quint32(p[3]) << 16) |
            (quint32(p[4]) << 8 ) |
             quint32(p[5]);

    const qint32 bebanInt = static_cast<qint32>(bebanRaw);
    parsedData.bebanAktual = bebanInt / 1000.0f;

    //------------------------------------
    // Perpindahan (int16 Big Endian)
    //------------------------------------
    const quint16 perpRaw =
            (quint16(p[6]) << 8) |
             quint16(p[7]);

    const qint16 perpInt = static_cast<qint16>(perpRaw);
    parsedData.perpindahan = perpInt / 1000.0f;

    //------------------------------------
    // Limit Switch + Status Flag
    //------------------------------------
    parsedData.limitSwitch = p[8];
    unpackFlag(p[9], parsedData);

    return true;
}

void MainWindow::unpackFlag(quint8 flag, DataTerima &parsedData) const
{
    parsedData.motorStatus  = flag & (1 << 0);
    parsedData.limitAtas    = flag & (1 << 1);
    parsedData.limitBawah   = flag & (1 << 2);
    parsedData.zeroLoadcell = flag & (1 << 3);
    parsedData.zeroEncoder  = flag & (1 << 4);
    parsedData.updateData   = flag & (1 << 5);
    parsedData.autoFlag     = flag & (1 << 6);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::setupRealtimeDataDemo(QCustomPlot *plotmmgram)
{
    demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:

    plotmmgram->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    plotmmgram->xAxis->setTickLabelFont(font);
    plotmmgram->yAxis->setTickLabelFont(font);
    plotmmgram->legend->setFont(font);

    //plotmmgram->addGraph(); // blue line, Pressure
    //plotmmgram->graph(0)->setPen(QPen(QColor(250, 250, 250)));
    //plotmmgram->graph(0)->data()->setAutoSqueeze(false);

    // Load-displacement memakai QCPCurve, bukan QCPGraph.
    // QCPCurve menyimpan urutan akuisisi melalui parameter t sehingga kurva tetap
    // benar walaupun displacement berhenti, berulang, atau bergerak balik.
    m_mmCurve = new QCPCurve(plotmmgram->xAxis, plotmmgram->yAxis);
    m_mmCurve->setPen(QPen(QColor(255, 255, 0)));
    m_mmCurve->data()->setAutoSqueeze(false);
    m_mmCurve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,5));

    // Ubah warna latar belakang (background)
    plotmmgram->setBackground(QBrush(QColor(30, 30, 30))); // Dark grey

    // Ubah warna area plot (graph area)
    plotmmgram->axisRect()->setBackground(QBrush(QColor(45, 45, 45))); // Lebih gelap

    // Ubah warna garis sumbu dan teks
    QPen axisPen(QColor(250, 250, 250)); // Light grey
    QPen tickPen(QColor(250, 250, 250));
    QFont labelFont("Arial", 10);

    plotmmgram->xAxis->setBasePen(axisPen);
    plotmmgram->xAxis->setTickPen(tickPen);
    plotmmgram->xAxis->setSubTickPen(tickPen);
    plotmmgram->xAxis->setTickLabelColor(QColor(250, 250, 250));
    plotmmgram->xAxis->setLabelColor(QColor(250, 250, 250));
    plotmmgram->xAxis->setLabelFont(labelFont);

    plotmmgram->yAxis->setBasePen(axisPen);
    plotmmgram->yAxis->setTickPen(tickPen);
    plotmmgram->yAxis->setSubTickPen(tickPen);
    plotmmgram->yAxis->setTickLabelColor(QColor(250, 250, 250));
    plotmmgram->yAxis->setLabelColor(QColor(250, 250, 250));
    plotmmgram->yAxis->setLabelFont(labelFont);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    //plot->xAxis->setTicker(timeTicker);
    //double xMax = qMax(100.0, displacement);
    //ui->plotmmgram->xAxis->setRange(0, xMax);

    plotmmgram->xAxis->setRange(0, 100);//10000); //350);
    plotmmgram->axisRect()->setupFullAxesBox();
    //plot->yAxis->setRange(-1.0, 1.0);
    //plot->yAxis->setRange(-0.6, 1.0);
    plotmmgram->yAxis->setRange(0, ui->labelTargetBebanVal->text().toInt()); //10);
    //ui->plot->axisRect()->setupFullAxesBox(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(plotmmgram->xAxis, SIGNAL(rangeChanged(QCPRange)), plotmmgram->xAxis2, SLOT(setRange(QCPRange)));
    connect(plotmmgram->yAxis, SIGNAL(rangeChanged(QCPRange)), plotmmgram->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    //dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    //Vertical Text
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::setupRealtimeDataDemoTs(QCustomPlot *plottsgram)
{
    demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:

    plottsgram->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    plottsgram->xAxis->setTickLabelFont(font);
    plottsgram->yAxis->setTickLabelFont(font);
    plottsgram->legend->setFont(font);

    plottsgram->addGraph(); // blue line, Pressure
    plottsgram->graph(0)->setPen(QPen(QColor(40, 255, 255)));
    plottsgram->graph(0)->data()->setAutoSqueeze(false);

    // Ubah warna latar belakang (background)
    plottsgram->setBackground(QBrush(QColor(30, 30, 30))); // Dark grey

    // Ubah warna area plot (graph area)
    plottsgram->axisRect()->setBackground(QBrush(QColor(45, 45, 45))); // Lebih gelap

    // Ubah warna garis sumbu dan teks
    QPen axisPen(QColor(250, 250, 250)); // Light grey
    QPen tickPen(QColor(250, 250, 250));
    QFont labelFont("Arial", 10);

    plottsgram->xAxis->setBasePen(axisPen);
    plottsgram->xAxis->setTickPen(tickPen);
    plottsgram->xAxis->setSubTickPen(tickPen);
    plottsgram->xAxis->setTickLabelColor(QColor(250, 250, 250));
    plottsgram->xAxis->setLabelColor(QColor(250, 250, 250));
    plottsgram->xAxis->setLabelFont(labelFont);

    plottsgram->yAxis->setBasePen(axisPen);
    plottsgram->yAxis->setTickPen(tickPen);
    plottsgram->yAxis->setSubTickPen(tickPen);
    plottsgram->yAxis->setTickLabelColor(QColor(250, 250, 250));
    plottsgram->yAxis->setLabelColor(QColor(250, 250, 250));
    plottsgram->yAxis->setLabelFont(labelFont);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    //plot->xAxis->setTicker(timeTicker);
    plottsgram->xAxis->setRange(0, 10000); //350);
    plottsgram->axisRect()->setupFullAxesBox();
    //plot->yAxis->setRange(-1.0, 1.0);
    //plot->yAxis->setRange(-0.6, 1.0);
    plottsgram->yAxis->setRange(0, ui->labelTargetBebanVal->text().toInt()); //10);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(plottsgram->xAxis, SIGNAL(rangeChanged(QCPRange)), plottsgram->xAxis2, SLOT(setRange(QCPRange)));
    connect(plottsgram->yAxis, SIGNAL(rangeChanged(QCPRange)), plottsgram->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    //dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    //Vertical Text
}

//---------------------------------------------------------------------------------------
// Dipanggil otomatis setiap ukuran MainWindow berubah.
//---------------------------------------------------------------------------------------
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (!m_uiReady)
        return;

    // Pass pertama: resize SW dan seluruh frame segera.
    setWidgetPosition();

    // Pass kedua: setelah QStackedWidget selesai menyesuaikan geometry page.
    // Ini penting agar plot page aktif maupun hidden benar-benar mengikuti sw.
    QTimer::singleShot(0, this, [this](){
        if (m_uiReady)
            setWidgetPosition();
    });
}

//---------------------------------------------------------------------------------------
// Pastikan overlay diposisikan sekali lagi SETELAH window benar-benar tampil.
//---------------------------------------------------------------------------------------
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    if (!m_uiReady)
        return;

    setWidgetPosition();
    positionExitButton();

    QTimer::singleShot(0, this, [this](){
        if (m_uiReady) {
            setWidgetPosition();
            positionExitButton();
        }
    });
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
bool MainWindow::init_port()
{
    // Periksa apakah port sudah diinisialisasi dan terbuka
    if (m_serial && m_serial->isOpen()) {
        qDebug() << "Port already open.";
        return true;
    }

    // Jika sudah ada instance `m_serial`, hapus untuk mencegah kebocoran memori
    if (m_serial) {
        delete m_serial;
        m_serial = nullptr;
    }

    // Buat instance QSerialPort baru
    m_serial = new QSerialPort(ui->serialPortInfoListBox->currentText()); //(UART_PORT);

    // Konfigurasi serial port
    m_serial->setPortName(ui->serialPortInfoListBox->currentText());
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);

    // Cek apakah port berhasil dibuka
    if (!m_serial->open(QIODevice::ReadWrite)) {

        //if (!warningShown) {
        //    uartdcwarning(); // Tampilkan peringatan hanya sekali
        //    warningShown = true;
        //}

        qDebug() << "Failed to open port:" << m_serial->errorString();
        delete m_serial; // Hapus instance karena tidak digunakan
        m_serial = nullptr;
        return false;
    } else {
        qDebug() << "Open Port OK";

        // Reset status warning
        //warningShown = false;

        // Hubungkan sinyal ke slot
        connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
        connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

        // Reset status header
        headerFound = false;

        ui->btnStop->setEnabled(true);
        ui->btnRefreshSerialPort->setEnabled(false);

        ui->btnTera->setEnabled(true);
        ui->btnStart->setEnabled(true);
        startRcvUart = false;
        return true;
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
bool MainWindow::initPortForce()
{
    // Periksa apakah port sudah diinisialisasi dan terbuka
    if (m_serial && m_serial->isOpen()) {
        qDebug() << "Port eksis, close....";
        m_serial->close();
        //return true;
    }

    // Jika sudah ada instance `m_serial`, hapus untuk mencegah kebocoran memori
    if (m_serial) {
        delete m_serial;
        m_serial = nullptr;
    }

    // Buat instance QSerialPort baru
    m_serial = new QSerialPort(ui->serialPortInfoListBox->currentText()); //(UART_PORT);

    // Konfigurasi serial port
    m_serial->setPortName(ui->serialPortInfoListBox->currentText());
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);

    // Cek apakah port berhasil dibuka
    if (!m_serial->open(QIODevice::ReadWrite)) {

        //if (!warningShown) {
        //    uartdcwarning(); // Tampilkan peringatan hanya sekali
        //    warningShown = true;
        //}

        qDebug() << "Failed to open port:" << m_serial->errorString();
        QMessageBox::warning(this,"Open PORT ERROR",m_serial->errorString());
        delete m_serial; // Hapus instance karena tidak digunakan
        m_serial = nullptr;
        return false;
    } else {
        qDebug() << "Open Port OK";

        // Reset status warning
        //warningShown = false;

        // Hubungkan sinyal ke slot
        connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
        connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

        // Reset status header
        headerFound = false;

        ui->btnStop->setEnabled(true);
        ui->btnRefreshSerialPort->setEnabled(false);

        ui->btnTera->setEnabled(true);
        ui->btnStart->setEnabled(true);
        startRcvUart = false;
        return true;
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::closeSerialPort()
{
    if(m_serial){
       if (m_serial->isOpen()){
           m_serial->close();
           qDebug() << "Close OK\n";

           disconnect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
           disconnect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

           ui->btnStop->setEnabled(false);
           ui->btnRefreshSerialPort->setEnabled(true);

           ui->btnTera->setEnabled(false);
           ui->btnResetEncoder->setEnabled(false);
           ui->btnStart->setEnabled(false);

       }
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
/*
void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    qDebug() << "<rcv=" << data << ">";
    QString strData = QString::fromUtf8(data).trimmed();

    ui->logSerialTextEdit->appendPlainText(strData);
    // contoh: "0.000 kg;0.000 mm"

    // Split pakai ";"

    if(!startRcvUart){
        return;
    }

    QStringList parts = strData.split(';');
    if (parts.size() == 2) {
        QString massa = parts[0].trimmed();
        QString displacement = parts[1].trimmed();

        // Hapus satuan
        massa.remove(" kg");
        displacement.remove(" mm");

        // Debug
        qDebug() << "Massa =" << massa;
        qDebug() << "Displacement =" << displacement;

        writeLog(massa + ";" + displacement);
        qDebug() << "Writing logs---------------------------------------------------------------";


        ui->labelLoadValue->setText(massa);
        ui->labelLoadValue->setStyleSheet("QLabel { background-color: black; color: red; font-size: 32pt; }");

        ui->labelDisplacementValue->setText(displacement);
        ui->labelDisplacementValue->setStyleSheet("QLabel { background-color: black; color: red; font-size: 32pt; }");

        double d = massa.toDouble();
        // Format ke 4 digit belakang koma
        QString formattedmass = QString::number(d, 'f', 4);
        double fixed4mass = formattedmass.toDouble();

        d = displacement.toDouble();
        formattedmass = QString::number(d, 'f', 4);
        double fixed4displ = formattedmass.toDouble();

        appendLoadDisplacementPoint(fixed4displ, fixed4mass);

        // Simpan ke variabel class misalnya:
        //this->massaValue = massa;
        //this->displacementValue = displacement;

        realtimeDataSlot(massa.toDouble());
    }
}*/

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::readData()
{
    static constexpr int PACKET_SIZE = 10;

    if (!m_serial)
        return;

    // 1) READ SERIAL: kumpulkan byte yang datang.
    m_rxBuffer.append(m_serial->readAll());

    while (true)
    {
        // Cari header frame 0xED 0xDC.
        const int headerIndex = m_rxBuffer.indexOf(QByteArray("\xED\xDC", 2));

        if (headerIndex < 0)
        {
            // Header belum ditemukan. Sisakan 1 byte terakhir untuk mengantisipasi
            // 0xED berada di ujung chunk dan 0xDC datang pada readyRead berikutnya.
            if (m_rxBuffer.size() > 1)
                m_rxBuffer.remove(0, m_rxBuffer.size() - 1);

            return;
        }

        // Buang noise/sampah sebelum header.
        if (headerIndex > 0)
            m_rxBuffer.remove(0, headerIndex);

        // Tunggu sampai satu frame lengkap tersedia.
        if (m_rxBuffer.size() < PACKET_SIZE)
            return;

        const QByteArray packet = m_rxBuffer.left(PACKET_SIZE);
        m_rxBuffer.remove(0, PACKET_SIZE);

        // 2) PARSING: ubah raw packet menjadi data terstruktur.
        DataTerima parsedData;
        if (!parsePacket(packet, parsedData))
            continue;

        // 3) EMIT DATA: consumer tidak lagi menerima QByteArray mentah.
        //qDebug() << "Parsed Data ";
        emit serialDataParsed(parsedData);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::enqueueParsedData(const DataTerima &data)
{
    // 4) QUEUE: queue khusus data yang SUDAH diparsing.
    // Batasi backlog agar Pause/consumer lambat tidak membuat RAM tumbuh tanpa batas.
    if (m_dataQueue.size() >= MAX_RX_QUEUE_SIZE) {
        m_dataQueue.dequeue(); // drop frame tertua, prioritaskan data real-time terbaru
        ++m_droppedRxFrames;
        if ((m_droppedRxFrames % 100) == 1) {
            qWarning() << "RX queue penuh. Total frame dibuang:" << m_droppedRxFrames;
        }
    }
    m_dataQueue.enqueue(data);

    // Tidak ada polling timer. Begitu data masuk queue dan processing aktif,
    // kirim signal untuk menjalankan consumer.
    requestQueueProcessing();
}

void MainWindow::requestQueueProcessing()
{
    if (!m_queueProcessingEnabled || m_dataQueue.isEmpty() || m_queueProcessPending)
        return;

    // Hindari menumpuk banyak event processDataQueue jika beberapa frame
    // diterima dalam satu burst serial.
    m_queueProcessPending = true;
    emit queueDataAvailable();
}

void MainWindow::setQueueProcessingEnabled(bool enabled)
{
    m_queueProcessingEnabled = enabled;

    // Saat Start/Resume, langsung proses backlog yang mungkin terkumpul
    // ketika processing sebelumnya Pause/Stop.
    if (enabled)
        requestQueueProcessing();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return; // Abaikan jika tidak ada error
    }

    qDebug() << "Serial port error occurred:" << m_serial->errorString();
    QMessageBox::warning(this,"Open PORT ERROR",m_serial->errorString());

    if (error == QSerialPort::NoError || !m_serial) {
        QMessageBox::warning(this,"Open PORT ERROR",m_serial->errorString());
        return; // Abaikan jika tidak ada error atau m_serial null
    }

    qDebug() << "Serial port error occurred:" << m_serial->errorString();
    QMessageBox::warning(this,"Open PORT ERROR",m_serial->errorString());

    // Tutup port untuk memastikan tidak digunakan lagi
    m_serial->close();

    // Hapus objek serial dengan deleteLater() untuk menghindari crash
    m_serial->deleteLater();
    m_serial = nullptr;
    counter = 0;

    modeBegin();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::realtimeDataSlot(double value)
{
    //--------------------------------------------------
    // Timestamp awal
    //--------------------------------------------------

    static qint64 startTimeMs = -1;

    if (startTimeMs < 0)
        startTimeMs = QDateTime::currentMSecsSinceEpoch();

    const qint64 currentTimeMs =
        QDateTime::currentMSecsSinceEpoch();

    const double key =
        (currentTimeMs - startTimeMs) / 1000.0;


    //--------------------------------------------------
    // Pastikan graph tersedia
    //--------------------------------------------------

    if (ui->plottsgram->graphCount() == 0)
    {
        ui->plottsgram->addGraph();

        ui->plottsgram->graph(0)->setPen(
            QPen(QColor(40, 255, 255))
        );

        ui->plottsgram->graph(0)
            ->data()
            ->setAutoSqueeze(false);
    }


    //--------------------------------------------------
    // Tambah data LANGSUNG ketika data queue diterima
    //--------------------------------------------------

    QCPGraph *graph =
        ui->plottsgram->graph(0);

    graph->addData(
        key,
        value
    );


    //--------------------------------------------------
    // Batasi histori data di RAM
    //--------------------------------------------------

    graph->data()->removeBefore(
        qMax(0.0,
             key - TS_HISTORY_SECONDS)
    );


    //--------------------------------------------------
    // Label axis
    //--------------------------------------------------

    ui->plottsgram->xAxis->setLabel("Time (s)");
    ui->plottsgram->yAxis->setLabel("Load (kg)");


    //--------------------------------------------------
    // X axis
    // 0-8 detik pertama tidak pernah negatif.
    // Setelah itu sliding window 8 detik.
    //--------------------------------------------------

    constexpr double DISPLAY_SECONDS = 8.0;

    if (key <= DISPLAY_SECONDS)
    {
        ui->plottsgram->xAxis->setRange(
            0.0,
            DISPLAY_SECONDS
        );
    }
    else
    {
        ui->plottsgram->xAxis->setRange(
            key - DISPLAY_SECONDS,
            key
        );
    }


    //--------------------------------------------------
    // Plot LANGSUNG
    //--------------------------------------------------

    ui->plottsgram->replot(
        QCustomPlot::rpQueuedReplot
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
/*void MainWindow::on_btnStart_clicked()
{
    init_port();
    qDebug() << "begin setup plot";
    //setupPlot();
    //testDraw();
    ui->sw->setCurrentIndex(0);
    qDebug() << "end setup plot";

    qDebug() << "Start write log";
}*/

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnRefreshSerialPort_clicked()
{

    //showPortInfo(1);
    fillPortsInfo();

    modeLoadPort();
    modeStart();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnStop_clicked()
{
    //closeSerialPort();
    //qDebug() << "CLOSED UART------------------------------------------";
    //if(timerStopWatch->isActive()) timerStopWatch->stop();
    //setQueueProcessingEnabled(false);

   // if(ui->teNama->toPlainText().isEmpty()){
   //     QMessageBox::warning(this,"Peringatan","isi nama file dulu");
   //     return;
   // }

    if(m_serial && m_serial->isOpen()){

       setQueueProcessingEnabled(false);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 3; //stop
       quint8 mperintahAuto = 0;
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }else{

    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnResume_clicked()
{
    if(!timerStopWatch->isActive()) timerStopWatch->start(10);
    setQueueProcessingEnabled(true);

    if(m_serial && m_serial->isOpen()){
       modeResumed();
       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 1; //start auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::slotTimerClock()
{
    //Get current data time
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString strTanggal = currentDateTime.toString("dd");
    QLocale indonesian(QLocale::Indonesian);
    QString dayName = indonesian.toString(currentDateTime,"dddd");
    QString namaBulan = indonesian.toString(currentDateTime, "MMMM");
    strTanggal.append(" ");
    strTanggal.append(namaBulan);
    strTanggal.append(" ");

    strTanggal.append(currentDateTime.toString("yyyy"));
    // Mengonversi waktu sekarang ke dalam format string
    ui->labelCurrentDate->setText(dayName + "," + strTanggal);
    ui->labelCurrentClock->setText(currentDateTime.toString("hh:mm:ss") + " WIB");
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::processDataQueue()
{
    // Signal queued yang meminta proses sudah diterima.
    m_queueProcessPending = false;

    // Pause/Stop hanya menahan consumer. Data serial tetap boleh masuk queue,
    // sama seperti perilaku lama ketika consumer dinonaktifkan.
    if (!m_queueProcessingEnabled)
        return;

    // 5) CONSUMER: semua pekerjaan yang relatif berat (plot, kalkulasi, logging, UI)
    // dilakukan dari queue data hasil parsing, bukan dari callback readyRead.
    while (!m_dataQueue.isEmpty())
    {
        dataTerima = m_dataQueue.dequeue();

        // Pertahankan tampilan debug serial seperti implementasi sebelumnya.
        QString strRcv;
        for (unsigned char c : dataTerima.rawPacket) {
            strRcv += QString("%1 ").arg(c, 2, 16, QLatin1Char('0')).toUpper();
        }

        if (strRcv.length() >= 5)
            strRcv.remove(0, 5); // buang dua byte header dari tampilan debug

        ui->logSerialTextEdit->setText(strRcv);

        //------------------------------------
        // Debug data hasil parsing
        //------------------------------------

        /*
        qDebug() << "==========================";
        qDebug() << "Beban        :" << dataTerima.bebanAktual;
        qDebug() << "Perpindahan  :" << dataTerima.perpindahan;
        qDebug() << "Limit Switch :" << dataTerima.limitSwitch;
        qDebug() << "Motor        :" << dataTerima.motorStatus;
        qDebug() << "Limit Atas   :" << dataTerima.limitAtas;
        qDebug() << "Limit Bawah  :" << dataTerima.limitBawah;
        qDebug() << "Zero Loadcell:" << dataTerima.zeroLoadcell;
        qDebug() << "Zero Encoder :" << dataTerima.zeroEncoder;
        qDebug() << "Update Data  :" << dataTerima.updateData;
        qDebug() << "Auto Flag    :" << dataTerima.autoFlag;
*/

        // Plot langsung dari data hasil parsing. Tidak ada lagi QVector histori
        // yang terus membesar dan tidak ada copy seluruh data pada setiap sample.
        appendLoadDisplacementPoint(dataTerima.perpindahan,dataTerima.bebanAktual);
        realtimeDataSlot(dataTerima.bebanAktual);

        // Logging.
        writeLog(QString::number(dataTerima.bebanAktual) + ";" +
                 QString::number(dataTerima.perpindahan));

        // Update nilai pada UI.
        ui->labelLoadValue->setText(QString::number(dataTerima.bebanAktual));
        ui->labelDisplacementValue->setText(QString::number(dataTerima.perpindahan));

        if(dataTerima.bebanAktual >= dataTx.targetBeban){
            ui->labelBatasAtas->setText(QString::number(dataTerima.bebanAktual));
            ui->labelBatasAtas->setStyleSheet(
                "QLabel {"
                "background-color: #D71920;"
                "color: white;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );

            timerStopWatch->stop();
            setQueueProcessingEnabled(false);

            float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
            quint8 mperintahManual = 3; //stop
            quint8 mperintahAuto = 0;
            quint8 mupdateData = 0;

            sendData(mtargetBeban,
                     mperintahManual,
                     mperintahAuto,
                     mupdateData);

            if (!mMsgTargeTercapai) {
                qDebug() << "warningbox baru akan dicreate";
                mMsgTargeTercapai = new msgtargetercapai(this);
                connect(mMsgTargeTercapai, &msgtargetercapai::btnYesClicked, this, &MainWindow::on_btnMsgTargetercapai_clicked);
                connect(mMsgTargeTercapai, &QObject::destroyed, [=]() mutable {
                    qDebug() << "mDATA Object destroyed. Pointer is now nullptr.";
                    mMsgTargeTercapai = nullptr; // Set pointer to nullptr
                });
                mMsgTargeTercapai->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
                mMsgTargeTercapai->setAttribute(Qt::WA_TranslucentBackground);

                mMsgTargeTercapai->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
                mMsgTargeTercapai->setAttribute(Qt::WA_TranslucentBackground);
                mMsgTargeTercapai->setWindowModality(Qt::ApplicationModal);
                mMsgTargeTercapai->setAttribute(Qt::WA_DeleteOnClose);
                mMsgTargeTercapai->show();
            } else {
                // Jika sudah ada, kirim notifikasi
                qDebug() << "warningbox udah dicreate";
                //mMsgLogout->sendNotification("Notifikasi: Tombol ditekan lagi!" + QString::number(counterklik));
            }


        }else{
            ui->labelBatasAtas->setStyleSheet(
                "QLabel {"
                "background-color: rgb(143, 255, 248);"
                "color: black;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );
        }

        // Limit switch label.
        switch (dataTerima.limitSwitch) {
        case 0: // normal
            break;

        case 1: // atas
            ui->labelBatasAtas->setText(QString::number(dataTerima.bebanAktual));
            ui->labelBatasAtas->setStyleSheet(
                "QLabel {"
                "background-color: #D71920;"
                "color: white;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );
            break;

        case 2: // bawah
            ui->labelBatasBawah->setText(QString::number(dataTerima.bebanAktual));
            ui->labelBatasAtas->setStyleSheet(
                "QLabel {"
                "background-color: #D71920;"
                "color: white;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );
            break;

        default:
            ui->labelBatasAtas->setText("");
            ui->labelBatasBawah->setText("");
            ui->labelBatasAtas->setStyleSheet(
                "QLabel {"
                "background-color: #14A0F1;"
                "color: black;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );
            ui->labelBatasBawah->setStyleSheet(
                "QLabel {"
                "background-color: #14A0F1;"
                "color: white;"
                "font-size: 36px;"
                "font-weight: bold;"
                "font-family: Arial;"
                "}"
            );
            break;
        }
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::updateStopwatch(){
     qint64 ms = elapsedTimer.elapsed();

     int minutes      = ms / 60000;
     int seconds      = (ms % 60000) / 1000;
     int milliseconds = (ms % 1000) / 10;   // 00-99

     ui->labelStopWatch->setText(
         QString("%1:%2.%3")
         .arg(minutes, 2, 10, QChar('0'))
         .arg(seconds, 2, 10, QChar('0'))
         .arg(milliseconds, 2, 10, QChar('0'))
     );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    const QStringList list = ui->serialPortInfoListBox->itemData(idx).toStringList();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_serialPortInfoListBox_currentIndexChanged(const QString &arg1)
{
    //ui->btnStart->setEnabled(true);
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_serialPortInfoListBox_activated(const QString &arg1)
{
    //ui->btnStart->setEnabled(true);
}



/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTera_clicked()
{
    if(m_serial && m_serial->isOpen()){
       //ui->btnStart->setVisible(false);
       //ui->btnSelesai->setVisible(true);
       //ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 0; //stop auto
       quint8 mupdateData = 2; //nol kan load cell

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->labelLoadValue->setText("0.0000");
    }
}



/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnResetEncoder_clicked()
{
    if(m_serial && m_serial->isOpen()){
      // ui->btnStart->setVisible(false);
      // ui->btnSelesai->setVisible(true);
      // ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 0; //stop auto
       quint8 mupdateData = 3; //nol kan encder

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->labelDisplacementValue->setText("0.0000");
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_logSerialTextEdit_textChanged()
{
    QString text = ui->logSerialTextEdit->text();

    /*
    // markers
    QString startMarker = "=== Status Saat Ini ===";
    QString endMarker   = "Jarak encoder:";

    // find positions
    int startIndex = text.indexOf(startMarker);
    int endIndex   = text.indexOf(endMarker, startIndex);

    QString extracted;

    if (startIndex != -1 && endIndex != -1) {
        // cari akhir baris setelah "Jarak encoder:"
        int lineEnd = text.indexOf("\r\n", endIndex);
        if (lineEnd != -1) {
            lineEnd += 2; // tambahkan panjang "\r\n"
            extracted = text.mid(startIndex, lineEnd - startIndex);
        }
    }
*/

    // markers
    QString startMarker = "=== Status Saat Ini ===";
    QString endMarker   = "mm";

    // find positions
    int startIndex = text.indexOf(startMarker);
    int endIndex   = text.indexOf(endMarker, startIndex);

    QString extracted;

    if (startIndex != -1 && endIndex != -1) {
        // include endMarker in substring
        endIndex += endMarker.length();
        extracted = text.mid(startIndex, endIndex - startIndex);
    }

    // now extracted contains the substring
    qDebug() << "Extracted block:\n" << extracted;
}



/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnStart_clicked()
{
    if(setupPlotView){
        resetPlotView();
        setupPlotView = false;
    }

    clearGraph();
    m_dataQueue.clear();
    m_droppedRxFrames = 0;
    dataTerima = DataTerima{};
    m_rxBuffer.clear();

    startRcvUart = true;

    logFilePath = logDir.filePath(ui->teNama->toPlainText() + ".csv");// + "_" + strTanggal + ".csv");
    qDebug() << "Path " << logFilePath;

    if(ui->serialPortInfoListBox->currentText() != ""){
      // if(!init_port()){
      //     QMessageBox::warning(this,"Peringatan","PORT gagal dibuka");
      //     return;
      // }
       if(ui->teNama->toPlainText().isEmpty()){
           //QMessageBox::warning(this,"Peringatan","isi nama file dulu");
           if (!mMsgisinamadulu) {
               qDebug() << "warningbox baru akan dicreate";
               mMsgisinamadulu = new msgisinamadulu(this);
               connect(mMsgisinamadulu, &msgisinamadulu::btnYesClicked, this, &MainWindow::on_btnMsgisinamadulu_clicked);
               connect(mMsgisinamadulu, &QObject::destroyed, [=]() mutable {
                   qDebug() << "mDATA Object destroyed. Pointer is now nullptr.";
                   mMsgisinamadulu = nullptr; // Set pointer to nullptr
               });
               mMsgisinamadulu->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
               mMsgisinamadulu->setAttribute(Qt::WA_TranslucentBackground);

               mMsgisinamadulu->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
               mMsgisinamadulu->setAttribute(Qt::WA_TranslucentBackground);
               mMsgisinamadulu->setWindowModality(Qt::ApplicationModal);
               mMsgisinamadulu->setAttribute(Qt::WA_DeleteOnClose);
               mMsgisinamadulu->show();
           } else {
               // Jika sudah ada, kirim notifikasi
               qDebug() << "warningbox udah dicreate";
               //mMsgLogout->sendNotification("Notifikasi: Tombol ditekan lagi!" + QString::number(counterklik));
           }
           return;
       }
       if(m_serial && m_serial->isOpen()){
          modeRunning();
          QTimer::singleShot(2000, this, [this](){
                qDebug() << "Startn";
                //ui->labelTargetBebanVal->setText(QString::number(mtargetBeban));
                //setupRealtimeDataDemo(ui->plotmmgram);
                //setupRealtimeDataDemoTs(ui->plottsgram);

                testRunning = true;
                elapsedTimer.start();      // mulai stopwatch

                //elapsedTimer.restart();
                if(!timerStopWatch->isActive()) timerStopWatch->start(10);
                setQueueProcessingEnabled(true);

                float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
                quint8 mperintahManual = 0;
                quint8 mperintahAuto = 1;
                quint8 mupdateData = 1;

                sendData(mtargetBeban,
                         mperintahManual,
                         mperintahAuto,
                         mupdateData);
               });
           }
    }else{
        QMessageBox::warning(this,"Peringatan","Pilih COM Port dulu!");
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnClearGraphmmGram_clicked()
{
     clearGraph();
     m_dataQueue.clear();
     dataTerima = DataTerima{};
     m_rxBuffer.clear();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnClearGraphtsgram_clicked()
{
    clearGraph();
    m_dataQueue.clear();
    dataTerima = DataTerima{};
    m_rxBuffer.clear();
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnStart_pressed()
{
    ui->btnStart->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/mulai2.png);"
        "}"
    );
}

void MainWindow::on_btnStart_released()
{
    ui->btnStart->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/mulai1.png);"
        "}"
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnRefreshSerialPort_pressed()
{
    /*ui->btnRefreshSerialPort->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/circle2.png);"
        "}"
    );*/

    ui->btnRefreshSerialPort->setStyleSheet("QPushButton {""border-image: url(:/circle2.png);""}");
}

void MainWindow::on_btnRefreshSerialPort_released()
{
    ui->btnRefreshSerialPort->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/circle1.png);"
        "}"
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnDown_clicked()
{
    //if(ui->teNama->toPlainText().isEmpty()){
    //    QMessageBox::warning(this,"Peringatan","isi nama file dulu");
    //    return;
    //}

    if(m_serial && m_serial->isOpen()){
       //ui->btnStart->setVisible(true);
       //ui->btnSelesai->setVisible(true);
       //ui->btnPause->setVisible(false);

       setQueueProcessingEnabled(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 2; //turun
       quint8 mperintahAuto = 0;
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/

void MainWindow::on_btnUp_clicked()
{
    //if(ui->teNama->toPlainText().isEmpty()){
    //    QMessageBox::warning(this,"Peringatan","isi nama file dulu");
    //    return;
    //}

    if(m_serial && m_serial->isOpen()){
       //ui->btnStart->setVisible(true);
       //ui->btnSelesai->setVisible(true);
       //ui->btnPause->setVisible(false);

       setQueueProcessingEnabled(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 1; //naik
       quint8 mperintahAuto = 0;
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTest_clicked()
{

   /*void MainWindow::sendData(float targetBeban,
                             quint8 perintahManual,
                             quint8 perintahAuto,
                             quint8 updateData)
                             */

    if(m_serial && m_serial->isOpen()){
        float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
        quint8 mperintahManual = 0;
        quint8 mperintahAuto = 1;
        quint8 mupdateData = 1;

        sendData(mtargetBeban,
                 mperintahManual,
                 mperintahAuto,
                 mupdateData);

        ui->labelTargetBebanVal->setText(QString::number(mtargetBeban));
        setupRealtimeDataDemo(ui->plotmmgram);
        setupRealtimeDataDemo(ui->plottsgram);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnArrowLeft_clicked()
{
     ui->sw->setCurrentIndex(0);
}

void MainWindow::on_btnArrowRight_clicked()
{
     ui->sw->setCurrentIndex(1);
}

void MainWindow::on_btnArrowRightDL_clicked()
{
     ui->sw->setCurrentIndex(1);
}

void MainWindow::on_btnArrowLeftDL_clicked()
{
    ui->sw->setCurrentIndex(0);
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTargetBebanRefresh_pressed()
{
    /*ui->btnTargetBebanRefresh->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/arrowcircle2.png);"
        "}"
    );*/

    ui->btnTargetBebanRefresh->setStyleSheet("QPushButton {""border-image: url(:/refresh2.png);""}");
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTargetBebanRefresh_released()
{
    ui->btnTargetBebanRefresh->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/refresh1.png);"
        "}"
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTera_pressed()
{
    ui->btnTera->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/zero2.png);"
        "}"
    );
}

void MainWindow::on_btnTera_released()
{
    ui->btnTera->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/zero1.png);"
        "}"
    );
}

void MainWindow::on_btnResetEncoder_pressed()
{
    ui->btnResetEncoder->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/zero2.png);"
        "}"
    );
}

void MainWindow::on_btnResetEncoder_released()
{
    ui->btnResetEncoder->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/zero1.png);"
        "}"
    );
}

void MainWindow::on_btnDown_pressed()
{
    ui->btnDown->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/down2.png);"
        "}"
    );
}

void MainWindow::on_btnDown_released()
{
    ui->btnDown->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/down1.png);"
        "}"
    );
}

void MainWindow::on_btnUp_pressed()
{
    ui->btnUp->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/up2.png);"
        "}"
    );
}

void MainWindow::on_btnUp_released()
{
    ui->btnUp->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/up1.png);"
        "}"
    );
}

void MainWindow::on_btnStop_pressed()
{
    ui->btnStop->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/stop4.png);"
        "}"
    );
}

void MainWindow::on_btnStop_released()
{
    ui->btnStop->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/stop3.png);"
        "}"
    );
}

void MainWindow::on_btnOpen_pressed()
{
    ui->btnOpen->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/open2.png);"
        "}"
    );
}

void MainWindow::on_btnOpen_released()
{
    ui->btnOpen->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/open1.png);"
        "}"
    );
}

void MainWindow::on_btnSave_pressed()
{
    ui->btnSave->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/save2.png);"
        "}"
    );
}



void MainWindow::on_btnSave_released()
{
    ui->btnSave->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/save1.png);"
        "}"
    );
}

void MainWindow::on_btnArrowRightDL_pressed()
{
    ui->btnArrowRightDL->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/right2.png);"
        "}"
    );
}

void MainWindow::on_btnArrowRightDL_released()
{
    ui->btnArrowRightDL->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/right1.png);"
        "}"
    );
}

void MainWindow::on_btnArrowLeftDL_pressed()
{
    ui->btnArrowLeftDL->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/left2.png);"
        "}"
    );
}

void MainWindow::on_btnArrowLeftDL_released()
{
    ui->btnArrowLeftDL->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/left1.png);"
        "}"
    );
}

void MainWindow::on_btnArrowRight_pressed()
{
    ui->btnArrowRight->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/right2.png);"
        "}"
    );
}

void MainWindow::on_btnArrowRight_released()
{
    ui->btnArrowRight->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/right1.png);"
        "}"
    );
}

void MainWindow::on_btnArrowLeft_pressed()
{
    ui->btnArrowLeft->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/left2.png);"
        "}"
    );
}

void MainWindow::on_btnArrowLeft_released()
{
    ui->btnArrowLeft->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/left1.png);"
        "}"
    );
}

void MainWindow::on_btnResume_pressed()
{
    ui->btnResume->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/resume2.png);"
        "}"
    );
}

void MainWindow::on_btnResume_released()
{
    ui->btnResume->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/resume.png);"
        "}"
    );
}

void MainWindow::on_btnPause_pressed()
{
    ui->btnPause->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/pause2.png);"
        "}"
    );
}

void MainWindow::on_btnPause_released()
{
    ui->btnPause->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/pause.png);"
        "}"
    );
}

void MainWindow::on_btnSelesai_pressed()
{
    ui->btnSelesai->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/selesai2.png);"
        "}"
    );
}

void MainWindow::on_btnSelesai_released()
{
    ui->btnSelesai->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/selesai.png);"
        "}"
    );
}

void MainWindow::on_btnAddNewMeasurement_pressed()
{
    ui->btnAddNewMeasurement->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/add2.png);"
        "}"
    );
}

void MainWindow::on_btnAddNewMeasurement_released()
{
    ui->btnAddNewMeasurement->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/add.png);"
        "}"
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTargetBebanRefresh_clicked()
{
    if(m_serial && m_serial->isOpen()){
       //ui->btnStart->setVisible(false);
       //ui->btnSelesai->setVisible(true);
       //ui->btnPause->setVisible(true);

       dataTx.targetBeban = ui->labelTargetBebanVal->text().toFloat();
       float mtargetBeban =  dataTx.targetBeban;
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 0; //stop auto
       quint8 mupdateData =12; //update target beban kan load cell

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnOpen_clicked()
{
    if(!setupPlotView){
        setPlotView();
        setupPlotView = true;
    }

    QString fileName = QFileDialog::getOpenFileName(
          this,
          tr("Open CSV File"),
          QDir::homePath(),                  // Folder awal
          tr("CSV Files (*.csv);;All Files (*)")
      );

      if (fileName.isEmpty())
          return;

      // Tampilkan nama file (opsional)
      qDebug() << "Selected file:" << fileName;

      // Panggil fungsi untuk membaca dan menampilkan CSV
      loadCsvToPlot(fileName);
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnSelesai_clicked()
{
    if (!mMsgEndUkur) {
        qDebug() << "warningbox baru akan dicreate";
        mMsgEndUkur = new msgendukur(this);
        connect(mMsgEndUkur, &msgendukur::btnYesClicked, this, &MainWindow::onbtnYes_msgEndUkurClicked);
        connect(mMsgEndUkur, &msgendukur::btnNoClicked, this, &MainWindow::onbtnNo_msgEndUkurClicked);
        connect(mMsgEndUkur, &QObject::destroyed, [=]() mutable {
            qDebug() << "mDATA Object destroyed. Pointer is now nullptr.";
            mMsgEndUkur = nullptr; // Set pointer to nullptr
        });
        mMsgEndUkur->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
        mMsgEndUkur->setAttribute(Qt::WA_TranslucentBackground);

        mMsgEndUkur->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
        mMsgEndUkur->setAttribute(Qt::WA_TranslucentBackground);
        mMsgEndUkur->setWindowModality(Qt::ApplicationModal);
        mMsgEndUkur->setAttribute(Qt::WA_DeleteOnClose);
        mMsgEndUkur->show();
    } else {
        // Jika sudah ada, kirim notifikasi
        qDebug() << "warningbox udah dicreate";
        //mMsgLogout->sendNotification("Notifikasi: Tombol ditekan lagi!" + QString::number(counterklik));
    }

    /*
    if(timerStopWatch->isActive()) timerStopWatch->stop();
    setQueueProcessingEnabled(false);

    if(m_serial && m_serial->isOpen()){
       modeEnd();
       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 3; //stop auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->teNama->setText("");
    }
    */
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnPause_clicked()
{
    if(timerStopWatch->isActive()) timerStopWatch->stop();
    setQueueProcessingEnabled(false);

    if(m_serial && m_serial->isOpen()){
       modePaused();

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 2; //start, resume auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);


    }
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnSave_clicked()
{
    // File sumber
   // QString sourceFile = "/home/pi/data/config.json";
   // logFilePath = exePath + "/log"; //logDir.filePath();
    QString sourceDir = exePath + "/log";

    QDir dir(sourceDir);

    QFileInfoList files = dir.entryInfoList(
                QDir::Files | QDir::NoDotAndDotDot);

    if (files.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Tidak ada file.");
        return;
    }

    std::sort(files.begin(), files.end(),
              [](const QFileInfo &a, const QFileInfo &b)
    {
        return a.birthTime() > b.birthTime();
    });

    QString sourceFile = files.first().absoluteFilePath();

    // Pastikan file sumber ada
    if (!QFile::exists(sourceFile))
    {
        QMessageBox::warning(this,
                             "Error",
                             "File source tidak ditemukan.");
        return;
    }

    // Dialog pilih folder
    QString targetDir = QFileDialog::getExistingDirectory(
                this,
                "Pilih Folder Tujuan",
                QDir::homePath(),
                QFileDialog::ShowDirsOnly |
                QFileDialog::DontResolveSymlinks);

    // User menekan Cancel
    if (targetDir.isEmpty())
        return;

    // Nama file tetap sama
    QString targetFile =
            targetDir + "/" + QFileInfo(sourceFile).fileName();

    // Hapus jika sudah ada
    if (QFile::exists(targetFile))
        QFile::remove(targetFile);

    // Copy file
    if (!QFile::copy(sourceFile, targetFile))
    {
        QMessageBox::critical(this,
                              "Error",
                              "Failed save file.");
        return;
    }

    QMessageBox::information(this,
                             "Success",
                             "File succesfully saved");
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnExit_clicked()
{
    //qApp->quit();
    // Alternatively: QCoreApplication::quit();
    // Jika belum ada instance, buat baru
    if (!mMsgLogout) {
        qDebug() << "warningbox baru akan dicreate";
        mMsgLogout = new msglogout(this);
        connect(mMsgLogout, &msglogout::btnYesClicked, this, &MainWindow::onbtnYes_msgLogoutClicked);
        connect(mMsgLogout, &msglogout::btnNoClicked, this, &MainWindow::onbtnNo_msgLogoutClicked);
        connect(mMsgLogout, &QObject::destroyed, [=]() mutable {
            qDebug() << "mDATA Object destroyed. Pointer is now nullptr.";
            mMsgLogout = nullptr; // Set pointer to nullptr
        });
        mMsgLogout->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
        mMsgLogout->setAttribute(Qt::WA_TranslucentBackground);

        mMsgLogout->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);  // Mengatur window tanpa frame
        mMsgLogout->setAttribute(Qt::WA_TranslucentBackground);
        mMsgLogout->setWindowModality(Qt::ApplicationModal);
        mMsgLogout->setAttribute(Qt::WA_DeleteOnClose);
        mMsgLogout->show();
    } else {
        // Jika sudah ada, kirim notifikasi
        qDebug() << "warningbox udah dicreate";
        //mMsgLogout->sendNotification("Notifikasi: Tombol ditekan lagi!" + QString::number(counterklik));
    }
}

//----------------------------------------------------------------------------------------------------
void MainWindow::on_btnAddNewMeasurement_clicked()
{
    ui->teNama->setText(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    ui->teNama->setEnabled(true);

    ui->labelLoadValue->setText("0.0000");
    ui->labelDisplacementValue->setText("0.0000");
    ui->labelStopWatch->setText("00:00:00");

    //ui->btnStart->setEnabled(true);
    //modeStart();

    clearGraph();
    m_dataQueue.clear();
    dataTerima = DataTerima{};
    m_rxBuffer.clear();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnMsgTargetercapai_clicked()
{

}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnMsgisinamadulu_clicked()
{

}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::horzScrollBarChanged(int value)
{
  if (qAbs(ui->plottsgram->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plottsgram->xAxis->setRange(value/100.0, ui->plottsgram->xAxis->range().size(), Qt::AlignCenter);
    ui->plottsgram->replot();
  }
}

void MainWindow::vertScrollBarChanged(int value)
{
  if (qAbs(ui->plottsgram->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plottsgram->yAxis->setRange(-value/100.0, ui->plottsgram->yAxis->range().size(), Qt::AlignCenter);
    ui->plottsgram->replot();
  }
}

void MainWindow::xAxisChanged(QCPRange range)
{
  ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void MainWindow::yAxisChanged(QCPRange range)
{
  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::horzScrollBar2Changed(int value)
{
    if (qAbs(ui->plotmmgram->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
      ui->plotmmgram->xAxis->setRange(value/100.0, ui->plotmmgram->xAxis->range().size(), Qt::AlignCenter);
      ui->plotmmgram->replot();
    }
}

void MainWindow::vertScrollBar2Changed(int value)
{
    if (qAbs(ui->plotmmgram->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
      ui->plotmmgram->yAxis->setRange(-value/100.0, ui->plotmmgram->yAxis->range().size(), Qt::AlignCenter);
      ui->plotmmgram->replot();
    }
}

void MainWindow::xAxis2Changed(QCPRange range)
{
    ui->horizontalScrollBar2->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
    ui->horizontalScrollBar2->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void MainWindow::yAxis2Changed(QCPRange range)
{
    ui->verticalScrollBar2->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
    ui->verticalScrollBar2->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::onbtnYes_msgLogoutClicked()
{
    qApp->quit();
}

void MainWindow::onbtnNo_msgLogoutClicked()
{
    qDebug() << "btn no msglog diklik";
    //mMsgLogout =  nullptr;
    //modeLoadPort();
    modeStart();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::onbtnYes_msgEndUkurClicked()
{
    if(timerStopWatch->isActive()) timerStopWatch->stop();
    setQueueProcessingEnabled(false);

    if(m_serial && m_serial->isOpen()){
       modeEnd();
       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 3; //stop auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->teNama->setText("");
    }
}

//------------------------------------------------------------------------------------
void MainWindow::onbtnNo_msgEndUkurClicked()
{
    modePaused();
}

//------------------------------------------------------------------------------------
void MainWindow::on_serialPortInfoListBox_currentTextChanged(const QString &arg1)
{
    qDebug() << "CB text changed " << arg1;
    initPortForce();
}
