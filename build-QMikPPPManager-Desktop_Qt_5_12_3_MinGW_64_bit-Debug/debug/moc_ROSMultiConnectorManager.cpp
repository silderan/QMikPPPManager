/****************************************************************************
** Meta object code from reading C++ file 'ROSMultiConnectorManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ROSMultiConnectorManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ROSMultiConnectorManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ROSMultiConnectManager_t {
    QByteArrayData data[24];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ROSMultiConnectManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ROSMultiConnectManager_t qt_meta_stringdata_ROSMultiConnectManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ROSMultiConnectManager"
QT_MOC_LITERAL(1, 23, 10), // "statusInfo"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "routerName"
QT_MOC_LITERAL(4, 46, 4), // "info"
QT_MOC_LITERAL(5, 51, 18), // "routerDisconnected"
QT_MOC_LITERAL(6, 70, 21), // "allRoutersDisconected"
QT_MOC_LITERAL(7, 92, 15), // "routerConnected"
QT_MOC_LITERAL(8, 108, 18), // "allRoutersConected"
QT_MOC_LITERAL(9, 127, 6), // "logued"
QT_MOC_LITERAL(10, 134, 8), // "comError"
QT_MOC_LITERAL(11, 143, 11), // "errorString"
QT_MOC_LITERAL(12, 155, 8), // "rosError"
QT_MOC_LITERAL(13, 164, 11), // "rosModReply"
QT_MOC_LITERAL(14, 176, 11), // "ROSDataBase"
QT_MOC_LITERAL(15, 188, 7), // "rosData"
QT_MOC_LITERAL(16, 196, 11), // "rosDelReply"
QT_MOC_LITERAL(17, 208, 10), // "DataTypeID"
QT_MOC_LITERAL(18, 219, 10), // "dataTypeID"
QT_MOC_LITERAL(19, 230, 11), // "rosObjectID"
QT_MOC_LITERAL(20, 242, 7), // "rosDone"
QT_MOC_LITERAL(21, 250, 16), // "updateRemoteData"
QT_MOC_LITERAL(22, 267, 12), // "QRouterIDMap"
QT_MOC_LITERAL(23, 280, 11) // "routerIDMap"

    },
    "ROSMultiConnectManager\0statusInfo\0\0"
    "routerName\0info\0routerDisconnected\0"
    "allRoutersDisconected\0routerConnected\0"
    "allRoutersConected\0logued\0comError\0"
    "errorString\0rosError\0rosModReply\0"
    "ROSDataBase\0rosData\0rosDelReply\0"
    "DataTypeID\0dataTypeID\0rosObjectID\0"
    "rosDone\0updateRemoteData\0QRouterIDMap\0"
    "routerIDMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ROSMultiConnectManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    1,   79,    2, 0x06 /* Public */,
       6,    0,   82,    2, 0x06 /* Public */,
       7,    1,   83,    2, 0x06 /* Public */,
       8,    0,   86,    2, 0x06 /* Public */,
       9,    1,   87,    2, 0x06 /* Public */,
      10,    2,   90,    2, 0x06 /* Public */,
      12,    2,   95,    2, 0x06 /* Public */,
      13,    1,  100,    2, 0x06 /* Public */,
      16,    3,  103,    2, 0x06 /* Public */,
      20,    2,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   11,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 17, QMetaType::QString,    3,   18,   19,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 17,    3,   18,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 22,   15,   23,

       0        // eod
};

void ROSMultiConnectManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ROSMultiConnectManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->routerDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->allRoutersDisconected(); break;
        case 3: _t->routerConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->allRoutersConected(); break;
        case 5: _t->logued((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->comError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->rosError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->rosModReply((*reinterpret_cast< const ROSDataBase(*)>(_a[1]))); break;
        case 9: _t->rosDelReply((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< DataTypeID(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 10: _t->rosDone((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< DataTypeID(*)>(_a[2]))); break;
        case 11: _t->updateRemoteData((*reinterpret_cast< const ROSDataBase(*)>(_a[1])),(*reinterpret_cast< const QRouterIDMap(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::statusInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::routerDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::allRoutersDisconected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::routerConnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::allRoutersConected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::logued)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::comError)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::rosError)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const ROSDataBase & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::rosModReply)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & , DataTypeID , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::rosDelReply)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ROSMultiConnectManager::*)(const QString & , DataTypeID );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSMultiConnectManager::rosDone)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ROSMultiConnectManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ROSMultiConnectManager.data,
    qt_meta_data_ROSMultiConnectManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ROSMultiConnectManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ROSMultiConnectManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ROSMultiConnectManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ROSMultiConnectManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ROSMultiConnectManager::statusInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ROSMultiConnectManager::routerDisconnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ROSMultiConnectManager::allRoutersDisconected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ROSMultiConnectManager::routerConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ROSMultiConnectManager::allRoutersConected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ROSMultiConnectManager::logued(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ROSMultiConnectManager::comError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ROSMultiConnectManager::rosError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ROSMultiConnectManager::rosModReply(const ROSDataBase & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ROSMultiConnectManager::rosDelReply(const QString & _t1, DataTypeID _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ROSMultiConnectManager::rosDone(const QString & _t1, DataTypeID _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
