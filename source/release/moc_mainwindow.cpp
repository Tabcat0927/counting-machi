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
    char stringdata0[178];
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
QT_MOC_LITERAL(10, 134, 15), // "GetXVRegionArea"
QT_MOC_LITERAL(11, 150, 9), // "XVRegion&"
QT_MOC_LITERAL(12, 160, 17) // "GetXVRegionRadius"

    },
    "MainWindow\0userLoginToggled\0\0setUpTriggerd\0"
    "runProgToggled\0minWinTriggerd\0"
    "logActionTriggered\0SlotShowImage\0"
    "SlotStudy\0QVector<XVRegion>\0GetXVRegionArea\0"
    "XVRegion&\0GetXVRegionRadius"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       3,    0,   62,    2, 0x0a /* Public */,
       4,    1,   63,    2, 0x0a /* Public */,
       5,    0,   66,    2, 0x0a /* Public */,
       6,    0,   67,    2, 0x0a /* Public */,
       7,    1,   68,    2, 0x0a /* Public */,
       8,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Int, 0x80000000 | 11,    2,
    QMetaType::Float, 0x80000000 | 11,    2,

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
        case 7: { int _r = _t->GetXVRegionArea((*reinterpret_cast< XVRegion(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { float _r = _t->GetXVRegionRadius((*reinterpret_cast< XVRegion(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
