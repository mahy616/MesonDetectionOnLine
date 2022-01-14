/****************************************************************************
** Meta object code from reading C++ file 'RunAlgo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RunAlgo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RunAlgo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRunAlgo_t {
    QByteArrayData data[12];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRunAlgo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRunAlgo_t qt_meta_stringdata_CRunAlgo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CRunAlgo"
QT_MOC_LITERAL(1, 9, 13), // "SendAlgoImage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "index"
QT_MOC_LITERAL(4, 30, 3), // "Mat"
QT_MOC_LITERAL(5, 34, 13), // "OriginalImage"
QT_MOC_LITERAL(6, 48, 11), // "RenderImage"
QT_MOC_LITERAL(7, 60, 4), // "Time"
QT_MOC_LITERAL(8, 65, 3), // "bok"
QT_MOC_LITERAL(9, 69, 13), // "SendLabelType"
QT_MOC_LITERAL(10, 83, 20), // "ReceivaOriginalImage"
QT_MOC_LITERAL(11, 104, 9) // "AlgoIndex"

    },
    "CRunAlgo\0SendAlgoImage\0\0index\0Mat\0"
    "OriginalImage\0RenderImage\0Time\0bok\0"
    "SendLabelType\0ReceivaOriginalImage\0"
    "AlgoIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRunAlgo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   29,    2, 0x06 /* Public */,
       9,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    3,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 4, QMetaType::Int, QMetaType::Bool,    3,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QVariant,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, QMetaType::Int,    5,    6,   11,

       0        // eod
};

void CRunAlgo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CRunAlgo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendAlgoImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< Mat(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: _t->SendLabelType((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->ReceivaOriginalImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CRunAlgo::*)(int , Mat , Mat , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRunAlgo::SendAlgoImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CRunAlgo::*)(QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRunAlgo::SendLabelType)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CRunAlgo::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CRunAlgo.data,
    qt_meta_data_CRunAlgo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CRunAlgo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRunAlgo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CRunAlgo.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CRunAlgo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CRunAlgo::SendAlgoImage(int _t1, Mat _t2, Mat _t3, int _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CRunAlgo::SendLabelType(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
