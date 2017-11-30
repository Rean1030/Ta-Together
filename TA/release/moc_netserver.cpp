/****************************************************************************
** Meta object code from reading C++ file 'netserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../netserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetServer_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetServer_t qt_meta_stringdata_NetServer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NetServer"
QT_MOC_LITERAL(1, 10, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "broadcastDatagram"
QT_MOC_LITERAL(4, 53, 8), // "datagram"
QT_MOC_LITERAL(5, 62, 12), // "QHostAddress"
QT_MOC_LITERAL(6, 75, 9), // "dstAdress"
QT_MOC_LITERAL(7, 85, 7) // "dstPort"

    },
    "NetServer\0processPendingDatagrams\0\0"
    "broadcastDatagram\0datagram\0QHostAddress\0"
    "dstAdress\0dstPort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    3,   35,    2, 0x08 /* Private */,
       3,    2,   42,    2, 0x28 /* Private | MethodCloned */,
       3,    1,   47,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::LongLong, QMetaType::QByteArray, 0x80000000 | 5, QMetaType::UShort,    4,    6,    7,
    QMetaType::LongLong, QMetaType::QByteArray, 0x80000000 | 5,    4,    6,
    QMetaType::LongLong, QMetaType::QByteArray,    4,

       0        // eod
};

void NetServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetServer *_t = static_cast<NetServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processPendingDatagrams(); break;
        case 1: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 2: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 3: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject NetServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetServer.data,
      qt_meta_data_NetServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetServer.stringdata0))
        return static_cast<void*>(const_cast< NetServer*>(this));
    return QObject::qt_metacast(_clname);
}

int NetServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
