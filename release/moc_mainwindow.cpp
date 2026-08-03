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
    QByteArrayData data[93];
    char stringdata0[2005];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "init_port"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "initPortForce"
QT_MOC_LITERAL(4, 36, 15), // "closeSerialPort"
QT_MOC_LITERAL(5, 52, 8), // "readData"
QT_MOC_LITERAL(6, 61, 11), // "handleError"
QT_MOC_LITERAL(7, 73, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(8, 102, 5), // "error"
QT_MOC_LITERAL(9, 108, 16), // "realtimeDataSlot"
QT_MOC_LITERAL(10, 125, 5), // "value"
QT_MOC_LITERAL(11, 131, 31), // "on_btnRefreshSerialPort_clicked"
QT_MOC_LITERAL(12, 163, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(13, 182, 14), // "slotTimerClock"
QT_MOC_LITERAL(14, 197, 23), // "slotTimerProcessPayload"
QT_MOC_LITERAL(15, 221, 15), // "updateStopwatch"
QT_MOC_LITERAL(16, 237, 12), // "showPortInfo"
QT_MOC_LITERAL(17, 250, 3), // "idx"
QT_MOC_LITERAL(18, 254, 44), // "on_serialPortInfoListBox_curr..."
QT_MOC_LITERAL(19, 299, 4), // "arg1"
QT_MOC_LITERAL(20, 304, 34), // "on_serialPortInfoListBox_acti..."
QT_MOC_LITERAL(21, 339, 18), // "on_btnTera_clicked"
QT_MOC_LITERAL(22, 358, 26), // "on_btnResetEncoder_clicked"
QT_MOC_LITERAL(23, 385, 32), // "on_logSerialTextEdit_textChanged"
QT_MOC_LITERAL(24, 418, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(25, 438, 20), // "on_btnResume_clicked"
QT_MOC_LITERAL(26, 459, 30), // "on_btnClearGraphmmGram_clicked"
QT_MOC_LITERAL(27, 490, 30), // "on_btnClearGraphtsgram_clicked"
QT_MOC_LITERAL(28, 521, 19), // "on_btnStart_pressed"
QT_MOC_LITERAL(29, 541, 20), // "on_btnStart_released"
QT_MOC_LITERAL(30, 562, 31), // "on_btnRefreshSerialPort_pressed"
QT_MOC_LITERAL(31, 594, 32), // "on_btnRefreshSerialPort_released"
QT_MOC_LITERAL(32, 627, 18), // "on_btnDown_clicked"
QT_MOC_LITERAL(33, 646, 16), // "on_btnUp_clicked"
QT_MOC_LITERAL(34, 663, 18), // "on_btnTest_clicked"
QT_MOC_LITERAL(35, 682, 23), // "on_btnArrowLeft_clicked"
QT_MOC_LITERAL(36, 706, 24), // "on_btnArrowRight_clicked"
QT_MOC_LITERAL(37, 731, 26), // "on_btnArrowRightDL_clicked"
QT_MOC_LITERAL(38, 758, 25), // "on_btnArrowLeftDL_clicked"
QT_MOC_LITERAL(39, 784, 32), // "on_btnTargetBebanRefresh_pressed"
QT_MOC_LITERAL(40, 817, 33), // "on_btnTargetBebanRefresh_rele..."
QT_MOC_LITERAL(41, 851, 18), // "on_btnTera_pressed"
QT_MOC_LITERAL(42, 870, 19), // "on_btnTera_released"
QT_MOC_LITERAL(43, 890, 26), // "on_btnResetEncoder_pressed"
QT_MOC_LITERAL(44, 917, 27), // "on_btnResetEncoder_released"
QT_MOC_LITERAL(45, 945, 18), // "on_btnDown_pressed"
QT_MOC_LITERAL(46, 964, 19), // "on_btnDown_released"
QT_MOC_LITERAL(47, 984, 16), // "on_btnUp_pressed"
QT_MOC_LITERAL(48, 1001, 17), // "on_btnUp_released"
QT_MOC_LITERAL(49, 1019, 18), // "on_btnStop_pressed"
QT_MOC_LITERAL(50, 1038, 19), // "on_btnStop_released"
QT_MOC_LITERAL(51, 1058, 18), // "on_btnOpen_pressed"
QT_MOC_LITERAL(52, 1077, 19), // "on_btnOpen_released"
QT_MOC_LITERAL(53, 1097, 18), // "on_btnSave_pressed"
QT_MOC_LITERAL(54, 1116, 19), // "on_btnSave_released"
QT_MOC_LITERAL(55, 1136, 26), // "on_btnArrowRightDL_pressed"
QT_MOC_LITERAL(56, 1163, 27), // "on_btnArrowRightDL_released"
QT_MOC_LITERAL(57, 1191, 25), // "on_btnArrowLeftDL_pressed"
QT_MOC_LITERAL(58, 1217, 26), // "on_btnArrowLeftDL_released"
QT_MOC_LITERAL(59, 1244, 24), // "on_btnArrowRight_pressed"
QT_MOC_LITERAL(60, 1269, 25), // "on_btnArrowRight_released"
QT_MOC_LITERAL(61, 1295, 23), // "on_btnArrowLeft_pressed"
QT_MOC_LITERAL(62, 1319, 24), // "on_btnArrowLeft_released"
QT_MOC_LITERAL(63, 1344, 20), // "on_btnResume_pressed"
QT_MOC_LITERAL(64, 1365, 21), // "on_btnResume_released"
QT_MOC_LITERAL(65, 1387, 19), // "on_btnPause_pressed"
QT_MOC_LITERAL(66, 1407, 20), // "on_btnPause_released"
QT_MOC_LITERAL(67, 1428, 21), // "on_btnSelesai_pressed"
QT_MOC_LITERAL(68, 1450, 22), // "on_btnSelesai_released"
QT_MOC_LITERAL(69, 1473, 31), // "on_btnAddNewMeasurement_pressed"
QT_MOC_LITERAL(70, 1505, 32), // "on_btnAddNewMeasurement_released"
QT_MOC_LITERAL(71, 1538, 32), // "on_btnTargetBebanRefresh_clicked"
QT_MOC_LITERAL(72, 1571, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(73, 1590, 21), // "on_btnSelesai_clicked"
QT_MOC_LITERAL(74, 1612, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(75, 1632, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(76, 1651, 18), // "on_btnExit_clicked"
QT_MOC_LITERAL(77, 1670, 31), // "on_btnAddNewMeasurement_clicked"
QT_MOC_LITERAL(78, 1702, 20), // "horzScrollBarChanged"
QT_MOC_LITERAL(79, 1723, 20), // "vertScrollBarChanged"
QT_MOC_LITERAL(80, 1744, 12), // "xAxisChanged"
QT_MOC_LITERAL(81, 1757, 8), // "QCPRange"
QT_MOC_LITERAL(82, 1766, 5), // "range"
QT_MOC_LITERAL(83, 1772, 12), // "yAxisChanged"
QT_MOC_LITERAL(84, 1785, 21), // "horzScrollBar2Changed"
QT_MOC_LITERAL(85, 1807, 21), // "vertScrollBar2Changed"
QT_MOC_LITERAL(86, 1829, 13), // "xAxis2Changed"
QT_MOC_LITERAL(87, 1843, 13), // "yAxis2Changed"
QT_MOC_LITERAL(88, 1857, 25), // "onbtnYes_msgLogoutClicked"
QT_MOC_LITERAL(89, 1883, 24), // "onbtnNo_msgLogoutClicked"
QT_MOC_LITERAL(90, 1908, 26), // "onbtnYes_msgEndUkurClicked"
QT_MOC_LITERAL(91, 1935, 25), // "onbtnNo_msgEndUkurClicked"
QT_MOC_LITERAL(92, 1961, 43) // "on_serialPortInfoListBox_curr..."

    },
    "MainWindow\0init_port\0\0initPortForce\0"
    "closeSerialPort\0readData\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "realtimeDataSlot\0value\0"
    "on_btnRefreshSerialPort_clicked\0"
    "on_btnStop_clicked\0slotTimerClock\0"
    "slotTimerProcessPayload\0updateStopwatch\0"
    "showPortInfo\0idx\0"
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
      84,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  434,    2, 0x08 /* Private */,
       3,    0,  435,    2, 0x08 /* Private */,
       4,    0,  436,    2, 0x08 /* Private */,
       5,    0,  437,    2, 0x08 /* Private */,
       6,    1,  438,    2, 0x08 /* Private */,
       9,    1,  441,    2, 0x08 /* Private */,
      11,    0,  444,    2, 0x08 /* Private */,
      12,    0,  445,    2, 0x08 /* Private */,
      13,    0,  446,    2, 0x08 /* Private */,
      14,    0,  447,    2, 0x08 /* Private */,
      15,    0,  448,    2, 0x08 /* Private */,
      16,    1,  449,    2, 0x08 /* Private */,
      18,    1,  452,    2, 0x08 /* Private */,
      20,    1,  455,    2, 0x08 /* Private */,
      21,    0,  458,    2, 0x08 /* Private */,
      22,    0,  459,    2, 0x08 /* Private */,
      23,    0,  460,    2, 0x08 /* Private */,
      24,    0,  461,    2, 0x08 /* Private */,
      25,    0,  462,    2, 0x08 /* Private */,
      26,    0,  463,    2, 0x08 /* Private */,
      27,    0,  464,    2, 0x08 /* Private */,
      28,    0,  465,    2, 0x08 /* Private */,
      29,    0,  466,    2, 0x08 /* Private */,
      30,    0,  467,    2, 0x08 /* Private */,
      31,    0,  468,    2, 0x08 /* Private */,
      32,    0,  469,    2, 0x08 /* Private */,
      33,    0,  470,    2, 0x08 /* Private */,
      34,    0,  471,    2, 0x08 /* Private */,
      35,    0,  472,    2, 0x08 /* Private */,
      36,    0,  473,    2, 0x08 /* Private */,
      37,    0,  474,    2, 0x08 /* Private */,
      38,    0,  475,    2, 0x08 /* Private */,
      39,    0,  476,    2, 0x08 /* Private */,
      40,    0,  477,    2, 0x08 /* Private */,
      41,    0,  478,    2, 0x08 /* Private */,
      42,    0,  479,    2, 0x08 /* Private */,
      43,    0,  480,    2, 0x08 /* Private */,
      44,    0,  481,    2, 0x08 /* Private */,
      45,    0,  482,    2, 0x08 /* Private */,
      46,    0,  483,    2, 0x08 /* Private */,
      47,    0,  484,    2, 0x08 /* Private */,
      48,    0,  485,    2, 0x08 /* Private */,
      49,    0,  486,    2, 0x08 /* Private */,
      50,    0,  487,    2, 0x08 /* Private */,
      51,    0,  488,    2, 0x08 /* Private */,
      52,    0,  489,    2, 0x08 /* Private */,
      53,    0,  490,    2, 0x08 /* Private */,
      54,    0,  491,    2, 0x08 /* Private */,
      55,    0,  492,    2, 0x08 /* Private */,
      56,    0,  493,    2, 0x08 /* Private */,
      57,    0,  494,    2, 0x08 /* Private */,
      58,    0,  495,    2, 0x08 /* Private */,
      59,    0,  496,    2, 0x08 /* Private */,
      60,    0,  497,    2, 0x08 /* Private */,
      61,    0,  498,    2, 0x08 /* Private */,
      62,    0,  499,    2, 0x08 /* Private */,
      63,    0,  500,    2, 0x08 /* Private */,
      64,    0,  501,    2, 0x08 /* Private */,
      65,    0,  502,    2, 0x08 /* Private */,
      66,    0,  503,    2, 0x08 /* Private */,
      67,    0,  504,    2, 0x08 /* Private */,
      68,    0,  505,    2, 0x08 /* Private */,
      69,    0,  506,    2, 0x08 /* Private */,
      70,    0,  507,    2, 0x08 /* Private */,
      71,    0,  508,    2, 0x08 /* Private */,
      72,    0,  509,    2, 0x08 /* Private */,
      73,    0,  510,    2, 0x08 /* Private */,
      74,    0,  511,    2, 0x08 /* Private */,
      75,    0,  512,    2, 0x08 /* Private */,
      76,    0,  513,    2, 0x08 /* Private */,
      77,    0,  514,    2, 0x08 /* Private */,
      78,    1,  515,    2, 0x08 /* Private */,
      79,    1,  518,    2, 0x08 /* Private */,
      80,    1,  521,    2, 0x08 /* Private */,
      83,    1,  524,    2, 0x08 /* Private */,
      84,    1,  527,    2, 0x08 /* Private */,
      85,    1,  530,    2, 0x08 /* Private */,
      86,    1,  533,    2, 0x08 /* Private */,
      87,    1,  536,    2, 0x08 /* Private */,
      88,    0,  539,    2, 0x08 /* Private */,
      89,    0,  540,    2, 0x08 /* Private */,
      90,    0,  541,    2, 0x08 /* Private */,
      91,    0,  542,    2, 0x08 /* Private */,
      92,    1,  543,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString,   19,
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
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 81,   82,
    QMetaType::Void, 0x80000000 | 81,   82,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 81,   82,
    QMetaType::Void, 0x80000000 | 81,   82,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->init_port();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->initPortForce();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->closeSerialPort(); break;
        case 3: _t->readData(); break;
        case 4: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 5: _t->realtimeDataSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_btnRefreshSerialPort_clicked(); break;
        case 7: _t->on_btnStop_clicked(); break;
        case 8: _t->slotTimerClock(); break;
        case 9: _t->slotTimerProcessPayload(); break;
        case 10: _t->updateStopwatch(); break;
        case 11: _t->showPortInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_serialPortInfoListBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_serialPortInfoListBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_btnTera_clicked(); break;
        case 15: _t->on_btnResetEncoder_clicked(); break;
        case 16: _t->on_logSerialTextEdit_textChanged(); break;
        case 17: _t->on_btnStart_clicked(); break;
        case 18: _t->on_btnResume_clicked(); break;
        case 19: _t->on_btnClearGraphmmGram_clicked(); break;
        case 20: _t->on_btnClearGraphtsgram_clicked(); break;
        case 21: _t->on_btnStart_pressed(); break;
        case 22: _t->on_btnStart_released(); break;
        case 23: _t->on_btnRefreshSerialPort_pressed(); break;
        case 24: _t->on_btnRefreshSerialPort_released(); break;
        case 25: _t->on_btnDown_clicked(); break;
        case 26: _t->on_btnUp_clicked(); break;
        case 27: _t->on_btnTest_clicked(); break;
        case 28: _t->on_btnArrowLeft_clicked(); break;
        case 29: _t->on_btnArrowRight_clicked(); break;
        case 30: _t->on_btnArrowRightDL_clicked(); break;
        case 31: _t->on_btnArrowLeftDL_clicked(); break;
        case 32: _t->on_btnTargetBebanRefresh_pressed(); break;
        case 33: _t->on_btnTargetBebanRefresh_released(); break;
        case 34: _t->on_btnTera_pressed(); break;
        case 35: _t->on_btnTera_released(); break;
        case 36: _t->on_btnResetEncoder_pressed(); break;
        case 37: _t->on_btnResetEncoder_released(); break;
        case 38: _t->on_btnDown_pressed(); break;
        case 39: _t->on_btnDown_released(); break;
        case 40: _t->on_btnUp_pressed(); break;
        case 41: _t->on_btnUp_released(); break;
        case 42: _t->on_btnStop_pressed(); break;
        case 43: _t->on_btnStop_released(); break;
        case 44: _t->on_btnOpen_pressed(); break;
        case 45: _t->on_btnOpen_released(); break;
        case 46: _t->on_btnSave_pressed(); break;
        case 47: _t->on_btnSave_released(); break;
        case 48: _t->on_btnArrowRightDL_pressed(); break;
        case 49: _t->on_btnArrowRightDL_released(); break;
        case 50: _t->on_btnArrowLeftDL_pressed(); break;
        case 51: _t->on_btnArrowLeftDL_released(); break;
        case 52: _t->on_btnArrowRight_pressed(); break;
        case 53: _t->on_btnArrowRight_released(); break;
        case 54: _t->on_btnArrowLeft_pressed(); break;
        case 55: _t->on_btnArrowLeft_released(); break;
        case 56: _t->on_btnResume_pressed(); break;
        case 57: _t->on_btnResume_released(); break;
        case 58: _t->on_btnPause_pressed(); break;
        case 59: _t->on_btnPause_released(); break;
        case 60: _t->on_btnSelesai_pressed(); break;
        case 61: _t->on_btnSelesai_released(); break;
        case 62: _t->on_btnAddNewMeasurement_pressed(); break;
        case 63: _t->on_btnAddNewMeasurement_released(); break;
        case 64: _t->on_btnTargetBebanRefresh_clicked(); break;
        case 65: _t->on_btnOpen_clicked(); break;
        case 66: _t->on_btnSelesai_clicked(); break;
        case 67: _t->on_btnPause_clicked(); break;
        case 68: _t->on_btnSave_clicked(); break;
        case 69: _t->on_btnExit_clicked(); break;
        case 70: _t->on_btnAddNewMeasurement_clicked(); break;
        case 71: _t->horzScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 72: _t->vertScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->xAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 74: _t->yAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 75: _t->horzScrollBar2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->vertScrollBar2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->xAxis2Changed((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 78: _t->yAxis2Changed((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 79: _t->onbtnYes_msgLogoutClicked(); break;
        case 80: _t->onbtnNo_msgLogoutClicked(); break;
        case 81: _t->onbtnYes_msgEndUkurClicked(); break;
        case 82: _t->onbtnNo_msgEndUkurClicked(); break;
        case 83: _t->on_serialPortInfoListBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 84)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 84;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 84)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 84;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
