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

#ifdef Q_OS_LINUX
    #define UART_PORT "ttyS0"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

#ifdef Q_OS_WIN
    #define UART_PORT "COM6"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

#ifdef Q_OS_MAC
    #define UART_PORT "cu.usbserial-110" //"tty.usbserial-110" //"tty.usbserial-A50285BI" //"cu.usbserial-10" //"ttyS0"  //"ttyUSB0" "COM5" "ttyUSB0"
#endif

struct RowData {
    double displacement;
    double masa;
};

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


private slots:
    bool init_port();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void realtimeDataSlot(QString value);

    //void on_btnStart_clicked();
    void on_btnRefreshSerialPort_clicked();
    void on_btnStop_clicked();

    void slotTimerClock();
    void slotTimerProcessPayload();
    void updateStopwatch();
    void showPortInfo(int idx);

    //void showFiles();
    //void downloadSelectedFile();

    void on_serialPortInfoListBox_currentIndexChanged(const QString &arg1);
    void on_serialPortInfoListBox_activated(const QString &arg1);
    void on_btnTera_clicked();
    void on_btnResetEncoder_clicked();
    void on_logSerialTextEdit_textChanged();
    void on_btnStart_clicked();
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
    void on_btnTargetBebanRefresh_clicked();
    void on_btnOpen_clicked();
    void on_btnStopFromRun_clicked();
    void on_btnResume_clicked();
    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer *timerClock = nullptr;
    QTimer *timerProcessPayload = nullptr;
    QElapsedTimer elapsedTimer;
    QTimer *timerStopWatch = nullptr;
    QQueue<QByteArray> m_packetQueue;
    bool startRcvUart;

    QVector<RowData> dataLoad;

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

    //Download files
    //QListWidget *fileListWidget;
    //QPushButton *btnShowFiles;
    //QPushButton *btnDownload;
    //QString sourceFolderPath;

    void setupPlotmm();
    void setupPlotTs();

    void testDraw();
    void drawRealTimemmgram();
    void drawRealTimeetsgram(QString massastr);
    void clearGraph();

    //Vector manipulation
    void DataManagerInit();
    void addOrUpdate(double displacement, double masa);
    void printData();
    void loadCsvToPlot(const QString &fileName);

    //Logging
    void writeLog(const QString &text);
    void writeLog2(const QString &path, const QString &text);

    void getDisplayResolution();

    void fillPortsInfo();
    void setWidgetPosition();

    //New
    QByteArray m_rxBuffer;

    struct DataTerima{
           float bebanAktual;
           float perpindahan;

           uint8_t limitSwitch;

           bool motorStatus;
           bool limitAtas;
           bool limitBawah;
           bool zeroLoadcell;
           bool zeroEncoder;
           bool updateData;
           bool autoFlag;
    };

    struct DataTX
    {
        float targetBeban = 0.0f;
        quint8 perintahManual = 0;
        quint8 perintahAuto = 0;
        quint8 updateData = 0;
    };

    bool testRunning = false;
    DataTerima dataTerima;
    void unpackFlag(uint8_t flag);
    void sendData(quint32 targetBeban,
                  quint8 perintahManual,
                  quint8 perintahAuto,
                  quint8 updateData);

    void sendDataStruct(const DataTX &tx);
};

#endif // MAINWINDOW_H
