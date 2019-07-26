/****************************************************************************
** Meta object code from reading C++ file 'DlgConfiguracion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Dialogs/DlgConfiguracion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgConfiguracion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DlgConfiguracion_t {
    QByteArrayData data[11];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgConfiguracion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgConfiguracion_t qt_meta_stringdata_DlgConfiguracion = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DlgConfiguracion"
QT_MOC_LITERAL(1, 17, 20), // "on_btAceptar_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 21), // "on_btCancelar_clicked"
QT_MOC_LITERAL(4, 61, 27), // "on_addProfileButton_clicked"
QT_MOC_LITERAL(5, 89, 27), // "on_delProfileButton_clicked"
QT_MOC_LITERAL(6, 117, 31), // "on_addStaticRangeButton_clicked"
QT_MOC_LITERAL(7, 149, 31), // "on_delStaticRangeButton_clicked"
QT_MOC_LITERAL(8, 181, 28), // "on_profilesTable_cellChanged"
QT_MOC_LITERAL(9, 210, 3), // "row"
QT_MOC_LITERAL(10, 214, 6) // "column"

    },
    "DlgConfiguracion\0on_btAceptar_clicked\0"
    "\0on_btCancelar_clicked\0"
    "on_addProfileButton_clicked\0"
    "on_delProfileButton_clicked\0"
    "on_addStaticRangeButton_clicked\0"
    "on_delStaticRangeButton_clicked\0"
    "on_profilesTable_cellChanged\0row\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgConfiguracion[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    2,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,

       0        // eod
};

void DlgConfiguracion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DlgConfiguracion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btAceptar_clicked(); break;
        case 1: _t->on_btCancelar_clicked(); break;
        case 2: _t->on_addProfileButton_clicked(); break;
        case 3: _t->on_delProfileButton_clicked(); break;
        case 4: _t->on_addStaticRangeButton_clicked(); break;
        case 5: _t->on_delStaticRangeButton_clicked(); break;
        case 6: _t->on_profilesTable_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DlgConfiguracion::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_DlgConfiguracion.data,
    qt_meta_data_DlgConfiguracion,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DlgConfiguracion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgConfiguracion::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DlgConfiguracion.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DlgConfiguracion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
