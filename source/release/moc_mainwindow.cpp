/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[13];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "userLoginToggled"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "setUpTriggerd"
QT_MOC_LITERAL(4, 43, 14), // "runProgToggled"
QT_MOC_LITERAL(5, 58, 14), // "minWinTriggerd"
QT_MOC_LITERAL(6, 73, 18), // "logActionTriggered"
QT_MOC_LITERAL(7, 92, 13), // "SlotShowImage"
QT_MOC_LITERAL(8, 106, 9), // "SlotStudy"
QT_MOC_LITERAL(9, 116, 17), // "QVector<XVRegion>"
QT_MOC_LITERAL(10, 134, 20), // "Write2SysSettingFile"
QT_MOC_LITERAL(11, 155, 16), // "SlotCountChanged"
QT_MOC_LITERAL(12, 172, 20) // "CreateUndCheckModbus"

    },
    "MainWindow\0userLoginToggled\0\0setUpTriggerd\0"
    "runProgToggled\0minWinTriggerd\0"
    "logActionTriggered\0SlotShowImage\0"
    "SlotStudy\0QVector<XVRegion>\0"
    "Write2SysSettingFile\0SlotCountChanged\0"
    "CreateUndCheckModbus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    1,   64,    2, 0x0a /* Public */,
       3,    0,   67,    2, 0x0a /* Public */,
       4,    1,   68,    2, 0x0a /* Public */,
       5,    0,   71,    2, 0x0a /* Public */,
       6,    0,   72,    2, 0x0a /* Public */,
       7,    1,   73,    2, 0x0a /* Public */,
       8,    1,   76,    2, 0x0a /* Public */,
      10,    1,   79,    2, 0x0a /* Public */,
      11,    4,   82,    2, 0x0a /* Public */,
      12,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userLoginToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setUpTriggerd(); break;
        case 2: _t->runProgToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->minWinTriggerd(); break;
        case 4: _t->logActionTriggered(); break;
        case 5: _t->SlotShowImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->SlotStudy((*reinterpret_cast< QVector<XVRegion>(*)>(_a[1]))); break;
        case 7: _t->Write2SysSettingFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->SlotCountChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->CreateUndCheckModbus(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
