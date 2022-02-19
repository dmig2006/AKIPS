/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "portCom"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "saveFile"
QT_MOC_LITERAL(4, 29, 10), // "saveAsFile"
QT_MOC_LITERAL(5, 40, 4), // "help"
QT_MOC_LITERAL(6, 45, 10), // "updateDate"
QT_MOC_LITERAL(7, 56, 14), // "englishClicked"
QT_MOC_LITERAL(8, 71, 14), // "russionClicked"
QT_MOC_LITERAL(9, 86, 12), // "tableClicked"
QT_MOC_LITERAL(10, 99, 9), // "sizeEdit1"
QT_MOC_LITERAL(11, 109, 4), // "pStr"
QT_MOC_LITERAL(12, 114, 9), // "sizeEdit2"
QT_MOC_LITERAL(13, 124, 9), // "sizeEdit3"
QT_MOC_LITERAL(14, 134, 23), // "on_pushButton_t_clicked"
QT_MOC_LITERAL(15, 158, 23), // "on_pushButton_b_clicked"
QT_MOC_LITERAL(16, 182, 23), // "on_pushButton_g_clicked"
QT_MOC_LITERAL(17, 206, 23), // "on_pushButton_z_clicked"
QT_MOC_LITERAL(18, 230, 13) // "handleTimeout"

    },
    "MainWindow\0portCom\0\0saveFile\0saveAsFile\0"
    "help\0updateDate\0englishClicked\0"
    "russionClicked\0tableClicked\0sizeEdit1\0"
    "pStr\0sizeEdit2\0sizeEdit3\0"
    "on_pushButton_t_clicked\0on_pushButton_b_clicked\0"
    "on_pushButton_g_clicked\0on_pushButton_z_clicked\0"
    "handleTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      12,    1,  105,    2, 0x08 /* Private */,
      13,    1,  108,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
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
        case 0: _t->portCom(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->saveAsFile(); break;
        case 3: _t->help(); break;
        case 4: _t->updateDate(); break;
        case 5: _t->englishClicked(); break;
        case 6: _t->russionClicked(); break;
        case 7: _t->tableClicked(); break;
        case 8: _t->sizeEdit1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->sizeEdit2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->sizeEdit3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_t_clicked(); break;
        case 12: _t->on_pushButton_b_clicked(); break;
        case 13: _t->on_pushButton_g_clicked(); break;
        case 14: _t->on_pushButton_z_clicked(); break;
        case 15: _t->handleTimeout(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "MDObject"))
        return static_cast< MDObject*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
