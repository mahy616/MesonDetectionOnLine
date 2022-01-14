/****************************************************************************
** Meta object code from reading C++ file 'CMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMainWindow_t {
    QByteArrayData data[22];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 13), // "StartDetecion"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "StopDetecion"
QT_MOC_LITERAL(4, 40, 11), // "OpenSetting"
QT_MOC_LITERAL(5, 52, 15), // "ResetStatistics"
QT_MOC_LITERAL(6, 68, 16), // "ReceiveAlgoImage"
QT_MOC_LITERAL(7, 85, 5), // "index"
QT_MOC_LITERAL(8, 91, 3), // "Mat"
QT_MOC_LITERAL(9, 95, 13), // "OriginalImage"
QT_MOC_LITERAL(10, 109, 11), // "RenderImage"
QT_MOC_LITERAL(11, 121, 4), // "Time"
QT_MOC_LITERAL(12, 126, 3), // "bok"
QT_MOC_LITERAL(13, 130, 17), // "ReceivePLCMessage"
QT_MOC_LITERAL(14, 148, 3), // "msg"
QT_MOC_LITERAL(15, 152, 20), // "ReceiveLabelTypeData"
QT_MOC_LITERAL(16, 173, 12), // "QVector<int>"
QT_MOC_LITERAL(17, 186, 9), // "LabelType"
QT_MOC_LITERAL(18, 196, 20), // "CheckSoftwareLicense"
QT_MOC_LITERAL(19, 217, 17), // "ReceiveClearQueue"
QT_MOC_LITERAL(20, 235, 16), // "ReceivePlcStatus"
QT_MOC_LITERAL(21, 252, 5) // "style"

    },
    "CMainWindow\0StartDetecion\0\0StopDetecion\0"
    "OpenSetting\0ResetStatistics\0"
    "ReceiveAlgoImage\0index\0Mat\0OriginalImage\0"
    "RenderImage\0Time\0bok\0ReceivePLCMessage\0"
    "msg\0ReceiveLabelTypeData\0QVector<int>\0"
    "LabelType\0CheckSoftwareLicense\0"
    "ReceiveClearQueue\0ReceivePlcStatus\0"
    "style"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    5,   68,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      15,    1,   82,    2, 0x08 /* Private */,
      18,    0,   85,    2, 0x08 /* Private */,
      19,    0,   86,    2, 0x08 /* Private */,
      20,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, 0x80000000 | 8, QMetaType::Int, QMetaType::Bool,    7,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartDetecion(); break;
        case 1: _t->StopDetecion(); break;
        case 2: _t->OpenSetting(); break;
        case 3: _t->ResetStatistics(); break;
        case 4: _t->ReceiveAlgoImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< Mat(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 5: _t->ReceivePLCMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->ReceiveLabelTypeData((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 7: _t->CheckSoftwareLicense(); break;
        case 8: _t->ReceiveClearQueue(); break;
        case 9: _t->ReceivePlcStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CMainWindow.data,
    qt_meta_data_CMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
