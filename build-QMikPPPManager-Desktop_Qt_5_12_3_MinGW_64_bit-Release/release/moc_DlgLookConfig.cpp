/****************************************************************************
** Meta object code from reading C++ file 'DlgLookConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Dialogs/DlgLookConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgLookConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DlgLookConfig_t {
    QByteArrayData data[17];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgLookConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgLookConfig_t qt_meta_stringdata_DlgLookConfig = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DlgLookConfig"
QT_MOC_LITERAL(1, 14, 14), // "onItemSelected"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "updateCellLook"
QT_MOC_LITERAL(4, 45, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(5, 63, 4), // "item"
QT_MOC_LITERAL(6, 68, 19), // "updateTableFontSize"
QT_MOC_LITERAL(7, 88, 4), // "size"
QT_MOC_LITERAL(8, 93, 20), // "updateTableRowHeight"
QT_MOC_LITERAL(9, 114, 21), // "updateCurrentCellLook"
QT_MOC_LITERAL(10, 136, 23), // "on_acceptButton_clicked"
QT_MOC_LITERAL(11, 160, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(12, 184, 23), // "on_boldCheckBox_clicked"
QT_MOC_LITERAL(13, 208, 25), // "on_italicCheckBox_clicked"
QT_MOC_LITERAL(14, 234, 26), // "on_textColorButton_clicked"
QT_MOC_LITERAL(15, 261, 25), // "on_textFontButton_clicked"
QT_MOC_LITERAL(16, 287, 26) // "on_backColorButton_clicked"

    },
    "DlgLookConfig\0onItemSelected\0\0"
    "updateCellLook\0QTableWidgetItem*\0item\0"
    "updateTableFontSize\0size\0updateTableRowHeight\0"
    "updateCurrentCellLook\0on_acceptButton_clicked\0"
    "on_cancelButton_clicked\0on_boldCheckBox_clicked\0"
    "on_italicCheckBox_clicked\0"
    "on_textColorButton_clicked\0"
    "on_textFontButton_clicked\0"
    "on_backColorButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgLookConfig[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       6,    1,   88,    2, 0x08 /* Private */,
       6,    0,   91,    2, 0x28 /* Private | MethodCloned */,
       8,    1,   92,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x28 /* Private | MethodCloned */,
       9,    1,   96,    2, 0x08 /* Private */,
      10,    0,   99,    2, 0x08 /* Private */,
      11,    0,  100,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    0,  104,    2, 0x08 /* Private */,
      16,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DlgLookConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DlgLookConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onItemSelected(); break;
        case 1: _t->updateCellLook((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->updateTableFontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateTableFontSize(); break;
        case 4: _t->updateTableRowHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateTableRowHeight(); break;
        case 6: _t->updateCurrentCellLook((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_acceptButton_clicked(); break;
        case 8: _t->on_cancelButton_clicked(); break;
        case 9: _t->on_boldCheckBox_clicked(); break;
        case 10: _t->on_italicCheckBox_clicked(); break;
        case 11: _t->on_textColorButton_clicked(); break;
        case 12: _t->on_textFontButton_clicked(); break;
        case 13: _t->on_backColorButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DlgLookConfig::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_DlgLookConfig.data,
    qt_meta_data_DlgLookConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DlgLookConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgLookConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DlgLookConfig.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DlgLookConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
