#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getDisplayResolution(); //1920 x 1080

    //setGeometry(0, 0, widthScreen, heightScreen);

    setupRealtimeDataDemo(ui->plotmmgram);
    setupRealtimeDataDemo(ui->plottsgram);

    ui->plotmmgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plottsgram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //setupPlot();
    DataManagerInit();

    timerClock = new QTimer(this);
    connect(timerClock, SIGNAL(timeout()), this, SLOT(slotTimerClock()));
    timerClock->start(1000);

    timerProcessPayload = new QTimer(this);
    connect(timerProcessPayload, SIGNAL(timeout()), this, SLOT(slotTimerProcessPayload()));
    //timerProcessPayload->start(10);

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

    //setWidgetPosition();



    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    // create connection between axes and scroll bars:
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plotmmgram->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plotmmgram->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    connect(ui->horizontalScrollBar2, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged2(int)));
    connect(ui->verticalScrollBar2, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged2(int)));
    connect(ui->plottsgram->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plottsgram->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    testRunning = false;
    ui->btnPause->setVisible(true);
    ui->btnStart->setVisible(false);
    ui->btnSelesai->setVisible(false);
    ui->btnResume->setVisible(false);
    ui->btnTest->setVisible(false);
    ui->btnRefreshSerialPort->setVisible(true);
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
void MainWindow::drawRealTimemmgram()
{
    QVector<double> x, y;
    for (const auto &row : dataLoad) {
        //x.append(row.displacement);
        //y.append(row.masa);

        x.append(row.masa);
        y.append(row.displacement);
    }

    ui->plotmmgram->addGraph();
    ui->plotmmgram->graph(0)->setPen(QPen(Qt::yellow, 2));
    //ui->plot->graph(0)->setData(x, y);
    ui->plotmmgram->graph(0)->setData(x,y);
    ui->plotmmgram->rescaleAxes();
    ui->plotmmgram->replot();
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::drawRealTimeetsgram(QString massastr)
{
    realtimeDataSlot(massastr);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::clearGraph()
{
    for (int i = 0; i < ui->plotmmgram->graphCount(); ++i) {
        ui->plotmmgram->graph(i)->data()->clear();
    }
    ui->plotmmgram->replot();

    for (int i = 0; i < ui->plottsgram->graphCount(); ++i) {
        ui->plottsgram->graph(i)->data()->clear();
    }
    ui->plottsgram->replot();
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::DataManagerInit()
{
    // Inisialisasi dengan 1 row <0.0000, 0.0000>
    dataLoad.append({0.0000, 0.0000});
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::addOrUpdate(double displacement, double masa)
{
    bool updated = false;
      for (int i = 0; i < dataLoad.size(); ++i) {
          if (dataLoad[i].displacement == displacement ||
              dataLoad[i].masa == masa) {
              // Update row yang punya kesamaan displacement atau masa
              dataLoad[i].displacement = displacement;
              dataLoad[i].masa = masa;
              updated = true;
              break;
          }
      }
      if (!updated) {
          // Tambahkan row baru
          dataLoad.append({displacement, masa});
      }
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::printData()
{
    qDebug() << "Data Vector:";
      for (const auto &row : dataLoad) {
          qDebug().nospace() << "<" << row.displacement << ", " << row.masa << ">";
      }
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::loadCsvToPlot(const QString &fileName)
{
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

    // Hapus graph lama
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
    ui->plottsgram->yAxis->setLabel("Value");

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

    ui->plotmmgram->xAxis->setLabel("Time (s)");
    ui->plotmmgram->yAxis->setLabel("Value");

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
    //Setup Widget Position and Size
    //ui->sw->move(0,0);
    //ui->sw->resize(500,500);
    //ui->sw->setGeometry(0, 0, 500, 500);
    float hHead = (heightScreen-100)/8;
    float wHead = widthScreen/6;
    ui->frame0->setGeometry(10,0,widthScreen-20, hHead);//-20);
    ui->labelJudul->setGeometry(10,0,widthScreen-20, hHead);//-20);

    ui->btnOpen->setGeometry(10,10,ui->frame0->height()-10,ui->frame0->height()-20);
    ui->btnSave->setGeometry(20+ui->frame0->height(),10,ui->frame0->height()-10,ui->frame0->height()-20);

    ui->labelCurrentDate->setGeometry(ui->frame0->width()-(ui->frame0->height()*2)-5,
                                      5,
                                      ui->frame0->height()*2,
                                      (ui->frame0->height()-10)/3
                                      );

    ui->labelCurrentClock->setGeometry(ui->frame0->width()-(ui->frame0->height()*2)-5,
                                       5 + (ui->frame0->height()-10)*1/3,
                                       ui->frame0->height()*2,
                                       (ui->frame0->height()-10)*2/3
                                       );

    ui->frameLeft1->setGeometry(10,
                               ui->frame0->y() + ui->frame0->height() + 10,
                               (widthScreen - 50)/4,
                               ui->frame0->height()*3/2
                               );

    ui->frameLeft2->setGeometry(
                               (widthScreen-10)/4 + 20,
                                ui->frame0->y() + ui->frame0->height() + 10,
                               (widthScreen - 50)/4,
                               ui->frame0->height()*3/2
                               );

    ui->frameLeft3->setGeometry(
                               2*(widthScreen-10)/4 + 30,
                                ui->frame0->y() + ui->frame0->height() + 10,
                               (widthScreen - 50)/4,
                               ui->frame0->height()*3/2
                               );

    ui->frameLeft4->setGeometry(
                               (3*widthScreen-10)/4 + 40,
                                ui->frame0->y() + ui->frame0->height() + 10,
                               (widthScreen - 50)/4 - 35,
                               ui->frame0->height()*3/2
                               );

    ui->frameLeft5->setGeometry(
                               (3*widthScreen-10)/4 + 40,
                               ui->frameLeft4->y() + ui->frameLeft4->height() +20,
                               (widthScreen - 50)/4 - 30,
                               //heightScreen - ui->frame0->height() - ui->frameLeft4->height() - 30
                               heightScreen*12/(2+2+2+11) + 10
                               );

    ui->sw->setGeometry(10,
                        ui->frameLeft4->y() + ui->frameLeft4->height() +20,
                        ui->frameLeft1->width() + ui->frameLeft2->width() + ui->frameLeft3->width() + 40,
                        //heightScreen - ui->frame0->height() - ui->logSerialTextEdit->height() - ui->frameLeft1->height() - 50
                        (heightScreen-40)*10/(2+2+2+11)
                        );

    ui->logSerialTextEdit->setGeometry(10,
                        ui->sw->y() + ui->sw->height() + 20,
                        ui->frameLeft1->width() + ui->frameLeft2->width() + ui->frameLeft3->width() + 40,
                        ui->frameLeft5->height() - ui->sw->height() - 10
                        );

    //Label atas

    ui->labelTargetBebanKG->setGeometry(0,0,
                                        ui->frameLeft1->width(),
                                        ui->frameLeft1->height()/3
                                        );

    ui->labelLoadKg->setGeometry(0,0,
                                        ui->frameLeft2->width(),
                                        ui->frameLeft2->height()/3
                                        );

    ui->labelDisplacementmm->setGeometry(0,0,
                                        ui->frameLeft3->width(),
                                        ui->frameLeft3->height()/3
                                        );

    ui->labelWaktuClock->setGeometry(0,0,
                                        ui->frameLeft4->width(),
                                        ui->frameLeft4->height()/3
                                        );

    //Label value
    //1
    ui->labelTargetBebanVal->setGeometry(10,
                               ui->frameLeft1->height()/3,
                               (ui->frameLeft1->width())*2/3 - 10,
                               (ui->frameLeft1->height())*2/3 - 10
                               );

    ui->btnTargetBebanRefresh->setGeometry(ui->frameLeft1->width()*2/3 + 10,
                             ui->frameLeft1->height()*1/3,
                             (ui->frameLeft1->width()-20)*1/3 - 10,
                             (ui->frameLeft1->height()-20)*2/3
                             );

    //2
    ui->labelLoadValue->setGeometry(10,
                               ui->frameLeft2->height()/3,
                               (ui->frameLeft2->width())*2/3 - 10,
                               (ui->frameLeft1->height())*2/3 - 10
                               );

    ui->btnTera->setGeometry(ui->frameLeft2->width()*2/3 + 10,
                             ui->frameLeft2->height()*1/3,
                             (ui->frameLeft2->width()-20)*1/3 - 10,
                             (ui->frameLeft2->height()-20)*2/3 - 10
                             );

    //3
    ui->labelDisplacementValue->setGeometry(10,
                               ui->frameLeft3->height()/3,
                               (ui->frameLeft3->width())*2/3 - 10,
                               (ui->frameLeft3->height())*2/3 - 10
                               );

    ui->btnResetEncoder->setGeometry(ui->frameLeft2->width()*2/3 + 10,
                             ui->frameLeft3->height()*1/3,
                             (ui->frameLeft3->width()-20)*1/3 - 10,
                             (ui->frameLeft3->height()-20)*2/3 - 10
                             );

    //4
    ui->labelStopWatch->setGeometry(10,
                             ui->frameLeft4->height()*1/3,
                             (ui->frameLeft4->width())- 20,
                             (ui->frameLeft4->height()*2/3) - 10
                             );

    /*
    float k = (heightScreen-hHead-50) - 60;//7/8;

    ui->frameLeft1->setGeometry(10,
                               hHead + 10,
                               wHead,
                               (k*2/10) //+ 20
                               );

    ui->frameLeft2->setGeometry(10 + wHead/4,
                                hHead + 10,
                                wHead,
                                (k*3/10) //+30
                                );





    //ui->labelLoad->setGeometry(ui->frameLeft->width()*1/5,40,ui->frameLeft->width()*3/5,ui->labelLoad->height());
   // ui->labelDisplacement->setGeometry(ui->frameLeft->width()*1/5,120,ui->frameLeft->width()*3/5,ui->labelDisplacement->height());

    //-------------Right side--------------------
    //ui->frameSw->setGeometry(10+10+(widthScreen/6)+10, (heightScreen/8)+10, widthScreen-20 , heightScreen - 20);
    //ui->sw->setGeometry(0,0, ui->frameSw->width()-10, ui->frameSw->height()-10);

    //ui->sw->setGeometry(10+10+(widthScreen/6)+10, (heightScreen/8)+10, widthScreen-20 - (widthScreen/6)+10-30, (heightScreen*8/10));

   ui->sw->setGeometry(wHead + 20,
                        hHead+10,
                        widthScreen-wHead-30,
                        k + 60
                        );

   // ui->plottsgram->setGeometry(70,40,ui->sw->width()-90,ui->sw->height()-90);
    ui->plotmmgram->setGeometry(70,40,ui->sw->width()-90,ui->sw->height()-90);

    ui->labelHeadTsGram->setGeometry(0,10, ui->sw->width(),20);
    ui->labelHeadmmGram->setGeometry(0,10, ui->sw->width(),20);

    ui->labelmm->setGeometry(0,ui->plotmmgram->height() + 40, ui->sw->width(),20);
    ui->labelts->setGeometry(0,ui->plotmmgram->height() + 40, ui->sw->width(),20);

    ui->labelLoadmm->setGeometry(10,0,40,ui->sw->height()-20);
    ui->labelLoadTs->setGeometry(10,0,40,ui->sw->height()-20);

    ui->btnClearGraphmmGram->setGeometry(0+5,
                                         ui->sw->height()-ui->btnClearGraphmmGram->height()-5,
                                         ui->btnClearGraphmmGram->width() - 5,
                                         ui->btnClearGraphmmGram->height() - 5
                                         );

    ui->btnClearGraphtsgram->setGeometry(0+5,
                                         ui->sw->height()-ui->btnClearGraphtsgram->height()-5,
                                         ui->btnClearGraphtsgram->width() - 5,
                                         ui->btnClearGraphtsgram->height() - 5
                                         );
*/

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void MainWindow::unpackFlag(uint8_t flag)
{
    dataTerima.motorStatus  = flag & (1 << 0);
    dataTerima.limitAtas    = flag & (1 << 1);
    dataTerima.limitBawah   = flag & (1 << 2);
    dataTerima.zeroLoadcell = flag & (1 << 3);
    dataTerima.zeroEncoder  = flag & (1 << 4);
    dataTerima.updateData   = flag & (1 << 5);
    dataTerima.autoFlag     = flag & (1 << 6);
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

    plotmmgram->addGraph(); // blue line, Pressure
    plotmmgram->graph(0)->setPen(QPen(QColor(40, 255, 255)));

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
    plotmmgram->xAxis->setRange(0, 10000); //350);
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

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
bool MainWindow::init_port()
{
    // Periksa apakah port sudah diinisialisasi dan terbuka
    if (m_serial && m_serial->isOpen()) {
        qDebug() << "Port already open.";
        return false;
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

        addOrUpdate(fixed4mass,fixed4displ);

        // Simpan ke variabel class misalnya:
        //this->massaValue = massa;
        //this->displacementValue = displacement;
        drawRealTimemmgram();
        drawRealTimeetsgram(massa);
    }
}*/

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::readData()
{
    const int PACKET_SIZE = 10;

    // Tambahkan data baru ke buffer
    m_rxBuffer.append(m_serial->readAll());

    while (true)
    {
        // Cari header
        int headerIndex = m_rxBuffer.indexOf(QByteArray("\xED\xDC",2));

        if(headerIndex < 0)
        {
            // Header tidak ditemukan
            if(m_rxBuffer.size() > 1)
                m_rxBuffer.remove(0, m_rxBuffer.size()-1);

            return;
        }

        // Buang sampah sebelum header
        if(headerIndex > 0)
            m_rxBuffer.remove(0, headerIndex);

        // Belum lengkap
        if(m_rxBuffer.size() < PACKET_SIZE)
            return;

        // Ambil 1 packet
        QByteArray packet = m_rxBuffer.left(PACKET_SIZE);

        // Masukkan queue
        m_packetQueue.enqueue(packet);

        // Hapus dari buffer
        m_rxBuffer.remove(0, PACKET_SIZE);
    }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return; // Abaikan jika tidak ada error

    qDebug() << "Serial port error occurred:" << m_serial->errorString();

    if (error == QSerialPort::NoError || !m_serial) return; // Abaikan jika tidak ada error atau m_serial null

    qDebug() << "Serial port error occurred:" << m_serial->errorString();

    // Tutup port untuk memastikan tidak digunakan lagi
    m_serial->close();

    // Hapus objek serial dengan deleteLater() untuk menghindari crash
    m_serial->deleteLater();
    m_serial = nullptr;
    counter = 0;
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::realtimeDataSlot(QString value)
{
    static QTime timeStart = QTime::currentTime();
     // calculate two new data points:
     double key = timeStart.msecsTo(QTime::currentTime()) / 1000.0; // time elapsed since start of demo, in seconds
     static double lastPointKey = 0;

     if (key - lastPointKey > 0.002) { // at most add point every 2 ms
         double filteredValue = value.toDouble();// = kalmanFilter[channel].update(value.toDouble());
         ui->plottsgram->graph(0)->addData(key, filteredValue);
         lastPointKey = key;
     }

     // make key axis range scroll with the data (at a constant range size of 8):
     ui->plottsgram->xAxis->setRange(key, 8, Qt::AlignRight);

     static QElapsedTimer replotTimer;
     if (!replotTimer.isValid()) replotTimer.start();

     if (replotTimer.elapsed() >= 50) { // Refresh setiap 50 ms
         ui->plottsgram->replot();
         replotTimer.restart();
     }
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
    // qDebug() << "start print >> ";
    // printData();
    // drawRealTime();
    // qDebug() << "end print >> ";

    //showPortInfo(1);
    fillPortsInfo();


    ui->btnPause->setEnabled(false);
    ui->btnStart->setEnabled(true);
    ui->btnDown->setEnabled(false);
    ui->btnUp->setEnabled(false);
    ui->btnRefreshSerialPort->setEnabled(false);
    ui->btnOpen->setEnabled(false);
    ui->btnTera->setEnabled(false);
    ui->btnResetEncoder->setEnabled(false);
    ui->btnTargetBebanRefresh->setEnabled(false);
    ui->labelTargetBebanVal->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->serialPortInfoListBox->setEnabled(true);
    ui->btnSelesai->setEnabled(false);
    ui->teNama->setEnabled(false);
    ui->btnResume->setEnabled(false);
    ui->btnResume->setVisible(false);

    ui->btnPause->setVisible(false);
    ui->btnStart->setVisible(true);
    ui->btnSelesai->setVisible(false);
    ui->btnResume->setVisible(false);
    ui->btnTest->setVisible(false);
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnStop_clicked()
{
    //closeSerialPort();
    //qDebug() << "CLOSED UART------------------------------------------";
    timerStopWatch->stop();
    timerProcessPayload->stop();

    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 3; //stop
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
void MainWindow::on_btnResume_clicked()
{
    timerStopWatch->start(5);
    timerProcessPayload->start(5);

    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(false);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 3; //stop auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->btnPause->setEnabled(true);
       ui->btnStart->setEnabled(false);
       ui->btnDown->setEnabled(false);
       ui->btnUp->setEnabled(false);
       ui->btnRefreshSerialPort->setEnabled(false);
       ui->btnOpen->setEnabled(false);
       ui->btnTera->setEnabled(false);
       ui->btnResetEncoder->setEnabled(false);
       ui->btnTargetBebanRefresh->setEnabled(false);
       ui->labelTargetBebanVal->setEnabled(false);
       ui->btnSave->setEnabled(false);
       ui->serialPortInfoListBox->setEnabled(false);
       ui->teNama->setEnabled(false);
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
void MainWindow::slotTimerProcessPayload()
{
    while(!m_packetQueue.isEmpty())
    {
        QByteArray packet = m_packetQueue.dequeue();

        QString strRcv;
        for (unsigned char c : packet) {
            strRcv += QString("%1 ").arg(c, 2, 16, QLatin1Char('0')).toUpper();
        }

        if (strRcv.length() >= 5)
            strRcv.remove(0, 5);   // Hapus 4 karakter pertama

        ui->logSerialTextEdit->setText(strRcv);

        const uchar *p = reinterpret_cast<const uchar*>(packet.constData());

        //------------------------------------
        // Beban Aktual (int32 Big Endian)
        //------------------------------------
        int32_t bebanInt =
                (int32_t(p[2]) << 24) |
                (int32_t(p[3]) << 16) |
                (int32_t(p[4]) << 8 ) |
                 int32_t(p[5]);

        dataTerima.bebanAktual = bebanInt / 1000.0f;

        //------------------------------------
        // Perpindahan (int16 Big Endian)
        //------------------------------------
        int16_t perpInt =
                (int16_t(p[6]) << 8) |
                 int16_t(p[7]);

        dataTerima.perpindahan = perpInt / 1000.0f;

        //------------------------------------
        // Limit Switch
        //------------------------------------
        dataTerima.limitSwitch = p[8];

        //------------------------------------
        // Status Flag
        //------------------------------------
        unpackFlag(p[9]);

        //------------------------------------
        // Debug
        //------------------------------------
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


        addOrUpdate(dataTerima.bebanAktual,dataTerima.perpindahan); //susun agar tidak ada data redundant

        //tampilkan di grafik
        drawRealTimemmgram();
        drawRealTimeetsgram(QString::number(dataTerima.bebanAktual));

        //Logging
        writeLog(QString::number(dataTerima.bebanAktual) + ";" + QString::number(dataTerima.perpindahan));

        //Placement
        ui->labelLoadValue->setText(QString::number(dataTerima.bebanAktual));
        ui->labelDisplacementValue->setText(QString::number(dataTerima.perpindahan));

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
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 0; //stop auto
       quint8 mupdateData = 2; //nol kan load cell

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
void MainWindow::on_btnResetEncoder_clicked()
{
    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 0; //stop auto
       quint8 mupdateData = 3; //nol kan encder

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);
    }}



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
       startRcvUart = true;
       //ui->btnStart->setText("STOP");
       QDateTime currentDateTime = QDateTime::currentDateTime();
       QString strTanggal = currentDateTime.toString("dd");
       QLocale indonesian(QLocale::Indonesian);
       QString dayName = indonesian.toString(currentDateTime,"dddd");
       QString namaBulan = indonesian.toString(currentDateTime, "MMMM");
       //strTanggal.append(" ");
       strTanggal.append(namaBulan);
       //strTanggal.append(" ");

       strTanggal.append(currentDateTime.toString("yyyy"));
       strTanggal.append(currentDateTime.toString("hhmmss"));

       logFilePath = logDir.filePath(ui->teNama->toPlainText() + "_" + strTanggal + ".csv");
       qDebug() << "Path " << logFilePath;

       if(ui->serialPortInfoListBox->currentText() != ""){
           if(!init_port()) return;
           if(m_serial && m_serial->isOpen()){
               //Disable all button, except StopFromRunning
               ui->btnPause->setVisible(true);
               ui->btnStart->setVisible(false);
               ui->btnSelesai->setVisible(true);
               ui->btnResume->setVisible(false);

               ui->btnStart->setEnabled(false);
               ui->btnPause->setEnabled(false);
               ui->btnResume->setEnabled(false);
               ui->btnDown->setEnabled(false);
               ui->btnUp->setEnabled(false);
               ui->btnRefreshSerialPort->setEnabled(false);
               ui->btnOpen->setEnabled(false);
               ui->btnTera->setEnabled(false);
               ui->btnResetEncoder->setEnabled(false);
               ui->btnTargetBebanRefresh->setEnabled(false);
               ui->labelTargetBebanVal->setEnabled(false);
               ui->btnSave->setEnabled(false);
               ui->serialPortInfoListBox->setEnabled(false);
               ui->btnSelesai->setEnabled(true);
               ui->teNama->setEnabled(false);

               QTimer::singleShot(2000, this, [this](){
                   qDebug() << "Startn";
                   //ui->labelTargetBebanVal->setText(QString::number(mtargetBeban));
                   setupRealtimeDataDemo(ui->plotmmgram);
                   setupRealtimeDataDemo(ui->plottsgram);

                   testRunning = true;
                   elapsedTimer.start();      // mulai stopwatch

                   //elapsedTimer.restart();
                   timerStopWatch->start(10);
                   timerProcessPayload->start(10);

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
       }
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnClearGraphmmGram_clicked()
{
     clearGraph();
     dataLoad.clear();
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnClearGraphtsgram_clicked()
{
    clearGraph();
    dataLoad.clear();
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
    ui->btnRefreshSerialPort->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/circle2.png);"
        "}"
    );
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
    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

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
    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

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
    ui->btnTargetBebanRefresh->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/arrowcircle2.png);"
        "}"
    );
}

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTargetBebanRefresh_released()
{
    ui->btnTargetBebanRefresh->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/arrowcircle1.png);"
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
        "border-image: url(:/stop2.png);"
        "}"
    );
}

void MainWindow::on_btnStop_released()
{
    ui->btnStop->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/stop1.png);"
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

/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnTargetBebanRefresh_clicked()
{
    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
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
    timerStopWatch->stop();
    timerProcessPayload->stop();

    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(false);
       ui->btnPause->setVisible(true);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 3; //stop auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->btnPause->setEnabled(true);
       ui->btnStart->setEnabled(false);
       ui->btnDown->setEnabled(false);
       ui->btnUp->setEnabled(false);
       ui->btnRefreshSerialPort->setEnabled(false);
       ui->btnOpen->setEnabled(false);
       ui->btnTera->setEnabled(false);
       ui->btnResetEncoder->setEnabled(false);
       ui->btnTargetBebanRefresh->setEnabled(false);
       ui->labelTargetBebanVal->setEnabled(false);
       ui->btnSave->setEnabled(false);
       ui->serialPortInfoListBox->setEnabled(false);
       ui->teNama->setEnabled(false);
    }
}


/*****************************************************************************************************
**--------------------------------------------------------------------------------------------------**
**--------------------------------------------------------------------------------------------------**
******************************************************************************************************/
void MainWindow::on_btnPause_clicked()
{
    timerStopWatch->stop();
    timerProcessPayload->stop();
    if(m_serial && m_serial->isOpen()){
       ui->btnStart->setVisible(false);
       ui->btnSelesai->setVisible(true);
       ui->btnPause->setVisible(false);

       float mtargetBeban = ui->labelTargetBebanVal->text().toFloat();
       quint8 mperintahManual = 0; //
       quint8 mperintahAuto = 1; //start, resume auto
       quint8 mupdateData = 0;

       sendData(mtargetBeban,
                mperintahManual,
                mperintahAuto,
                mupdateData);

       ui->btnPause->setEnabled(false);
       ui->btnStart->setEnabled(false);
       ui->btnResume->setEnabled(true);
       ui->btnDown->setEnabled(false);
       ui->btnUp->setEnabled(false);
       ui->btnRefreshSerialPort->setEnabled(false);
       ui->btnOpen->setEnabled(false);
       ui->btnTera->setEnabled(false);
       ui->btnResetEncoder->setEnabled(false);
       ui->btnTargetBebanRefresh->setEnabled(false);
       ui->labelTargetBebanVal->setEnabled(false);
       ui->btnSave->setEnabled(false);
       ui->serialPortInfoListBox->setEnabled(false);
       ui->btnSelesai->setEnabled(true);
       ui->teNama->setEnabled(false);
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
    qApp->quit();
    // Alternatively: QCoreApplication::quit();
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




