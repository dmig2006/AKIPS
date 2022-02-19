/****************************************************************************
** Meta object code from reading C++ file 'comport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/comport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComPort_t {
    QByteArrayData data[7];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComPort_t qt_meta_stringdata_ComPort = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ComPort"
QT_MOC_LITERAL(1, 8, 8), // "COM_Open"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "pId"
QT_MOC_LITERAL(4, 22, 5), // "index"
QT_MOC_LITERAL(5, 28, 1), // "p"
QT_MOC_LITERAL(6, 30, 9) // "emitIndex"

    },
    "ComPort\0COM_Open\0\0pId\0index\0p\0emitIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void ComPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComPort *_t = static_cast<ComPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->COM_Open((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->emitIndex(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ComPort::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ComPort::COM_Open)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ComPort::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ComPort.data,
      qt_meta_data_ComPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ComPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ComPort.stringdata0))
        return static_cast<void*>(const_cast< ComPort*>(this));
    if (!strcmp(_clname, "MDObject"))
        return static_cast< MDObject*>(const_cast< ComPort*>(this));
    return QDialog::qt_metacast(_clname);
}

int ComPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void ComPort::COM_Open(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
