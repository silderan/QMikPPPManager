/****************************************************************************
** Meta object code from reading C++ file 'Comm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ROSAPI/Comm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Comm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ROS__Comm_t {
    QByteArrayData data[30];
    char stringdata0[371];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ROS__Comm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ROS__Comm_t qt_meta_stringdata_ROS__Comm = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ROS::Comm"
QT_MOC_LITERAL(1, 10, 8), // "comError"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 20), // "ROS::Comm::CommError"
QT_MOC_LITERAL(4, 41, 2), // "ce"
QT_MOC_LITERAL(5, 44, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(6, 73, 2), // "se"
QT_MOC_LITERAL(7, 76, 10), // "comReceive"
QT_MOC_LITERAL(8, 87, 15), // "ROS::QSentence&"
QT_MOC_LITERAL(9, 103, 1), // "s"
QT_MOC_LITERAL(10, 105, 15), // "comStateChanged"
QT_MOC_LITERAL(11, 121, 20), // "ROS::Comm::CommState"
QT_MOC_LITERAL(12, 142, 17), // "loginStateChanged"
QT_MOC_LITERAL(13, 160, 21), // "ROS::Comm::LoginState"
QT_MOC_LITERAL(14, 182, 13), // "onSocketError"
QT_MOC_LITERAL(15, 196, 3), // "err"
QT_MOC_LITERAL(16, 200, 15), // "receiveSentence"
QT_MOC_LITERAL(17, 216, 20), // "onSocketStateChanges"
QT_MOC_LITERAL(18, 237, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(19, 266, 13), // "setRouterName"
QT_MOC_LITERAL(20, 280, 10), // "routerName"
QT_MOC_LITERAL(21, 291, 13), // "setRemoteHost"
QT_MOC_LITERAL(22, 305, 4), // "addr"
QT_MOC_LITERAL(23, 310, 4), // "port"
QT_MOC_LITERAL(24, 315, 15), // "setUserNamePass"
QT_MOC_LITERAL(25, 331, 5), // "uname"
QT_MOC_LITERAL(26, 337, 5), // "upass"
QT_MOC_LITERAL(27, 343, 12), // "connectToROS"
QT_MOC_LITERAL(28, 356, 8), // "closeCom"
QT_MOC_LITERAL(29, 365, 5) // "force"

    },
    "ROS::Comm\0comError\0\0ROS::Comm::CommError\0"
    "ce\0QAbstractSocket::SocketError\0se\0"
    "comReceive\0ROS::QSentence&\0s\0"
    "comStateChanged\0ROS::Comm::CommState\0"
    "loginStateChanged\0ROS::Comm::LoginState\0"
    "onSocketError\0err\0receiveSentence\0"
    "onSocketStateChanges\0QAbstractSocket::SocketState\0"
    "setRouterName\0routerName\0setRemoteHost\0"
    "addr\0port\0setUserNamePass\0uname\0upass\0"
    "connectToROS\0closeCom\0force"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ROS__Comm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,
      10,    1,   87,    2, 0x06 /* Public */,
      12,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   93,    2, 0x08 /* Private */,
      16,    0,   96,    2, 0x08 /* Private */,
      17,    1,   97,    2, 0x08 /* Private */,
      19,    1,  100,    2, 0x0a /* Public */,
      21,    2,  103,    2, 0x0a /* Public */,
      24,    2,  108,    2, 0x0a /* Public */,
      27,    0,  113,    2, 0x0a /* Public */,
      28,    1,  114,    2, 0x0a /* Public */,
      28,    0,  117,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 13,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,    9,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Void,

       0        // eod
};

void ROS::Comm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Comm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->comError((*reinterpret_cast< ROS::Comm::CommError(*)>(_a[1])),(*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[2]))); break;
        case 1: _t->comReceive((*reinterpret_cast< ROS::QSentence(*)>(_a[1]))); break;
        case 2: _t->comStateChanged((*reinterpret_cast< ROS::Comm::CommState(*)>(_a[1]))); break;
        case 3: _t->loginStateChanged((*reinterpret_cast< ROS::Comm::LoginState(*)>(_a[1]))); break;
        case 4: _t->onSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->receiveSentence(); break;
        case 6: _t->onSocketStateChanges((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 7: _t->setRouterName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setRemoteHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 9: _t->setUserNamePass((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->connectToROS(); break;
        case 11: _t->closeCom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->closeCom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Comm::*)(ROS::Comm::CommError , QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Comm::comError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Comm::*)(ROS::QSentence & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Comm::comReceive)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Comm::*)(ROS::Comm::CommState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Comm::comStateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Comm::*)(ROS::Comm::LoginState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Comm::loginStateChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ROS::Comm::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ROS__Comm.data,
    qt_meta_data_ROS__Comm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ROS::Comm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ROS::Comm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ROS__Comm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ROS::Comm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ROS::Comm::comError(ROS::Comm::CommError _t1, QAbstractSocket::SocketError _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ROS::Comm::comReceive(ROS::QSentence & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ROS::Comm::comStateChanged(ROS::Comm::CommState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ROS::Comm::loginStateChanged(ROS::Comm::LoginState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
