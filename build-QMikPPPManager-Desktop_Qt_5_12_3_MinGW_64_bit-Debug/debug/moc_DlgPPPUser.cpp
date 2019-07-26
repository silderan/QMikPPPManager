/****************************************************************************
** Meta object code from reading C++ file 'DlgPPPUser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Dialogs/DlgPPPUser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgPPPUser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DlgPPPUser_t {
    QByteArrayData data[17];
    char stringdata0[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgPPPUser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgPPPUser_t qt_meta_stringdata_DlgPPPUser = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DlgPPPUser"
QT_MOC_LITERAL(1, 11, 41), // "on_pppProfileComboBox_current..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "index"
QT_MOC_LITERAL(4, 60, 26), // "on_applyDataButton_clicked"
QT_MOC_LITERAL(5, 87, 24), // "on_addPortButton_clicked"
QT_MOC_LITERAL(6, 112, 24), // "on_delPortButton_clicked"
QT_MOC_LITERAL(7, 137, 27), // "on_clientLogsButton_clicked"
QT_MOC_LITERAL(8, 165, 32), // "on_pppUserNameCopyButton_clicked"
QT_MOC_LITERAL(9, 198, 32), // "on_pppUserPassCopyButton_clicked"
QT_MOC_LITERAL(10, 231, 34), // "on_pppUserPassCreateButton_cl..."
QT_MOC_LITERAL(11, 266, 25), // "on_copyInfoButton_clicked"
QT_MOC_LITERAL(12, 292, 17), // "onEditUserRequest"
QT_MOC_LITERAL(13, 310, 13), // "QPPPSecretMap"
QT_MOC_LITERAL(14, 324, 12), // "pppSecretMap"
QT_MOC_LITERAL(15, 337, 12), // "ROSPPPActive"
QT_MOC_LITERAL(16, 350, 9) // "pppActive"

    },
    "DlgPPPUser\0on_pppProfileComboBox_currentIndexChanged\0"
    "\0index\0on_applyDataButton_clicked\0"
    "on_addPortButton_clicked\0"
    "on_delPortButton_clicked\0"
    "on_clientLogsButton_clicked\0"
    "on_pppUserNameCopyButton_clicked\0"
    "on_pppUserPassCopyButton_clicked\0"
    "on_pppUserPassCreateButton_clicked\0"
    "on_copyInfoButton_clicked\0onEditUserRequest\0"
    "QPPPSecretMap\0pppSecretMap\0ROSPPPActive\0"
    "pppActive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgPPPUser[] = {

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
       1,    1,   64,    2, 0x08 /* Private */,
       4,    0,   67,    2, 0x08 /* Private */,
       5,    0,   68,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    2,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15,   14,   16,

       0        // eod
};

void DlgPPPUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DlgPPPUser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pppProfileComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_applyDataButton_clicked(); break;
        case 2: _t->on_addPortButton_clicked(); break;
        case 3: _t->on_delPortButton_clicked(); break;
        case 4: _t->on_clientLogsButton_clicked(); break;
        case 5: _t->on_pppUserNameCopyButton_clicked(); break;
        case 6: _t->on_pppUserPassCopyButton_clicked(); break;
        case 7: _t->on_pppUserPassCreateButton_clicked(); break;
        case 8: _t->on_copyInfoButton_clicked(); break;
        case 9: _t->onEditUserRequest((*reinterpret_cast< const QPPPSecretMap(*)>(_a[1])),(*reinterpret_cast< const ROSPPPActive(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DlgPPPUser::staticMetaObject = { {
    &QDlgMultiDataBase::staticMetaObject,
    qt_meta_stringdata_DlgPPPUser.data,
    qt_meta_data_DlgPPPUser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DlgPPPUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgPPPUser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DlgPPPUser.stringdata0))
        return static_cast<void*>(this);
    return QDlgMultiDataBase::qt_metacast(_clname);
}

int DlgPPPUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDlgMultiDataBase::qt_metacall(_c, _id, _a);
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
