/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ThisTimeForSure/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 13), // "digit_numbers"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 11), // "bracketable"
QT_MOC_LITERAL(38, 10), // "ooperators"
QT_MOC_LITERAL(49, 22), // "ooperators_un_possible"
QT_MOC_LITERAL(72, 16), // "on_point_clicked"
QT_MOC_LITERAL(89, 20), // "on_factorial_clicked"
QT_MOC_LITERAL(110, 16), // "on_reset_clicked"
QT_MOC_LITERAL(127, 20), // "on_backspace_clicked"
QT_MOC_LITERAL(148, 17), // "on_open_b_clicked"
QT_MOC_LITERAL(166, 18), // "on_close_b_clicked"
QT_MOC_LITERAL(185, 16), // "on_equal_clicked"
QT_MOC_LITERAL(202, 14), // "on_CoW_clicked"
QT_MOC_LITERAL(217, 16), // "on_Graph_clicked"
QT_MOC_LITERAL(234, 17), // "on_credit_clicked"
QT_MOC_LITERAL(252, 18) // "on_deposit_clicked"

    },
    "MainWindow\0digit_numbers\0\0bracketable\0"
    "ooperators\0ooperators_un_possible\0"
    "on_point_clicked\0on_factorial_clicked\0"
    "on_reset_clicked\0on_backspace_clicked\0"
    "on_open_b_clicked\0on_close_b_clicked\0"
    "on_equal_clicked\0on_CoW_clicked\0"
    "on_Graph_clicked\0on_credit_clicked\0"
    "on_deposit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    0,  107,    2, 0x08,    4 /* Private */,
       6,    0,  108,    2, 0x08,    5 /* Private */,
       7,    0,  109,    2, 0x08,    6 /* Private */,
       8,    0,  110,    2, 0x08,    7 /* Private */,
       9,    0,  111,    2, 0x08,    8 /* Private */,
      10,    0,  112,    2, 0x08,    9 /* Private */,
      11,    0,  113,    2, 0x08,   10 /* Private */,
      12,    0,  114,    2, 0x08,   11 /* Private */,
      13,    0,  115,    2, 0x08,   12 /* Private */,
      14,    0,  116,    2, 0x08,   13 /* Private */,
      15,    0,  117,    2, 0x08,   14 /* Private */,
      16,    0,  118,    2, 0x08,   15 /* Private */,

 // slots: parameters
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
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->digit_numbers(); break;
        case 1: _t->bracketable(); break;
        case 2: _t->ooperators(); break;
        case 3: _t->ooperators_un_possible(); break;
        case 4: _t->on_point_clicked(); break;
        case 5: _t->on_factorial_clicked(); break;
        case 6: _t->on_reset_clicked(); break;
        case 7: _t->on_backspace_clicked(); break;
        case 8: _t->on_open_b_clicked(); break;
        case 9: _t->on_close_b_clicked(); break;
        case 10: _t->on_equal_clicked(); break;
        case 11: _t->on_CoW_clicked(); break;
        case 12: _t->on_Graph_clicked(); break;
        case 13: _t->on_credit_clicked(); break;
        case 14: _t->on_deposit_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
