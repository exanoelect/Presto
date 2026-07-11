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
    QByteArrayData data[65];
    char stringdata0[1408];
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
QT_MOC_LITERAL(3, 22, 15), // "closeSerialPort"
QT_MOC_LITERAL(4, 38, 8), // "readData"
QT_MOC_LITERAL(5, 47, 11), // "handleError"
QT_MOC_LITERAL(6, 59, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(7, 88, 5), // "error"
QT_MOC_LITERAL(8, 94, 16), // "realtimeDataSlot"
QT_MOC_LITERAL(9, 111, 5), // "value"
QT_MOC_LITERAL(10, 117, 31), // "on_btnRefreshSerialPort_clicked"
QT_MOC_LITERAL(11, 149, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(12, 168, 14), // "slotTimerClock"
QT_MOC_LITERAL(13, 183, 23), // "slotTimerProcessPayload"
QT_MOC_LITERAL(14, 207, 15), // "updateStopwatch"
QT_MOC_LITERAL(15, 223, 12), // "showPortInfo"
QT_MOC_LITERAL(16, 236, 3), // "idx"
QT_MOC_LITERAL(17, 240, 44), // "on_serialPortInfoListBox_curr..."
QT_MOC_LITERAL(18, 285, 4), // "arg1"
QT_MOC_LITERAL(19, 290, 34), // "on_serialPortInfoListBox_acti..."
QT_MOC_LITERAL(20, 325, 18), // "on_btnTera_clicked"
QT_MOC_LITERAL(21, 344, 26), // "on_btnResetEncoder_clicked"
QT_MOC_LITERAL(22, 371, 32), // "on_logSerialTextEdit_textChanged"
QT_MOC_LITERAL(23, 404, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(24, 424, 30), // "on_btnClearGraphmmGram_clicked"
QT_MOC_LITERAL(25, 455, 30), // "on_btnClearGraphtsgram_clicked"
QT_MOC_LITERAL(26, 486, 19), // "on_btnStart_pressed"
QT_MOC_LITERAL(27, 506, 20), // "on_btnStart_released"
QT_MOC_LITERAL(28, 527, 31), // "on_btnRefreshSerialPort_pressed"
QT_MOC_LITERAL(29, 559, 32), // "on_btnRefreshSerialPort_released"
QT_MOC_LITERAL(30, 592, 18), // "on_btnDown_clicked"
QT_MOC_LITERAL(31, 611, 16), // "on_btnUp_clicked"
QT_MOC_LITERAL(32, 628, 18), // "on_btnTest_clicked"
QT_MOC_LITERAL(33, 647, 23), // "on_btnArrowLeft_clicked"
QT_MOC_LITERAL(34, 671, 24), // "on_btnArrowRight_clicked"
QT_MOC_LITERAL(35, 696, 26), // "on_btnArrowRightDL_clicked"
QT_MOC_LITERAL(36, 723, 25), // "on_btnArrowLeftDL_clicked"
QT_MOC_LITERAL(37, 749, 32), // "on_btnTargetBebanRefresh_pressed"
QT_MOC_LITERAL(38, 782, 33), // "on_btnTargetBebanRefresh_rele..."
QT_MOC_LITERAL(39, 816, 18), // "on_btnTera_pressed"
QT_MOC_LITERAL(40, 835, 19), // "on_btnTera_released"
QT_MOC_LITERAL(41, 855, 26), // "on_btnResetEncoder_pressed"
QT_MOC_LITERAL(42, 882, 27), // "on_btnResetEncoder_released"
QT_MOC_LITERAL(43, 910, 18), // "on_btnDown_pressed"
QT_MOC_LITERAL(44, 929, 19), // "on_btnDown_released"
QT_MOC_LITERAL(45, 949, 16), // "on_btnUp_pressed"
QT_MOC_LITERAL(46, 966, 17), // "on_btnUp_released"
QT_MOC_LITERAL(47, 984, 18), // "on_btnStop_pressed"
QT_MOC_LITERAL(48, 1003, 19), // "on_btnStop_released"
QT_MOC_LITERAL(49, 1023, 18), // "on_btnOpen_pressed"
QT_MOC_LITERAL(50, 1042, 19), // "on_btnOpen_released"
QT_MOC_LITERAL(51, 1062, 18), // "on_btnSave_pressed"
QT_MOC_LITERAL(52, 1081, 19), // "on_btnSave_released"
QT_MOC_LITERAL(53, 1101, 26), // "on_btnArrowRightDL_pressed"
QT_MOC_LITERAL(54, 1128, 27), // "on_btnArrowRightDL_released"
QT_MOC_LITERAL(55, 1156, 25), // "on_btnArrowLeftDL_pressed"
QT_MOC_LITERAL(56, 1182, 26), // "on_btnArrowLeftDL_released"
QT_MOC_LITERAL(57, 1209, 24), // "on_btnArrowRight_pressed"
QT_MOC_LITERAL(58, 1234, 25), // "on_btnArrowRight_released"
QT_MOC_LITERAL(59, 1260, 23), // "on_btnArrowLeft_pressed"
QT_MOC_LITERAL(60, 1284, 24), // "on_btnArrowLeft_released"
QT_MOC_LITERAL(61, 1309, 32), // "on_btnTargetBebanRefresh_clicked"
QT_MOC_LITERAL(62, 1342, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(63, 1361, 25), // "on_btnStopFromRun_clicked"
QT_MOC_LITERAL(64, 1387, 20) // "on_btnResume_clicked"

    },
    "MainWindow\0init_port\0\0closeSerialPort\0"
    "readData\0handleError\0QSerialPort::SerialPortError\0"
    "error\0realtimeDataSlot\0value\0"
    "on_btnRefreshSerialPort_clicked\0"
    "on_btnStop_clicked\0slotTimerClock\0"
    "slotTimerProcessPayload\0updateStopwatch\0"
    "showPortInfo\0idx\0"
    "on_serialPortInfoListBox_currentIndexChanged\0"
    "arg1\0on_serialPortInfoListBox_activated\0"
    "on_btnTera_clicked\0on_btnResetEncoder_clicked\0"
    "on_logSerialTextEdit_textChanged\0"
    "on_btnStart_clicked\0on_btnClearGraphmmGram_clicked\0"
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
    "on_btnArrowLeft_released\0"
    "on_btnTargetBebanRefresh_clicked\0"
    "on_btnOpen_clicked\0on_btnStopFromRun_clicked\0"
    "on_btnResume_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      58,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  304,    2, 0x08 /* Private */,
       3,    0,  305,    2, 0x08 /* Private */,
       4,    0,  306,    2, 0x08 /* Private */,
       5,    1,  307,    2, 0x08 /* Private */,
       8,    1,  310,    2, 0x08 /* Private */,
      10,    0,  313,    2, 0x08 /* Private */,
      11,    0,  314,    2, 0x08 /* Private */,
      12,    0,  315,    2, 0x08 /* Private */,
      13,    0,  316,    2, 0x08 /* Private */,
      14,    0,  317,    2, 0x08 /* Private */,
      15,    1,  318,    2, 0x08 /* Private */,
      17,    1,  321,    2, 0x08 /* Private */,
      19,    1,  324,    2, 0x08 /* Private */,
      20,    0,  327,    2, 0x08 /* Private */,
      21,    0,  328,    2, 0x08 /* Private */,
      22,    0,  329,    2, 0x08 /* Private */,
      23,    0,  330,    2, 0x08 /* Private */,
      24,    0,  331,    2, 0x08 /* Private */,
      25,    0,  332,    2, 0x08 /* Private */,
      26,    0,  333,    2, 0x08 /* Private */,
      27,    0,  334,    2, 0x08 /* Private */,
      28,    0,  335,    2, 0x08 /* Private */,
      29,    0,  336,    2, 0x08 /* Private */,
      30,    0,  337,    2, 0x08 /* Private */,
      31,    0,  338,    2, 0x08 /* Private */,
      32,    0,  339,    2, 0x08 /* Private */,
      33,    0,  340,    2, 0x08 /* Private */,
      34,    0,  341,    2, 0x08 /* Private */,
      35,    0,  342,    2, 0x08 /* Private */,
      36,    0,  343,    2, 0x08 /* Private */,
      37,    0,  344,    2, 0x08 /* Private */,
      38,    0,  345,    2, 0x08 /* Private */,
      39,    0,  346,    2, 0x08 /* Private */,
      40,    0,  347,    2, 0x08 /* Private */,
      41,    0,  348,    2, 0x08 /* Private */,
      42,    0,  349,    2, 0x08 /* Private */,
      43,    0,  350,    2, 0x08 /* Private */,
      44,    0,  351,    2, 0x08 /* Private */,
      45,    0,  352,    2, 0x08 /* Private */,
      46,    0,  353,    2, 0x08 /* Private */,
      47,    0,  354,    2, 0x08 /* Private */,
      48,    0,  355,    2, 0x08 /* Private */,
      49,    0,  356,    2, 0x08 /* Private */,
      50,    0,  357,    2, 0x08 /* Private */,
      51,    0,  358,    2, 0x08 /* Private */,
      52,    0,  359,    2, 0x08 /* Private */,
      53,    0,  360,    2, 0x08 /* Private */,
      54,    0,  361,    2, 0x08 /* Private */,
      55,    0,  362,    2, 0x08 /* Private */,
      56,    0,  363,    2, 0x08 /* Private */,
      57,    0,  364,    2, 0x08 /* Private */,
      58,    0,  365,    2, 0x08 /* Private */,
      59,    0,  366,    2, 0x08 /* Private */,
      60,    0,  367,    2, 0x08 /* Private */,
      61,    0,  368,    2, 0x08 /* Private */,
      62,    0,  369,    2, 0x08 /* Private */,
      63,    0,  370,    2, 0x08 /* Private */,
      64,    0,  371,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   18,
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
        case 1: _t->closeSerialPort(); break;
        case 2: _t->readData(); break;
        case 3: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 4: _t->realtimeDataSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_btnRefreshSerialPort_clicked(); break;
        case 6: _t->on_btnStop_clicked(); break;
        case 7: _t->slotTimerClock(); break;
        case 8: _t->slotTimerProcessPayload(); break;
        case 9: _t->updateStopwatch(); break;
        case 10: _t->showPortInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_serialPortInfoListBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_serialPortInfoListBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_btnTera_clicked(); break;
        case 14: _t->on_btnResetEncoder_clicked(); break;
        case 15: _t->on_logSerialTextEdit_textChanged(); break;
        case 16: _t->on_btnStart_clicked(); break;
        case 17: _t->on_btnClearGraphmmGram_clicked(); break;
        case 18: _t->on_btnClearGraphtsgram_clicked(); break;
        case 19: _t->on_btnStart_pressed(); break;
        case 20: _t->on_btnStart_released(); break;
        case 21: _t->on_btnRefreshSerialPort_pressed(); break;
        case 22: _t->on_btnRefreshSerialPort_released(); break;
        case 23: _t->on_btnDown_clicked(); break;
        case 24: _t->on_btnUp_clicked(); break;
        case 25: _t->on_btnTest_clicked(); break;
        case 26: _t->on_btnArrowLeft_clicked(); break;
        case 27: _t->on_btnArrowRight_clicked(); break;
        case 28: _t->on_btnArrowRightDL_clicked(); break;
        case 29: _t->on_btnArrowLeftDL_clicked(); break;
        case 30: _t->on_btnTargetBebanRefresh_pressed(); break;
        case 31: _t->on_btnTargetBebanRefresh_released(); break;
        case 32: _t->on_btnTera_pressed(); break;
        case 33: _t->on_btnTera_released(); break;
        case 34: _t->on_btnResetEncoder_pressed(); break;
        case 35: _t->on_btnResetEncoder_released(); break;
        case 36: _t->on_btnDown_pressed(); break;
        case 37: _t->on_btnDown_released(); break;
        case 38: _t->on_btnUp_pressed(); break;
        case 39: _t->on_btnUp_released(); break;
        case 40: _t->on_btnStop_pressed(); break;
        case 41: _t->on_btnStop_released(); break;
        case 42: _t->on_btnOpen_pressed(); break;
        case 43: _t->on_btnOpen_released(); break;
        case 44: _t->on_btnSave_pressed(); break;
        case 45: _t->on_btnSave_released(); break;
        case 46: _t->on_btnArrowRightDL_pressed(); break;
        case 47: _t->on_btnArrowRightDL_released(); break;
        case 48: _t->on_btnArrowLeftDL_pressed(); break;
        case 49: _t->on_btnArrowLeftDL_released(); break;
        case 50: _t->on_btnArrowRight_pressed(); break;
        case 51: _t->on_btnArrowRight_released(); break;
        case 52: _t->on_btnArrowLeft_pressed(); break;
        case 53: _t->on_btnArrowLeft_released(); break;
        case 54: _t->on_btnTargetBebanRefresh_clicked(); break;
        case 55: _t->on_btnOpen_clicked(); break;
        case 56: _t->on_btnStopFromRun_clicked(); break;
        case 57: _t->on_btnResume_clicked(); break;
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
        if (_id < 58)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 58;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 58)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 58;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
