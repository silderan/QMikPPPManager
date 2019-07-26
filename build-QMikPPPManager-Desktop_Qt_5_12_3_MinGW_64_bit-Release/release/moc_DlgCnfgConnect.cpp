/****************************************************************************
** Meta object code from reading C++ file 'DlgCnfgConnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Dialogs/DlgCnfgConnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgCnfgConnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DlgCnfgConnect_t {
    QByteArrayData data[10];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgCnfgConnect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgCnfgConnect_t qt_meta_stringdata_DlgCnfgConnect = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DlgCnfgConnect"
QT_MOC_LITERAL(1, 15, 6), // "addRow"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "row"
QT_MOC_LITERAL(4, 27, 8), // "hostAddr"
QT_MOC_LITERAL(5, 36, 8), // "hostPort"
QT_MOC_LITERAL(6, 45, 11), // "routerState"
QT_MOC_LITERAL(7, 57, 16), // "removeCurrentRow"
QT_MOC_LITERAL(8, 74, 23), // "on_acceptButton_clicked"
QT_MOC_LITERAL(9, 98, 23) // "on_cancelButton_clicked"

    },
    "DlgCnfgConnect\0addRow\0\0row\0hostAddr\0"
    "hostPort\0routerState\0removeCurrentRow\0"
    "on_acceptButton_clicked\0on_cancelButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgCnfgConnect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x08 /* Private */,
       1,    3,   63,    2, 0x28 /* Private | MethodCloned */,
       1,    2,   70,    2, 0x28 /* Private | MethodCloned */,
       1,    1,   75,    2, 0x28 /* Private | MethodCloned */,
       1,    0,   78,    2, 0x28 /* Private | MethodCloned */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::UShort, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::UShort,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DlgCnfgConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DlgCnfgConnect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 1: _t->addRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 2: _t->addRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->addRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->addRow(); break;
        case 5: _t->removeCurrentRow(); break;
        case 6: _t->on_acceptButton_clicked(); break;
        case 7: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DlgCnfgConnect::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_DlgCnfgConnect.data,
    qt_meta_data_DlgCnfgConnect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DlgCnfgConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgCnfgConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DlgCnfgConnect.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DlgCnfgConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
