/****************************************************************************
** Meta object code from reading C++ file 'SerialManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SerialManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CSerialManager_t {
    QByteArrayData data[11];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSerialManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSerialManager_t qt_meta_stringdata_CSerialManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CSerialManager"
QT_MOC_LITERAL(1, 15, 17), // "SendConnectStatus"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 10), // "bConnected"
QT_MOC_LITERAL(4, 45, 14), // "SendClearQueue"
QT_MOC_LITERAL(5, 60, 17), // "handleSerialError"
QT_MOC_LITERAL(6, 78, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(7, 107, 5), // "error"
QT_MOC_LITERAL(8, 113, 11), // "handle_data"
QT_MOC_LITERAL(9, 125, 16), // "SendPLCHeartbeat"
QT_MOC_LITERAL(10, 142, 15) // "GetPLCHeartbeat"

    },
    "CSerialManager\0SendConnectStatus\0\0"
    "bConnected\0SendClearQueue\0handleSerialError\0"
    "QSerialPort::SerialPortError\0error\0"
    "handle_data\0SendPLCHeartbeat\0"
    "GetPLCHeartbeat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSerialManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CSerialManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CSerialManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SendClearQueue(); break;
        case 2: _t->handleSerialError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 3: _t->handle_data(); break;
        case 4: _t->SendPLCHeartbeat(); break;
        case 5: _t->GetPLCHeartbeat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CSerialManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerialManager::SendConnectStatus)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CSerialManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerialManager::SendClearQueue)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CSerialManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPort::staticMetaObject>(),
    qt_meta_stringdata_CSerialManager.data,
    qt_meta_data_CSerialManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CSerialManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSerialManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CSerialManager.stringdata0))
        return static_cast<void*>(this);
    return QSerialPort::qt_metacast(_clname);
}

int CSerialManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CSerialManager::SendConnectStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CSerialManager::SendClearQueue()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
