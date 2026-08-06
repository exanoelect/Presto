/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[98];
    char stringdata0[2068];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "serialDataParsed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "DataTerima"
QT_MOC_LITERAL(4, 40, 4), // "data"
QT_MOC_LITERAL(5, 45, 18), // "queueDataAvailable"
QT_MOC_LITERAL(6, 64, 9), // "init_port"
QT_MOC_LITERAL(7, 74, 13), // "initPortForce"
QT_MOC_LITERAL(8, 88, 15), // "closeSerialPort"
QT_MOC_LITERAL(9, 104, 8), // "readData"
QT_MOC_LITERAL(10, 113, 17), // "enqueueParsedData"
QT_MOC_LITERAL(11, 131, 16), // "processDataQueue"
QT_MOC_LITERAL(12, 148, 11), // "handleError"
QT_MOC_LITERAL(13, 160, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(14, 189, 5), // "error"
QT_MOC_LITERAL(15, 195, 16), // "realtimeDataSlot"
QT_MOC_LITERAL(16, 212, 5), // "value"
QT_MOC_LITERAL(17, 218, 31), // "on_btnRefreshSerialPort_clicked"
QT_MOC_LITERAL(18, 250, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(19, 269, 14), // "slotTimerClock"
QT_MOC_LITERAL(20, 284, 15), // "updateStopwatch"
QT_MOC_LITERAL(21, 300, 12), // "showPortInfo"
QT_MOC_LITERAL(22, 313, 3), // "idx"
QT_MOC_LITERAL(23, 317, 44), // "on_serialPortInfoListBox_curr..."
QT_MOC_LITERAL(24, 362, 4), // "arg1"
QT_MOC_LITERAL(25, 367, 34), // "on_serialPortInfoListBox_acti..."
QT_MOC_LITERAL(26, 402, 18), // "on_btnTera_clicked"
QT_MOC_LITERAL(27, 421, 26), // "on_btnResetEncoder_clicked"
QT_MOC_LITERAL(28, 448, 32), // "on_logSerialTextEdit_textChanged"
QT_MOC_LITERAL(29, 481, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(30, 501, 20), // "on_btnResume_clicked"
QT_MOC_LITERAL(31, 522, 30), // "on_btnClearGraphmmGram_clicked"
QT_MOC_LITERAL(32, 553, 30), // "on_btnClearGraphtsgram_clicked"
QT_MOC_LITERAL(33, 584, 19), // "on_btnStart_pressed"
QT_MOC_LITERAL(34, 604, 20), // "on_btnStart_released"
QT_MOC_LITERAL(35, 625, 31), // "on_btnRefreshSerialPort_pressed"
QT_MOC_LITERAL(36, 657, 32), // "on_btnRefreshSerialPort_released"
QT_MOC_LITERAL(37, 690, 18), // "on_btnDown_clicked"
QT_MOC_LITERAL(38, 709, 16), // "on_btnUp_clicked"
QT_MOC_LITERAL(39, 726, 18), // "on_btnTest_clicked"
QT_MOC_LITERAL(40, 745, 23), // "on_btnArrowLeft_clicked"
QT_MOC_LITERAL(41, 769, 24), // "on_btnArrowRight_clicked"
QT_MOC_LITERAL(42, 794, 26), // "on_btnArrowRightDL_clicked"
QT_MOC_LITERAL(43, 821, 25), // "on_btnArrowLeftDL_clicked"
QT_MOC_LITERAL(44, 847, 32), // "on_btnTargetBebanRefresh_pressed"
QT_MOC_LITERAL(45, 880, 33), // "on_btnTargetBebanRefresh_rele..."
QT_MOC_LITERAL(46, 914, 18), // "on_btnTera_pressed"
QT_MOC_LITERAL(47, 933, 19), // "on_btnTera_released"
QT_MOC_LITERAL(48, 953, 26), // "on_btnResetEncoder_pressed"
QT_MOC_LITERAL(49, 980, 27), // "on_btnResetEncoder_released"
QT_MOC_LITERAL(50, 1008, 18), // "on_btnDown_pressed"
QT_MOC_LITERAL(51, 1027, 19), // "on_btnDown_released"
QT_MOC_LITERAL(52, 1047, 16), // "on_btnUp_pressed"
QT_MOC_LITERAL(53, 1064, 17), // "on_btnUp_released"
QT_MOC_LITERAL(54, 1082, 18), // "on_btnStop_pressed"
QT_MOC_LITERAL(55, 1101, 19), // "on_btnStop_released"
QT_MOC_LITERAL(56, 1121, 18), // "on_btnOpen_pressed"
QT_MOC_LITERAL(57, 1140, 19), // "on_btnOpen_released"
QT_MOC_LITERAL(58, 1160, 18), // "on_btnSave_pressed"
QT_MOC_LITERAL(59, 1179, 19), // "on_btnSave_released"
QT_MOC_LITERAL(60, 1199, 26), // "on_btnArrowRightDL_pressed"
QT_MOC_LITERAL(61, 1226, 27), // "on_btnArrowRightDL_released"
QT_MOC_LITERAL(62, 1254, 25), // "on_btnArrowLeftDL_pressed"
QT_MOC_LITERAL(63, 1280, 26), // "on_btnArrowLeftDL_released"
QT_MOC_LITERAL(64, 1307, 24), // "on_btnArrowRight_pressed"
QT_MOC_LITERAL(65, 1332, 25), // "on_btnArrowRight_released"
QT_MOC_LITERAL(66, 1358, 23), // "on_btnArrowLeft_pressed"
QT_MOC_LITERAL(67, 1382, 24), // "on_btnArrowLeft_released"
QT_MOC_LITERAL(68, 1407, 20), // "on_btnResume_pressed"
QT_MOC_LITERAL(69, 1428, 21), // "on_btnResume_released"
QT_MOC_LITERAL(70, 1450, 19), // "on_btnPause_pressed"
QT_MOC_LITERAL(71, 1470, 20), // "on_btnPause_released"
QT_MOC_LITERAL(72, 1491, 21), // "on_btnSelesai_pressed"
QT_MOC_LITERAL(73, 1513, 22), // "on_btnSelesai_released"
QT_MOC_LITERAL(74, 1536, 31), // "on_btnAddNewMeasurement_pressed"
QT_MOC_LITERAL(75, 1568, 32), // "on_btnAddNewMeasurement_released"
QT_MOC_LITERAL(76, 1601, 32), // "on_btnTargetBebanRefresh_clicked"
QT_MOC_LITERAL(77, 1634, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(78, 1653, 21), // "on_btnSelesai_clicked"
QT_MOC_LITERAL(79, 1675, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(80, 1695, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(81, 1714, 18), // "on_btnExit_clicked"
QT_MOC_LITERAL(82, 1733, 31), // "on_btnAddNewMeasurement_clicked"
QT_MOC_LITERAL(83, 1765, 20), // "horzScrollBarChanged"
QT_MOC_LITERAL(84, 1786, 20), // "vertScrollBarChanged"
QT_MOC_LITERAL(85, 1807, 12), // "xAxisChanged"
QT_MOC_LITERAL(86, 1820, 8), // "QCPRange"
QT_MOC_LITERAL(87, 1829, 5), // "range"
QT_MOC_LITERAL(88, 1835, 12), // "yAxisChanged"
QT_MOC_LITERAL(89, 1848, 21), // "horzScrollBar2Changed"
QT_MOC_LITERAL(90, 1870, 21), // "vertScrollBar2Changed"
QT_MOC_LITERAL(91, 1892, 13), // "xAxis2Changed"
QT_MOC_LITERAL(92, 1906, 13), // "yAxis2Changed"
QT_MOC_LITERAL(93, 1920, 25), // "onbtnYes_msgLogoutClicked"
QT_MOC_LITERAL(94, 1946, 24), // "onbtnNo_msgLogoutClicked"
QT_MOC_LITERAL(95, 1971, 26), // "onbtnYes_msgEndUkurClicked"
QT_MOC_LITERAL(96, 1998, 25), // "onbtnNo_msgEndUkurClicked"
QT_MOC_LITERAL(97, 2024, 43) // "on_serialPortInfoListBox_curr..."

    },
    "MainWindow\0serialDataParsed\0\0DataTerima\0"
    "data\0queueDataAvailable\0init_port\0"
    "initPortForce\0closeSerialPort\0readData\0"
    "enqueueParsedData\0processDataQueue\0"
    "handleError\0QSerialPort::SerialPortError\0"
    "error\0realtimeDataSlot\0value\0"
    "on_btnRefreshSerialPort_clicked\0"
    "on_btnStop_clicked\0slotTimerClock\0"
    "updateStopwatch\0showPortInfo\0idx\0"
    "on_serialPortInfoListBox_currentIndexChanged\0"
    "arg1\0on_serialPortInfoListBox_activated\0"
    "on_btnTera_clicked\0on_btnResetEncoder_clicked\0"
    "on_logSerialTextEdit_textChanged\0"
    "on_btnStart_clicked\0on_btnResume_clicked\0"
    "on_btnClearGraphmmGram_clicked\0"
    "on_btnClearGraphtsgram_clicked\0"
    "on_btnStart_pressed\0on_btnStart_released\0"
    "on_btnRefreshSerialPort_pressed\0"
    "on_btnRefreshSerialPort_released\0"
    "on_btnDown_clicked\0on_btnUp_clicked\0"
    "on_btnTest_clicked\0on_btnArrowLeft_clicked\0"
    "on_btnArrowRight_clicked\0"
    "on_btnArrowRightDL_clicked\0"
    "on_btnArrowLeftDL_clicked\0"
    "on_btnTargetBebanRefresh_pressed\0"
    "on_btnTargetBebanRefresh_released\0"
    "on_btnTera_pressed\0on_btnTera_released\0"
    "on_btnResetEncoder_pressed\0"
    "on_btnResetEncoder_released\0"
    "on_btnDown_pressed\0on_btnDown_released\0"
    "on_btnUp_pressed\0on_btnUp_released\0"
    "on_btnStop_pressed\0on_btnStop_released\0"
    "on_btnOpen_pressed\0on_btnOpen_released\0"
    "on_btnSave_pressed\0on_btnSave_released\0"
    "on_btnArrowRightDL_pressed\0"
    "on_btnArrowRightDL_released\0"
    "on_btnArrowLeftDL_pressed\0"
    "on_btnArrowLeftDL_released\0"
    "on_btnArrowRight_pressed\0"
    "on_btnArrowRight_released\0"
    "on_btnArrowLeft_pressed\0"
    "on_btnArrowLeft_released\0on_btnResume_pressed\0"
    "on_btnResume_released\0on_btnPause_pressed\0"
    "on_btnPause_released\0on_btnSelesai_pressed\0"
    "on_btnSelesai_released\0"
    "on_btnAddNewMeasurement_pressed\0"
    "on_btnAddNewMeasurement_released\0"
    "on_btnTargetBebanRefresh_clicked\0"
    "on_btnOpen_clicked\0on_btnSelesai_clicked\0"
    "on_btnPause_clicked\0on_btnSave_clicked\0"
    "on_btnExit_clicked\0on_btnAddNewMeasurement_clicked\0"
    "horzScrollBarChanged\0vertScrollBarChanged\0"
    "xAxisChanged\0QCPRange\0range\0yAxisChanged\0"
    "horzScrollBar2Changed\0vertScrollBar2Changed\0"
    "xAxis2Changed\0yAxis2Changed\0"
    "onbtnYes_msgLogoutClicked\0"
    "onbtnNo_msgLogoutClicked\0"
    "onbtnYes_msgEndUkurClicked\0"
    "onbtnNo_msgEndUkurClicked\0"
    "on_serialPortInfoListBox_currentTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      87,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  449,    2, 0x06 /* Public */,
       5,    0,  452,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  453,    2, 0x08 /* Private */,
       7,    0,  454,    2, 0x08 /* Private */,
       8,    0,  455,    2, 0x08 /* Private */,
       9,    0,  456,    2, 0x08 /* Private */,
      10,    1,  457,    2, 0x08 /* Private */,
      11,    0,  460,    2, 0x08 /* Private */,
      12,    1,  461,    2, 0x08 /* Private */,
      15,    1,  464,    2, 0x08 /* Private */,
      17,    0,  467,    2, 0x08 /* Private */,
      18,    0,  468,    2, 0x08 /* Private */,
      19,    0,  469,    2, 0x08 /* Private */,
      20,    0,  470,    2, 0x08 /* Private */,
      21,    1,  471,    2, 0x08 /* Private */,
      23,    1,  474,    2, 0x08 /* Private */,
      25,    1,  477,    2, 0x08 /* Private */,
      26,    0,  480,    2, 0x08 /* Private */,
      27,    0,  481,    2, 0x08 /* Private */,
      28,    0,  482,    2, 0x08 /* Private */,
      29,    0,  483,    2, 0x08 /* Private */,
      30,    0,  484,    2, 0x08 /* Private */,
      31,    0,  485,    2, 0x08 /* Private */,
      32,    0,  486,    2, 0x08 /* Private */,
      33,    0,  487,    2, 0x08 /* Private */,
      34,    0,  488,    2, 0x08 /* Private */,
      35,    0,  489,    2, 0x08 /* Private */,
      36,    0,  490,    2, 0x08 /* Private */,
      37,    0,  491,    2, 0x08 /* Private */,
      38,    0,  492,    2, 0x08 /* Private */,
      39,    0,  493,    2, 0x08 /* Private */,
      40,    0,  494,    2, 0x08 /* Private */,
      41,    0,  495,    2, 0x08 /* Private */,
      42,    0,  496,    2, 0x08 /* Private */,
      43,    0,  497,    2, 0x08 /* Private */,
      44,    0,  498,    2, 0x08 /* Private */,
      45,    0,  499,    2, 0x08 /* Private */,
      46,    0,  500,    2, 0x08 /* Private */,
      47,    0,  501,    2, 0x08 /* Private */,
      48,    0,  502,    2, 0x08 /* Private */,
      49,    0,  503,    2, 0x08 /* Private */,
      50,    0,  504,    2, 0x08 /* Private */,
      51,    0,  505,    2, 0x08 /* Private */,
      52,    0,  506,    2, 0x08 /* Private */,
      53,    0,  507,    2, 0x08 /* Private */,
      54,    0,  508,    2, 0x08 /* Private */,
      55,    0,  509,    2, 0x08 /* Private */,
      56,    0,  510,    2, 0x08 /* Private */,
      57,    0,  511,    2, 0x08 /* Private */,
      58,    0,  512,    2, 0x08 /* Private */,
      59,    0,  513,    2, 0x08 /* Private */,
      60,    0,  514,    2, 0x08 /* Private */,
      61,    0,  515,    2, 0x08 /* Private */,
      62,    0,  516,    2, 0x08 /* Private */,
      63,    0,  517,    2, 0x08 /* Private */,
      64,    0,  518,    2, 0x08 /* Private */,
      65,    0,  519,    2, 0x08 /* Private */,
      66,    0,  520,    2, 0x08 /* Private */,
      67,    0,  521,    2, 0x08 /* Private */,
      68,    0,  522,    2, 0x08 /* Private */,
      69,    0,  523,    2, 0x08 /* Private */,
      70,    0,  524,    2, 0x08 /* Private */,
      71,    0,  525,    2, 0x08 /* Private */,
      72,    0,  526,    2, 0x08 /* Private */,
      73,    0,  527,    2, 0x08 /* Private */,
      74,    0,  528,    2, 0x08 /* Private */,
      75,    0,  529,    2, 0x08 /* Private */,
      76,    0,  530,    2, 0x08 /* Private */,
      77,    0,  531,    2, 0x08 /* Private */,
      78,    0,  532,    2, 0x08 /* Private */,
      79,    0,  533,    2, 0x08 /* Private */,
      80,    0,  534,    2, 0x08 /* Private */,
      81,    0,  535,    2, 0x08 /* Private */,
      82,    0,  536,    2, 0x08 /* Private */,
      83,    1,  537,    2, 0x08 /* Private */,
      84,    1,  540,    2, 0x08 /* Private */,
      85,    1,  543,    2, 0x08 /* Private */,
      88,    1,  546,    2, 0x08 /* Private */,
      89,    1,  549,    2, 0x08 /* Private */,
      90,    1,  552,    2, 0x08 /* Private */,
      91,    1,  555,    2, 0x08 /* Private */,
      92,    1,  558,    2, 0x08 /* Private */,
      93,    0,  561,    2, 0x08 /* Private */,
      94,    0,  562,    2, 0x08 /* Private */,
      95,    0,  563,    2, 0x08 /* Private */,
      96,    0,  564,    2, 0x08 /* Private */,
      97,    1,  565,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 86,   87,
    QMetaType::Void, 0x80000000 | 86,   87,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 86,   87,
    QMetaType::Void, 0x80000000 | 86,   87,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serialDataParsed((*reinterpret_cast< const DataTerima(*)>(_a[1]))); break;
        case 1: _t->queueDataAvailable(); break;
        case 2: { bool _r = _t->init_port();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->initPortForce();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->closeSerialPort(); break;
        case 5: _t->readData(); break;
        case 6: _t->enqueueParsedData((*reinterpret_cast< const DataTerima(*)>(_a[1]))); break;
        case 7: _t->processDataQueue(); break;
        case 8: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 9: _t->realtimeDataSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_btnRefreshSerialPort_clicked(); break;
        case 11: _t->on_btnStop_clicked(); break;
        case 12: _t->slotTimerClock(); break;
        case 13: _t->updateStopwatch(); break;
        case 14: _t->showPortInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_serialPortInfoListBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->on_serialPortInfoListBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->on_btnTera_clicked(); break;
        case 18: _t->on_btnResetEncoder_clicked(); break;
        case 19: _t->on_logSerialTextEdit_textChanged(); break;
        case 20: _t->on_btnStart_clicked(); break;
        case 21: _t->on_btnResume_clicked(); break;
        case 22: _t->on_btnClearGraphmmGram_clicked(); break;
        case 23: _t->on_btnClearGraphtsgram_clicked(); break;
        case 24: _t->on_btnStart_pressed(); break;
        case 25: _t->on_btnStart_released(); break;
        case 26: _t->on_btnRefreshSerialPort_pressed(); break;
        case 27: _t->on_btnRefreshSerialPort_released(); break;
        case 28: _t->on_btnDown_clicked(); break;
        case 29: _t->on_btnUp_clicked(); break;
        case 30: _t->on_btnTest_clicked(); break;
        case 31: _t->on_btnArrowLeft_clicked(); break;
        case 32: _t->on_btnArrowRight_clicked(); break;
        case 33: _t->on_btnArrowRightDL_clicked(); break;
        case 34: _t->on_btnArrowLeftDL_clicked(); break;
        case 35: _t->on_btnTargetBebanRefresh_pressed(); break;
        case 36: _t->on_btnTargetBebanRefresh_released(); break;
        case 37: _t->on_btnTera_pressed(); break;
        case 38: _t->on_btnTera_released(); break;
        case 39: _t->on_btnResetEncoder_pressed(); break;
        case 40: _t->on_btnResetEncoder_released(); break;
        case 41: _t->on_btnDown_pressed(); break;
        case 42: _t->on_btnDown_released(); break;
        case 43: _t->on_btnUp_pressed(); break;
        case 44: _t->on_btnUp_released(); break;
        case 45: _t->on_btnStop_pressed(); break;
        case 46: _t->on_btnStop_released(); break;
        case 47: _t->on_btnOpen_pressed(); break;
        case 48: _t->on_btnOpen_released(); break;
        case 49: _t->on_btnSave_pressed(); break;
        case 50: _t->on_btnSave_released(); break;
        case 51: _t->on_btnArrowRightDL_pressed(); break;
        case 52: _t->on_btnArrowRightDL_released(); break;
        case 53: _t->on_btnArrowLeftDL_pressed(); break;
        case 54: _t->on_btnArrowLeftDL_released(); break;
        case 55: _t->on_btnArrowRight_pressed(); break;
        case 56: _t->on_btnArrowRight_released(); break;
        case 57: _t->on_btnArrowLeft_pressed(); break;
        case 58: _t->on_btnArrowLeft_released(); break;
        case 59: _t->on_btnResume_pressed(); break;
        case 60: _t->on_btnResume_released(); break;
        case 61: _t->on_btnPause_pressed(); break;
        case 62: _t->on_btnPause_released(); break;
        case 63: _t->on_btnSelesai_pressed(); break;
        case 64: _t->on_btnSelesai_released(); break;
        case 65: _t->on_btnAddNewMeasurement_pressed(); break;
        case 66: _t->on_btnAddNewMeasurement_released(); break;
        case 67: _t->on_btnTargetBebanRefresh_clicked(); break;
        case 68: _t->on_btnOpen_clicked(); break;
        case 69: _t->on_btnSelesai_clicked(); break;
        case 70: _t->on_btnPause_clicked(); break;
        case 71: _t->on_btnSave_clicked(); break;
        case 72: _t->on_btnExit_clicked(); break;
        case 73: _t->on_btnAddNewMeasurement_clicked(); break;
        case 74: _t->horzScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 75: _t->vertScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->xAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 77: _t->yAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 78: _t->horzScrollBar2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->vertScrollBar2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 80: _t->xAxis2Changed((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 81: _t->yAxis2Changed((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 82: _t->onbtnYes_msgLogoutClicked(); break;
        case 83: _t->onbtnNo_msgLogoutClicked(); break;
        case 84: _t->onbtnYes_msgEndUkurClicked(); break;
        case 85: _t->onbtnNo_msgEndUkurClicked(); break;
        case 86: _t->on_serialPortInfoListBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataTerima >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataTerima >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const DataTerima & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::serialDataParsed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::queueDataAvailable)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 87)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 87;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 87)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 87;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::serialDataParsed(const DataTerima & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::queueDataAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
