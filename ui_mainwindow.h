/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frameLeft5;
    QPushButton *btnRefreshSerialPort;
    QComboBox *serialPortInfoListBox;
    QPushButton *btnStart;
    QFrame *frameLeft_5;
    QLabel *labelLoadStr_4;
    QPushButton *btnStop;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QLabel *labelLoadStr_8;
    QLabel *labelLoadStr_9;
    QLabel *labelBatasAtas;
    QLabel *labelBatasBawah;
    QFrame *frameLeft_7;
    QLabel *labelNama;
    QTextEdit *teNama;
    QPushButton *btnAddNewMeasurement;
    QPushButton *btnTest;
    QPushButton *btnSelesai;
    QPushButton *btnPause;
    QPushButton *btnResume;
    QStackedWidget *sw;
    QWidget *page;
    QPushButton *btnClearGraphmmGram;
    QLabel *labelmm;
    QLabel *labelHeadmmGram;
    QPushButton *btnArrowRightDL;
    QPushButton *btnArrowLeftDL;
    QScrollBar *horizontalScrollBar2;
    QScrollBar *verticalScrollBar2;
    QCustomPlot *plotmmgram;
    QWidget *page_4;
    QPushButton *btnClearGraphtsgram;
    QLabel *labelts;
    QLabel *labelHeadTsGram;
    QPushButton *btnArrowRight;
    QPushButton *btnArrowLeft;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QCustomPlot *plottsgram;
    QFrame *frameLeft3;
    QLabel *labelDisplacementValue;
    QPushButton *btnResetEncoder;
    QLabel *labelDisplacementmm;
    QFrame *frameLeft4;
    QLabel *labelStopWatch;
    QLabel *labelWaktuClock;
    QFrame *frameLeft2;
    QLabel *labelLoadValue;
    QPushButton *btnTera;
    QLabel *labelLoadKg;
    QFrame *frameLeft1;
    QLabel *labelTargetBebanKG;
    QPushButton *btnTargetBebanRefresh;
    QLineEdit *labelTargetBebanVal;
    QFrame *frame0;
    QPushButton *btnSave;
    QPushButton *btnOpen;
    QLabel *labelCurrentClock;
    QLabel *labelCurrentDate;
    QLabel *labelJudul;
    QPushButton *btnExit;
    QLabel *logSerialTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setStyleSheet(QStringLiteral("background-color:#B4B4B4;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frameLeft5 = new QFrame(centralWidget);
        frameLeft5->setObjectName(QStringLiteral("frameLeft5"));
        frameLeft5->setGeometry(QRect(1440, 350, 461, 681));
        frameLeft5->setStyleSheet(QLatin1String("background-color: #F3F3F3;\n"
"border-radius: 30px;"));
        frameLeft5->setFrameShape(QFrame::Box);
        frameLeft5->setFrameShadow(QFrame::Raised);
        btnRefreshSerialPort = new QPushButton(frameLeft5);
        btnRefreshSerialPort->setObjectName(QStringLiteral("btnRefreshSerialPort"));
        btnRefreshSerialPort->setGeometry(QRect(330, 570, 101, 91));
        btnRefreshSerialPort->setStyleSheet(QStringLiteral("border-image: url(:/circle1.png);"));
        serialPortInfoListBox = new QComboBox(frameLeft5);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));
        serialPortInfoListBox->setGeometry(QRect(10, 580, 281, 81));
        serialPortInfoListBox->setStyleSheet(QLatin1String("font: 75 36pt \"MS Shell Dlg 2\";\n"
"border-radius: 30px;\n"
"background-color: rgb(251, 255, 203);"));
        btnStart = new QPushButton(frameLeft5);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setEnabled(true);
        btnStart->setGeometry(QRect(10, 470, 211, 91));
        btnStart->setStyleSheet(QStringLiteral("border-image: url(:/mulai1.png);"));
        frameLeft_5 = new QFrame(frameLeft5);
        frameLeft_5->setObjectName(QStringLiteral("frameLeft_5"));
        frameLeft_5->setGeometry(QRect(10, 140, 441, 181));
        frameLeft_5->setStyleSheet(QStringLiteral("background-color:#FFF699;"));
        frameLeft_5->setFrameShape(QFrame::StyledPanel);
        frameLeft_5->setFrameShadow(QFrame::Raised);
        labelLoadStr_4 = new QLabel(frameLeft_5);
        labelLoadStr_4->setObjectName(QStringLiteral("labelLoadStr_4"));
        labelLoadStr_4->setGeometry(QRect(130, 0, 181, 41));
        labelLoadStr_4->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 28pt \".AppleSystemUIFont\";"));
        labelLoadStr_4->setAlignment(Qt::AlignCenter);
        btnStop = new QPushButton(frameLeft_5);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setEnabled(true);
        btnStop->setGeometry(QRect(150, 50, 141, 131));
        btnStop->setStyleSheet(QStringLiteral("border-image: url(:/stop3.png);"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStop->setIcon(icon);
        btnStop->setIconSize(QSize(0, 0));
        btnUp = new QPushButton(frameLeft_5);
        btnUp->setObjectName(QStringLiteral("btnUp"));
        btnUp->setEnabled(true);
        btnUp->setGeometry(QRect(340, 50, 91, 121));
        btnUp->setStyleSheet(QStringLiteral("border-image: url(:/up1.png);"));
        btnUp->setIcon(icon);
        btnUp->setIconSize(QSize(0, 0));
        btnDown = new QPushButton(frameLeft_5);
        btnDown->setObjectName(QStringLiteral("btnDown"));
        btnDown->setEnabled(true);
        btnDown->setGeometry(QRect(10, 50, 91, 121));
        btnDown->setStyleSheet(QStringLiteral("border-image: url(:/down1.png);"));
        labelLoadStr_8 = new QLabel(frameLeft_5);
        labelLoadStr_8->setObjectName(QStringLiteral("labelLoadStr_8"));
        labelLoadStr_8->setGeometry(QRect(10, 20, 101, 29));
        labelLoadStr_8->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 18pt \".AppleSystemUIFont\";"));
        labelLoadStr_8->setAlignment(Qt::AlignCenter);
        labelLoadStr_9 = new QLabel(frameLeft_5);
        labelLoadStr_9->setObjectName(QStringLiteral("labelLoadStr_9"));
        labelLoadStr_9->setGeometry(QRect(340, 20, 91, 29));
        labelLoadStr_9->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 18pt \"MS Shell Dlg 2\";"));
        labelLoadStr_9->setAlignment(Qt::AlignCenter);
        labelBatasAtas = new QLabel(frameLeft5);
        labelBatasAtas->setObjectName(QStringLiteral("labelBatasAtas"));
        labelBatasAtas->setGeometry(QRect(10, 330, 441, 61));
        labelBatasAtas->setStyleSheet(QLatin1String("font: 18pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(143, 255, 248);"));
        labelBatasAtas->setAlignment(Qt::AlignCenter);
        labelBatasAtas->setIndent(-1);
        labelBatasBawah = new QLabel(frameLeft5);
        labelBatasBawah->setObjectName(QStringLiteral("labelBatasBawah"));
        labelBatasBawah->setGeometry(QRect(10, 400, 441, 61));
        labelBatasBawah->setStyleSheet(QStringLiteral("background-color: rgb(133, 255, 255);"));
        labelBatasBawah->setAlignment(Qt::AlignCenter);
        labelBatasBawah->setIndent(-1);
        frameLeft_7 = new QFrame(frameLeft5);
        frameLeft_7->setObjectName(QStringLiteral("frameLeft_7"));
        frameLeft_7->setGeometry(QRect(10, 10, 441, 121));
        frameLeft_7->setStyleSheet(QStringLiteral("background-color:#FFF699;"));
        frameLeft_7->setFrameShape(QFrame::StyledPanel);
        frameLeft_7->setFrameShadow(QFrame::Raised);
        labelNama = new QLabel(frameLeft_7);
        labelNama->setObjectName(QStringLiteral("labelNama"));
        labelNama->setGeometry(QRect(0, 0, 441, 31));
        labelNama->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 24pt \".AppleSystemUIFont\";"));
        labelNama->setAlignment(Qt::AlignCenter);
        teNama = new QTextEdit(frameLeft_7);
        teNama->setObjectName(QStringLiteral("teNama"));
        teNama->setGeometry(QRect(10, 40, 351, 71));
        teNama->setStyleSheet(QLatin1String("background-color: rgb(222, 255, 239);\n"
"font: 24pt \"MS Shell Dlg 2\";\n"
""));
        btnAddNewMeasurement = new QPushButton(frameLeft_7);
        btnAddNewMeasurement->setObjectName(QStringLiteral("btnAddNewMeasurement"));
        btnAddNewMeasurement->setGeometry(QRect(370, 40, 71, 71));
        btnAddNewMeasurement->setStyleSheet(QStringLiteral("border-image: url(:/add.png);"));
        btnTest = new QPushButton(frameLeft5);
        btnTest->setObjectName(QStringLiteral("btnTest"));
        btnTest->setGeometry(QRect(300, 610, 31, 41));
        btnSelesai = new QPushButton(frameLeft5);
        btnSelesai->setObjectName(QStringLiteral("btnSelesai"));
        btnSelesai->setEnabled(true);
        btnSelesai->setGeometry(QRect(250, 470, 201, 91));
        btnSelesai->setStyleSheet(QStringLiteral("border-image: url(:/selesai.png);"));
        btnPause = new QPushButton(frameLeft5);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setEnabled(true);
        btnPause->setGeometry(QRect(10, 470, 211, 91));
        btnPause->setStyleSheet(QStringLiteral("border-image: url(:/pause.png);"));
        btnResume = new QPushButton(frameLeft5);
        btnResume->setObjectName(QStringLiteral("btnResume"));
        btnResume->setEnabled(true);
        btnResume->setGeometry(QRect(10, 470, 211, 91));
        btnResume->setStyleSheet(QStringLiteral("border-image: url(:/resume.png);"));
        sw = new QStackedWidget(centralWidget);
        sw->setObjectName(QStringLiteral("sw"));
        sw->setGeometry(QRect(10, 350, 1411, 611));
        sw->setStyleSheet(QLatin1String("background-color: #F3F3F3;\n"
"border-radius: 30px;"));
        sw->setFrameShape(QFrame::Box);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        btnClearGraphmmGram = new QPushButton(page);
        btnClearGraphmmGram->setObjectName(QStringLiteral("btnClearGraphmmGram"));
        btnClearGraphmmGram->setGeometry(QRect(10, 790, 80, 40));
        btnClearGraphmmGram->setStyleSheet(QLatin1String("image: url(:/clear.png);\n"
"color: rgb(255, 250, 189);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearGraphmmGram->setIcon(icon1);
        labelmm = new QLabel(page);
        labelmm->setObjectName(QStringLiteral("labelmm"));
        labelmm->setGeometry(QRect(620, 760, 251, 29));
        labelmm->setStyleSheet(QStringLiteral("background-color: transparent;"));
        labelmm->setAlignment(Qt::AlignCenter);
        labelHeadmmGram = new QLabel(page);
        labelHeadmmGram->setObjectName(QStringLiteral("labelHeadmmGram"));
        labelHeadmmGram->setGeometry(QRect(60, 10, 1341, 29));
        labelHeadmmGram->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 12pt \"MS Shell Dlg 2\";"));
        labelHeadmmGram->setAlignment(Qt::AlignCenter);
        btnArrowRightDL = new QPushButton(page);
        btnArrowRightDL->setObjectName(QStringLiteral("btnArrowRightDL"));
        btnArrowRightDL->setGeometry(QRect(1300, 10, 80, 30));
        btnArrowRightDL->setStyleSheet(QStringLiteral("border-image: url(:/right1.png);"));
        btnArrowLeftDL = new QPushButton(page);
        btnArrowLeftDL->setObjectName(QStringLiteral("btnArrowLeftDL"));
        btnArrowLeftDL->setGeometry(QRect(20, 10, 80, 30));
        btnArrowLeftDL->setStyleSheet(QStringLiteral("border-image: url(:/left1.png);"));
        horizontalScrollBar2 = new QScrollBar(page);
        horizontalScrollBar2->setObjectName(QStringLiteral("horizontalScrollBar2"));
        horizontalScrollBar2->setGeometry(QRect(20, 590, 1361, 20));
        horizontalScrollBar2->setOrientation(Qt::Horizontal);
        verticalScrollBar2 = new QScrollBar(page);
        verticalScrollBar2->setObjectName(QStringLiteral("verticalScrollBar2"));
        verticalScrollBar2->setGeometry(QRect(1390, 40, 20, 531));
        verticalScrollBar2->setOrientation(Qt::Vertical);
        plotmmgram = new QCustomPlot(page);
        plotmmgram->setObjectName(QStringLiteral("plotmmgram"));
        plotmmgram->setGeometry(QRect(20, 50, 1360, 540));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotmmgram->sizePolicy().hasHeightForWidth());
        plotmmgram->setSizePolicy(sizePolicy);
        sw->addWidget(page);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        btnClearGraphtsgram = new QPushButton(page_4);
        btnClearGraphtsgram->setObjectName(QStringLiteral("btnClearGraphtsgram"));
        btnClearGraphtsgram->setGeometry(QRect(10, 790, 80, 40));
        btnClearGraphtsgram->setStyleSheet(QLatin1String("image: url(:/clear.png);\n"
"color: rgb(255, 250, 189);"));
        btnClearGraphtsgram->setIcon(icon1);
        labelts = new QLabel(page_4);
        labelts->setObjectName(QStringLiteral("labelts"));
        labelts->setGeometry(QRect(530, 800, 251, 29));
        labelts->setStyleSheet(QStringLiteral("background-color: transparent;"));
        labelts->setAlignment(Qt::AlignCenter);
        labelHeadTsGram = new QLabel(page_4);
        labelHeadTsGram->setObjectName(QStringLiteral("labelHeadTsGram"));
        labelHeadTsGram->setGeometry(QRect(40, 10, 1351, 29));
        labelHeadTsGram->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 12pt \"MS Shell Dlg 2\";"));
        labelHeadTsGram->setAlignment(Qt::AlignCenter);
        btnArrowRight = new QPushButton(page_4);
        btnArrowRight->setObjectName(QStringLiteral("btnArrowRight"));
        btnArrowRight->setGeometry(QRect(1300, 10, 80, 30));
        btnArrowRight->setStyleSheet(QStringLiteral("border-image: url(:/right1.png);"));
        btnArrowLeft = new QPushButton(page_4);
        btnArrowLeft->setObjectName(QStringLiteral("btnArrowLeft"));
        btnArrowLeft->setGeometry(QRect(20, 10, 80, 30));
        btnArrowLeft->setStyleSheet(QStringLiteral("border-image: url(:/left1.png);"));
        horizontalScrollBar = new QScrollBar(page_4);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(0, 590, 1411, 20));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(page_4);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(1390, 50, 20, 541));
        verticalScrollBar->setOrientation(Qt::Vertical);
        plottsgram = new QCustomPlot(page_4);
        plottsgram->setObjectName(QStringLiteral("plottsgram"));
        plottsgram->setGeometry(QRect(20, 50, 1360, 540));
        sizePolicy.setHeightForWidth(plottsgram->sizePolicy().hasHeightForWidth());
        plottsgram->setSizePolicy(sizePolicy);
        sw->addWidget(page_4);
        frameLeft3 = new QFrame(centralWidget);
        frameLeft3->setObjectName(QStringLiteral("frameLeft3"));
        frameLeft3->setGeometry(QRect(960, 130, 464, 201));
        frameLeft3->setStyleSheet(QLatin1String("background-color:#FFDE99;\n"
"border-radius: 30px;"));
        frameLeft3->setFrameShape(QFrame::StyledPanel);
        frameLeft3->setFrameShadow(QFrame::Raised);
        labelDisplacementValue = new QLabel(frameLeft3);
        labelDisplacementValue->setObjectName(QStringLiteral("labelDisplacementValue"));
        labelDisplacementValue->setGeometry(QRect(20, 90, 311, 91));
        labelDisplacementValue->setStyleSheet(QLatin1String("background-color: #FF7300;\n"
"font: 72pt \"MS Shell Dlg 2\";"));
        labelDisplacementValue->setAlignment(Qt::AlignCenter);
        btnResetEncoder = new QPushButton(frameLeft3);
        btnResetEncoder->setObjectName(QStringLiteral("btnResetEncoder"));
        btnResetEncoder->setEnabled(true);
        btnResetEncoder->setGeometry(QRect(350, 90, 101, 91));
        btnResetEncoder->setStyleSheet(QStringLiteral("border-image: url(:/zero1.png);"));
        labelDisplacementmm = new QLabel(frameLeft3);
        labelDisplacementmm->setObjectName(QStringLiteral("labelDisplacementmm"));
        labelDisplacementmm->setGeometry(QRect(0, 0, 461, 81));
        labelDisplacementmm->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 32pt \".AppleSystemUIFont\";"));
        labelDisplacementmm->setAlignment(Qt::AlignCenter);
        frameLeft4 = new QFrame(centralWidget);
        frameLeft4->setObjectName(QStringLiteral("frameLeft4"));
        frameLeft4->setGeometry(QRect(1440, 130, 464, 201));
        frameLeft4->setStyleSheet(QLatin1String("background-color:#FFDE99;\n"
"border-radius: 30px;"));
        frameLeft4->setFrameShape(QFrame::StyledPanel);
        frameLeft4->setFrameShadow(QFrame::Raised);
        labelStopWatch = new QLabel(frameLeft4);
        labelStopWatch->setObjectName(QStringLiteral("labelStopWatch"));
        labelStopWatch->setGeometry(QRect(20, 90, 431, 91));
        labelStopWatch->setStyleSheet(QLatin1String("background-color: #FF7300;\n"
"font: 72pt \"MS Shell Dlg 2\";"));
        labelStopWatch->setAlignment(Qt::AlignCenter);
        labelStopWatch->setIndent(-1);
        labelWaktuClock = new QLabel(frameLeft4);
        labelWaktuClock->setObjectName(QStringLiteral("labelWaktuClock"));
        labelWaktuClock->setGeometry(QRect(0, 0, 461, 81));
        labelWaktuClock->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font:  32pt \".AppleSystemUIFont\";"));
        labelWaktuClock->setAlignment(Qt::AlignCenter);
        frameLeft2 = new QFrame(centralWidget);
        frameLeft2->setObjectName(QStringLiteral("frameLeft2"));
        frameLeft2->setGeometry(QRect(490, 130, 455, 201));
        frameLeft2->setStyleSheet(QLatin1String("background-color:#FFDE99;\n"
"border-radius: 30px;"));
        frameLeft2->setFrameShape(QFrame::StyledPanel);
        frameLeft2->setFrameShadow(QFrame::Raised);
        labelLoadValue = new QLabel(frameLeft2);
        labelLoadValue->setObjectName(QStringLiteral("labelLoadValue"));
        labelLoadValue->setGeometry(QRect(20, 90, 301, 100));
        labelLoadValue->setStyleSheet(QLatin1String("background-color: #FF7300;\n"
"font: 72pt \"MS Shell Dlg 2\";"));
        labelLoadValue->setAlignment(Qt::AlignCenter);
        labelLoadValue->setIndent(-1);
        btnTera = new QPushButton(frameLeft2);
        btnTera->setObjectName(QStringLiteral("btnTera"));
        btnTera->setEnabled(true);
        btnTera->setGeometry(QRect(340, 90, 91, 91));
        btnTera->setStyleSheet(QStringLiteral("border-image: url(:/zero1.png);"));
        labelLoadKg = new QLabel(frameLeft2);
        labelLoadKg->setObjectName(QStringLiteral("labelLoadKg"));
        labelLoadKg->setGeometry(QRect(0, 0, 461, 81));
        labelLoadKg->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 32pt \".AppleSystemUIFont\";"));
        labelLoadKg->setAlignment(Qt::AlignCenter);
        frameLeft1 = new QFrame(centralWidget);
        frameLeft1->setObjectName(QStringLiteral("frameLeft1"));
        frameLeft1->setGeometry(QRect(10, 130, 464, 201));
        frameLeft1->setStyleSheet(QLatin1String("background-color:#FFDE99;\n"
"border-radius: 30px;"));
        frameLeft1->setFrameShape(QFrame::StyledPanel);
        frameLeft1->setFrameShadow(QFrame::Raised);
        labelTargetBebanKG = new QLabel(frameLeft1);
        labelTargetBebanKG->setObjectName(QStringLiteral("labelTargetBebanKG"));
        labelTargetBebanKG->setGeometry(QRect(0, 0, 461, 71));
        labelTargetBebanKG->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 32pt \".AppleSystemUIFont\";"));
        labelTargetBebanKG->setAlignment(Qt::AlignCenter);
        btnTargetBebanRefresh = new QPushButton(frameLeft1);
        btnTargetBebanRefresh->setObjectName(QStringLiteral("btnTargetBebanRefresh"));
        btnTargetBebanRefresh->setEnabled(true);
        btnTargetBebanRefresh->setGeometry(QRect(340, 80, 111, 101));
        btnTargetBebanRefresh->setStyleSheet(QStringLiteral("border-image: url(:/refresh1.png);"));
        labelTargetBebanVal = new QLineEdit(frameLeft1);
        labelTargetBebanVal->setObjectName(QStringLiteral("labelTargetBebanVal"));
        labelTargetBebanVal->setGeometry(QRect(30, 80, 291, 101));
        labelTargetBebanVal->setStyleSheet(QLatin1String("background-color: #FF7300;\n"
"font: 48pt \"MS Shell Dlg 2\";"));
        frame0 = new QFrame(centralWidget);
        frame0->setObjectName(QStringLiteral("frame0"));
        frame0->setGeometry(QRect(9, 0, 1901, 121));
        frame0->setStyleSheet(QLatin1String("background-color:#5FB7D4;\n"
"border-radius: 30px;"));
        frame0->setFrameShape(QFrame::StyledPanel);
        frame0->setFrameShadow(QFrame::Raised);
        btnSave = new QPushButton(frame0);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(140, 20, 101, 81));
        btnSave->setStyleSheet(QStringLiteral("border-image: url(:/save1.png);"));
        btnOpen = new QPushButton(frame0);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setGeometry(QRect(30, 20, 91, 81));
        btnOpen->setStyleSheet(QStringLiteral("border-image: url(:/open1.png);"));
        labelCurrentClock = new QLabel(frame0);
        labelCurrentClock->setObjectName(QStringLiteral("labelCurrentClock"));
        labelCurrentClock->setGeometry(QRect(1520, 40, 321, 71));
        labelCurrentClock->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 36pt \"MS Shell Dlg 2\";"));
        labelCurrentClock->setAlignment(Qt::AlignCenter);
        labelCurrentDate = new QLabel(frame0);
        labelCurrentDate->setObjectName(QStringLiteral("labelCurrentDate"));
        labelCurrentDate->setGeometry(QRect(1480, 10, 371, 31));
        labelCurrentDate->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 28pt \"MS Shell Dlg 2\";\n"
"color: black;"));
        labelCurrentDate->setAlignment(Qt::AlignCenter);
        labelJudul = new QLabel(frame0);
        labelJudul->setObjectName(QStringLiteral("labelJudul"));
        labelJudul->setGeometry(QRect(260, 0, 1341, 121));
        labelJudul->setStyleSheet(QLatin1String("background-color: transparent;\n"
"color: black;\n"
"border-radius: 30px;"));
        labelJudul->setAlignment(Qt::AlignCenter);
        btnExit = new QPushButton(frame0);
        btnExit->setObjectName(QStringLiteral("btnExit"));
        btnExit->setGeometry(QRect(1850, 0, 51, 51));
        btnExit->setStyleSheet(QLatin1String("border-image: url(:/application-exit.png);\n"
"border-radius: 30px;"));
        logSerialTextEdit = new QLabel(centralWidget);
        logSerialTextEdit->setObjectName(QStringLiteral("logSerialTextEdit"));
        logSerialTextEdit->setGeometry(QRect(10, 970, 1411, 61));
        logSerialTextEdit->setStyleSheet(QLatin1String("background-color: rgb(247, 255, 237);\n"
"font: 28pt \"MS Shell Dlg 2\";\n"
"border-radius: 30px;"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        sw->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnRefreshSerialPort->setText(QString());
        btnStart->setText(QString());
        labelLoadStr_4->setText(QApplication::translate("MainWindow", "MANUAL", nullptr));
        btnStop->setText(QString());
        btnUp->setText(QString());
        btnDown->setText(QString());
        labelLoadStr_8->setText(QApplication::translate("MainWindow", "TURUN", nullptr));
        labelLoadStr_9->setText(QApplication::translate("MainWindow", "NAIK", nullptr));
        labelBatasAtas->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt;\">BATAS ATAS</span></p></body></html>", nullptr));
        labelBatasBawah->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt;\">BATAS BAWAH</span></p></body></html>", nullptr));
        labelNama->setText(QApplication::translate("MainWindow", "NAMA PENGUJIAN", nullptr));
        teNama->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:24pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.AppleSystemUIFont';\">pengukuran_1</span></p></body></html>", nullptr));
        btnAddNewMeasurement->setText(QApplication::translate("MainWindow", "+", nullptr));
        btnTest->setText(QApplication::translate("MainWindow", "test", nullptr));
        btnSelesai->setText(QString());
        btnPause->setText(QString());
        btnResume->setText(QString());
        btnClearGraphmmGram->setText(QString());
        labelmm->setText(QApplication::translate("MainWindow", "Displacement mm", nullptr));
        labelHeadmmGram->setText(QApplication::translate("MainWindow", "Displacement (mm) vs Load (gram)", nullptr));
        btnArrowRightDL->setText(QString());
        btnArrowLeftDL->setText(QString());
        btnClearGraphtsgram->setText(QString());
        labelts->setText(QApplication::translate("MainWindow", "timestamps ms", nullptr));
        labelHeadTsGram->setText(QApplication::translate("MainWindow", "timeStamps vs Gram", nullptr));
        btnArrowRight->setText(QString());
        btnArrowLeft->setText(QString());
        labelDisplacementValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">0.0000</span></p></body></html>", nullptr));
        btnResetEncoder->setText(QString());
        labelDisplacementmm->setText(QApplication::translate("MainWindow", "Displacement (mm)", nullptr));
        labelStopWatch->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">00:00:00:00</span></p></body></html>", nullptr));
        labelWaktuClock->setText(QApplication::translate("MainWindow", "Waktu", nullptr));
        labelLoadValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">0.0000</span></p></body></html>", nullptr));
        btnTera->setText(QString());
        labelLoadKg->setText(QApplication::translate("MainWindow", "Load (kg)", nullptr));
        labelTargetBebanKG->setText(QApplication::translate("MainWindow", "Target Beban (kg)", nullptr));
        btnTargetBebanRefresh->setText(QString());
        labelTargetBebanVal->setText(QApplication::translate("MainWindow", "100", nullptr));
        btnSave->setText(QString());
        btnOpen->setText(QString());
        labelCurrentClock->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">12:23:45</span></p></body></html>", nullptr));
        labelCurrentDate->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Current Date</span></p></body></html>", nullptr));
        labelJudul->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:48pt;\">MESIN UJI TEKAN</span></p></body></html>", nullptr));
        btnExit->setText(QString());
        logSerialTextEdit->setText(QApplication::translate("MainWindow", "000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
