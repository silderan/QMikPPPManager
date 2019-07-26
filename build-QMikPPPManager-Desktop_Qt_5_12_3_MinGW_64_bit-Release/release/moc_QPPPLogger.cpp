/****************************************************************************
** Meta object code from reading C++ file 'QPPPLogger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Utils/QPPPLogger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPPPLogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QPPPLogger_t {
    QByteArrayData data[16];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QPPPLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QPPPLogger_t qt_meta_stringdata_QPPPLogger = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QPPPLogger"
QT_MOC_LITERAL(1, 11, 5), // "flush"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "shutdown"
QT_MOC_LITERAL(4, 27, 9), // "setLogDir"
QT_MOC_LITERAL(5, 37, 6), // "logDir"
QT_MOC_LITERAL(6, 44, 15), // "logAddingSecret"
QT_MOC_LITERAL(7, 60, 12), // "ROSPPPSecret"
QT_MOC_LITERAL(8, 73, 9), // "pppSecret"
QT_MOC_LITERAL(9, 83, 17), // "logDeletingSecret"
QT_MOC_LITERAL(10, 101, 17), // "logChangingSecret"
QT_MOC_LITERAL(11, 119, 9), // "oldSecret"
QT_MOC_LITERAL(12, 129, 9), // "newSecret"
QT_MOC_LITERAL(13, 139, 8), // "readLogs"
QT_MOC_LITERAL(14, 148, 15), // "QPPPLogDataList"
QT_MOC_LITERAL(15, 164, 8) // "userName"

    },
    "QPPPLogger\0flush\0\0shutdown\0setLogDir\0"
    "logDir\0logAddingSecret\0ROSPPPSecret\0"
    "pppSecret\0logDeletingSecret\0"
    "logChangingSecret\0oldSecret\0newSecret\0"
    "readLogs\0QPPPLogDataList\0userName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QPPPLogger[] = {

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
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x0a /* Public */,
       5,    0,   64,    2, 0x0a /* Public */,
       6,    1,   65,    2, 0x0a /* Public */,
       9,    1,   68,    2, 0x0a /* Public */,
      10,    2,   71,    2, 0x0a /* Public */,
      13,    1,   76,    2, 0x0a /* Public */,
      13,    0,   79,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,   11,   12,
    0x80000000 | 14, QMetaType::QString,   15,
    0x80000000 | 14,

       0        // eod
};

void QPPPLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPPPLogger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flush(); break;
        case 1: _t->shutdown(); break;
        case 2: _t->setLogDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->logDir(); break;
        case 4: _t->logAddingSecret((*reinterpret_cast< const ROSPPPSecret(*)>(_a[1]))); break;
        case 5: _t->logDeletingSecret((*reinterpret_cast< const ROSPPPSecret(*)>(_a[1]))); break;
        case 6: _t->logChangingSecret((*reinterpret_cast< const ROSPPPSecret(*)>(_a[1])),(*reinterpret_cast< const ROSPPPSecret(*)>(_a[2]))); break;
        case 7: { QPPPLogDataList _r = _t->readLogs((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPPPLogDataList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QPPPLogDataList _r = _t->readLogs();
            if (_a[0]) *reinterpret_cast< QPPPLogDataList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QPPPLogger::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QPPPLogger.data,
    qt_meta_data_QPPPLogger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QPPPLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPPPLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QPPPLogger.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QPPPLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
