/****************************************************************************
** Meta object code from reading C++ file 'DlgROSAPIUsers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Dialogs/DlgROSAPIUsers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgROSAPIUsers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DlgROSAPIUsers_t {
    QByteArrayData data[8];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgROSAPIUsers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgROSAPIUsers_t qt_meta_stringdata_DlgROSAPIUsers = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DlgROSAPIUsers"
QT_MOC_LITERAL(1, 15, 12), // "dataModified"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "ROSDataBase"
QT_MOC_LITERAL(4, 41, 7), // "rosData"
QT_MOC_LITERAL(5, 49, 12), // "QRouterIDMap"
QT_MOC_LITERAL(6, 62, 11), // "routerIDMap"
QT_MOC_LITERAL(7, 74, 24) // "on_addUserButton_clicked"

    },
    "DlgROSAPIUsers\0dataModified\0\0ROSDataBase\0"
    "rosData\0QRouterIDMap\0routerIDMap\0"
    "on_addUserButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgROSAPIUsers[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DlgROSAPIUsers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DlgROSAPIUsers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataModified((*reinterpret_cast< const ROSDataBase(*)>(_a[1])),(*reinterpret_cast< const QRouterIDMap(*)>(_a[2]))); break;
        case 1: _t->on_addUserButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DlgROSAPIUsers::*)(const ROSDataBase & , const QRouterIDMap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DlgROSAPIUsers::dataModified)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DlgROSAPIUsers::staticMetaObject = { {
    &QDlgMultiDataBase::staticMetaObject,
    qt_meta_stringdata_DlgROSAPIUsers.data,
    qt_meta_data_DlgROSAPIUsers,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DlgROSAPIUsers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgROSAPIUsers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DlgROSAPIUsers.stringdata0))
        return static_cast<void*>(this);
    return QDlgMultiDataBase::qt_metacast(_clname);
}

int DlgROSAPIUsers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDlgMultiDataBase::qt_metacall(_c, _id, _a);
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
void DlgROSAPIUsers::dataModified(const ROSDataBase & _t1, const QRouterIDMap _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
