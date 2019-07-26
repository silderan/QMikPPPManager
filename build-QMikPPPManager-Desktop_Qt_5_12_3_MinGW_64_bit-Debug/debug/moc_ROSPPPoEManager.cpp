/****************************************************************************
** Meta object code from reading C++ file 'ROSPPPoEManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ROSPPPoEManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ROSPPPoEManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ROSPPPoEManager_t {
    QByteArrayData data[30];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ROSPPPoEManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ROSPPPoEManager_t qt_meta_stringdata_ROSPPPoEManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ROSPPPoEManager"
QT_MOC_LITERAL(1, 16, 10), // "statusInfo"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "routerName"
QT_MOC_LITERAL(4, 39, 4), // "info"
QT_MOC_LITERAL(5, 44, 18), // "routerDisconnected"
QT_MOC_LITERAL(6, 63, 15), // "routerConnected"
QT_MOC_LITERAL(7, 79, 6), // "logued"
QT_MOC_LITERAL(8, 86, 8), // "comError"
QT_MOC_LITERAL(9, 95, 11), // "errorString"
QT_MOC_LITERAL(10, 107, 8), // "rosError"
QT_MOC_LITERAL(11, 116, 11), // "rosModReply"
QT_MOC_LITERAL(12, 128, 11), // "ROSDataBase"
QT_MOC_LITERAL(13, 140, 7), // "rosData"
QT_MOC_LITERAL(14, 148, 11), // "rosDelReply"
QT_MOC_LITERAL(15, 160, 10), // "DataTypeID"
QT_MOC_LITERAL(16, 171, 10), // "dataTypeID"
QT_MOC_LITERAL(17, 182, 11), // "rosObjectID"
QT_MOC_LITERAL(18, 194, 7), // "rosDone"
QT_MOC_LITERAL(19, 202, 14), // "onDataReceived"
QT_MOC_LITERAL(20, 217, 15), // "ROS::QSentence&"
QT_MOC_LITERAL(21, 233, 8), // "sentence"
QT_MOC_LITERAL(22, 242, 10), // "onComError"
QT_MOC_LITERAL(23, 253, 20), // "ROS::Comm::CommError"
QT_MOC_LITERAL(24, 274, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(25, 303, 18), // "onCommStateChanged"
QT_MOC_LITERAL(26, 322, 20), // "ROS::Comm::CommState"
QT_MOC_LITERAL(27, 343, 1), // "s"
QT_MOC_LITERAL(28, 345, 14), // "onLoginChanged"
QT_MOC_LITERAL(29, 360, 21) // "ROS::Comm::LoginState"

    },
    "ROSPPPoEManager\0statusInfo\0\0routerName\0"
    "info\0routerDisconnected\0routerConnected\0"
    "logued\0comError\0errorString\0rosError\0"
    "rosModReply\0ROSDataBase\0rosData\0"
    "rosDelReply\0DataTypeID\0dataTypeID\0"
    "rosObjectID\0rosDone\0onDataReceived\0"
    "ROS::QSentence&\0sentence\0onComError\0"
    "ROS::Comm::CommError\0QAbstractSocket::SocketError\0"
    "onCommStateChanged\0ROS::Comm::CommState\0"
    "s\0onLoginChanged\0ROS::Comm::LoginState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ROSPPPoEManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    1,   84,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
       8,    2,   93,    2, 0x06 /* Public */,
      10,    2,   98,    2, 0x06 /* Public */,
      11,    1,  103,    2, 0x06 /* Public */,
      14,    3,  106,    2, 0x06 /* Public */,
      18,    2,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  118,    2, 0x08 /* Private */,
      22,    2,  121,    2, 0x08 /* Private */,
      25,    1,  126,    2, 0x08 /* Private */,
      28,    1,  129,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15, QMetaType::QString,    3,   16,   17,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15,    3,   16,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 24,    2,    2,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 29,   27,

       0        // eod
};

void ROSPPPoEManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ROSPPPoEManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->routerDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->routerConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->logued((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->comError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->rosError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->rosModReply((*reinterpret_cast< const ROSDataBase(*)>(_a[1]))); break;
        case 7: _t->rosDelReply((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< DataTypeID(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->rosDone((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< DataTypeID(*)>(_a[2]))); break;
        case 9: _t->onDataReceived((*reinterpret_cast< ROS::QSentence(*)>(_a[1]))); break;
        case 10: _t->onComError((*reinterpret_cast< ROS::Comm::CommError(*)>(_a[1])),(*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[2]))); break;
        case 11: _t->onCommStateChanged((*reinterpret_cast< ROS::Comm::CommState(*)>(_a[1]))); break;
        case 12: _t->onLoginChanged((*reinterpret_cast< ROS::Comm::LoginState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ROSPPPoEManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::statusInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::routerDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::routerConnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::logued)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::comError)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::rosError)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const ROSDataBase & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::rosModReply)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & , DataTypeID , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::rosDelReply)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ROSPPPoEManager::*)(const QString & , DataTypeID );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ROSPPPoEManager::rosDone)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ROSPPPoEManager::staticMetaObject = { {
    &ROS::Comm::staticMetaObject,
    qt_meta_stringdata_ROSPPPoEManager.data,
    qt_meta_data_ROSPPPoEManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ROSPPPoEManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ROSPPPoEManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ROSPPPoEManager.stringdata0))
        return static_cast<void*>(this);
    return ROS::Comm::qt_metacast(_clname);
}

int ROSPPPoEManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ROS::Comm::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ROSPPPoEManager::statusInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ROSPPPoEManager::routerDisconnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ROSPPPoEManager::routerConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ROSPPPoEManager::logued(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ROSPPPoEManager::comError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ROSPPPoEManager::rosError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ROSPPPoEManager::rosModReply(const ROSDataBase & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ROSPPPoEManager::rosDelReply(const QString & _t1, DataTypeID _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ROSPPPoEManager::rosDone(const QString & _t1, DataTypeID _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
