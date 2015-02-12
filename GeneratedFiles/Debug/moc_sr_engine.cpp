/****************************************************************************
** Meta object code from reading C++ file 'sr_engine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Source/sr_engine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sr_engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sr_engine_t {
    QByteArrayData data[5];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sr_engine_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sr_engine_t qt_meta_stringdata_sr_engine = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 11),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 6),
QT_MOC_LITERAL(4, 30, 12)
    },
    "sr_engine\0sample_read\0\0sample\0"
    "debug_signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sr_engine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void sr_engine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sr_engine *_t = static_cast<sr_engine *>(_o);
        switch (_id) {
        case 0: _t->sample_read((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 1: _t->debug_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sr_engine::*_t)(short );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sr_engine::sample_read)) {
                *result = 0;
            }
        }
        {
            typedef void (sr_engine::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sr_engine::debug_signal)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject sr_engine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_sr_engine.data,
      qt_meta_data_sr_engine,  qt_static_metacall, 0, 0}
};


const QMetaObject *sr_engine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sr_engine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sr_engine.stringdata))
        return static_cast<void*>(const_cast< sr_engine*>(this));
    return QObject::qt_metacast(_clname);
}

int sr_engine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void sr_engine::sample_read(short _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sr_engine::debug_signal(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
