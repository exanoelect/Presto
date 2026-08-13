#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h> // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <iostream>
#include <QVector>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QRegularExpressionValidator>
#include <QDoubleValidator>
#include <QElapsedTimer>
#include <QFileDialog>
#include <qcustomplot.h>
#include <msglogout.h>
#include <msgendukur.h>
#include <QMessageBox>
#include <QQueue>
#include <QByteArray>
#include <QMetaType>
#include <msgtargettercapai.h>
#include <msgisinamadulu.h>

//color label batas atas bawah background-color: #14A0F1;

#ifdef Q_OS_LINUX
    #define UART_PORT "ttyS0"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

#ifdef Q_OS_WIN
    #define UART_PORT "COM6"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

#ifdef Q_OS_MAC
    #define UART_PORT "cu.usbserial-110" //"tty.usbserial-110" //"tty.usbserial-A50285BI" //"cu.usbserial-10" //"ttyS0"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

// Data hasil parsing satu frame serial.
// Raw packet tetap disimpan untuk kebutuhan debug/log serial, sedangkan
// plot dan kalkulasi hanya menggunakan field yang sudah terurai.
struct DataTerima {
    float bebanAktual = 0.0f;
    float perpindahan = 0.0f;

    quint8 limitSwitch = 0;

    quint8 motorStatus = 0;   // 2 bit: 0..3
    bool newtarget1 = false;
    bool newtarget2 = false;
    bool zeroLoadcell = false;
    bool zeroEncoder = false;
    bool updateData = false;
    bool autoFlag = false;

    QByteArray rawPacket;
};

Q_DECLARE_METATYPE(DataTerima)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void setupRealtimeDataDemoTs(QCustomPlot *customPlot);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    // Dikeluarkan setelah satu frame serial selesai diparsing.
    void serialDataParsed(const DataTerima &data);
    // Memicu consumer queue tanpa polling QTimer.
    void queueDataAvailable();

private slots:
    bool init_port();
    bool initPortForce();
    void closeSerialPort();
    void readData();
    void enqueueParsedData(const DataTerima &data);
    void processDataQueue();
    void handleError(QSerialPort::SerialPortError error);

    void realtimeDataSlot(double value);

    //void on_btnStart_clicked();
    void on_btnRefreshSerialPort_clicked();
    void on_btnStop_clicked();

    void slotTimerClock();
    void updateStopwatch();
    void showPortInfo(int idx);

    //void showFiles();
    //void downloadSelectedFile();

    void on_serialPortInfoListBox_currentIndexChanged(const QString &arg1);
    void on_serialPortInfoListBox_activated(const QString &arg1);
    void on_btnTera_clicked();
    void on_btnResetEncoder_clicked();
    void on_logSerialRX_textChanged();
    void on_btnStart_clicked();
    void on_btnResume_clicked();
    void on_btnClearGraphmmGram_clicked();
    void on_btnClearGraphtsgram_clicked();
    void on_btnStart_pressed();
    void on_btnStart_released();
    void on_btnRefreshSerialPort_pressed();
    void on_btnRefreshSerialPort_released();
    void on_btnDown_clicked();
    void on_btnUp_clicked();
    void on_btnTest_clicked();
    void on_btnArrowLeft_clicked();
    void on_btnArrowRight_clicked();
    void on_btnArrowRightDL_clicked();
    void on_btnArrowLeftDL_clicked();
    void on_btnTargetBebanRefresh_pressed();
    void on_btnTargetBebanRefresh_released();
    void on_btnTera_pressed();
    void on_btnTera_released();
    void on_btnResetEncoder_pressed();
    void on_btnResetEncoder_released();
    void on_btnDown_pressed();
    void on_btnDown_released();
    void on_btnUp_pressed();
    void on_btnUp_released();
    void on_btnStop_pressed();
    void on_btnStop_released();
    void on_btnOpen_pressed();
    void on_btnOpen_released();
    void on_btnSave_pressed();
    void on_btnSave_released();
    void on_btnArrowRightDL_pressed();
    void on_btnArrowRightDL_released();
    void on_btnArrowLeftDL_pressed();
    void on_btnArrowLeftDL_released();
    void on_btnArrowRight_pressed();
    void on_btnArrowRight_released();
    void on_btnArrowLeft_pressed();
    void on_btnArrowLeft_released();
    void on_btnResume_pressed();
    void on_btnResume_released();
    void on_btnPause_pressed();
    void on_btnPause_released();
    void on_btnSelesai_pressed();
    void on_btnSelesai_released();
    void on_btnAddNewMeasurement_pressed();
    void on_btnAddNewMeasurement_released();
    void on_btnTargetBebanRefresh_clicked();
    void on_btnOpen_clicked();
    void on_btnSelesai_clicked();
    void on_btnPause_clicked();
    void on_btnSave_clicked();
    void on_btnExit_clicked();
    void on_btnAddNewMeasurement_clicked();
    void on_btnMsgTargetercapai_clicked();
    void on_btnMsgTargetTercapaiResume_clicked();
    void on_btnMsgisinamadulu_clicked();

    //1...............
    void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);

    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);

    //2.........................
    void horzScrollBar2Changed(int value);
    void vertScrollBar2Changed(int value);

    void xAxis2Changed(QCPRange range);
    void yAxis2Changed(QCPRange range);

    void onbtnYes_msgLogoutClicked();
    void onbtnNo_msgLogoutClicked();

    void onbtnYes_msgEndUkurClicked();
    void onbtnNo_msgEndUkurClicked();

    void on_serialPortInfoListBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    bool m_uiReady = false;

    QString demoName;
    QTimer *timerClock = nullptr;
    QElapsedTimer elapsedTimer;
    QTimer *timerStopWatch = nullptr;
    QQueue<DataTerima> m_dataQueue;
    bool m_queueProcessingEnabled = false;
    bool m_queueProcessPending = false;

    // True saat motor digerakkan manual dengan tombol UP/DOWN.
    // RX/plot tetap aktif selama mode manual.
    bool m_manualMovementActive = false;

    // Latch satu kejadian limit atas untuk indikator limit.
    bool m_limitAtasLatched = false;

    // Deteksi akhir pengukuran AUTO:
    // popup hanya boleh muncul setelah autoFlag pernah TRUE lalu menjadi FALSE.
    bool m_autoMeasurementWasActive = false;
    bool m_autoCompletionHandled = false;

    bool startRcvUart;

    // Batas memori untuk data real-time. Histori lengkap tetap ditulis ke CSV/log.
    static constexpr int MAX_RX_QUEUE_SIZE = 2000;
    static constexpr int MAX_MM_PLOT_POINTS = 10000;
    static constexpr double TS_HISTORY_SECONDS = 10.0;

    QCPCurve *m_mmCurve = nullptr;
    double m_mmCurveSequence = 0.0;
    double m_lastPlotDisplacement = 0.0;
    double m_lastPlotMass = 0.0;
    bool m_hasLastPlotPoint = false;
    quint64 m_droppedRxFrames = 0;

    QSerialPort *m_serial = nullptr;
    bool headerFound = false;
    bool crFound;
    bool lfFound;

    int counter;
    QString exePath;
    QDir logDir;
    QString logFilePath;

    int widthScreen;
    int heightScreen;

    void setupPlotmm();
    void setupPlotTs();

    void testDraw();
    void appendLoadDisplacementPoint(double displacement, double mass);
    void clearGraph();
    void loadCsvToPlot(const QString &fileName);

    //Logging
    void writeLog(const QString &text);
    void writeLog2(const QString &path, const QString &text);

    void getDisplayResolution();

    void fillPortsInfo();
    void setWidgetPosition();

    //New
    QByteArray m_rxBuffer;

    struct DataTX
    {
        float targetBeban = 0.0f;
        quint8 perintahManual = 0;
        quint8 perintahAuto = 0;
        quint8 updateData = 0;
    };

    DataTX dataTx;
    bool testRunning = false;
    DataTerima dataTerima;
    void setQueueProcessingEnabled(bool enabled);
    void requestQueueProcessing();

    bool parsePacket(const QByteArray &packet, DataTerima &parsedData) const;
    void unpackFlag(quint8 flag, DataTerima &parsedData) const;
    void sendData(quint32 targetBeban,
                  quint8 perintahManual,
                  quint8 perintahAuto,
                  quint8 updateData);

    void sendDataStruct(const DataTX &tx);
    void setPlotView();
    void resetPlotView();
    bool setupPlotView;
    void positionExitButton();

    //mode
    void modeBegin();
    void modeLoadPort();
    void modeStart();
    void modeRunning();
    void modePaused();
    void modeResumed();
    void modeEnd();

    double m_mmMaxX = 100.0;
    msglogout *mMsgLogout =  nullptr;
    msgendukur *mMsgEndUkur = nullptr;
    msgtargetercapai *mMsgTargeTercapai = nullptr;
    msgisinamadulu *mMsgisinamadulu = nullptr;
};

#endif // MAINWINDOW_H
