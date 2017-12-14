/****************************************************************************
** Meta object code from reading C++ file 'netserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../netserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpSocket_t {
    QByteArrayData data[11];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpSocket_t qt_meta_stringdata_UdpSocket = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UdpSocket"
QT_MOC_LITERAL(1, 10, 11), // "updateProjs"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "updateFiles"
QT_MOC_LITERAL(4, 35, 14), // "updateFileLogs"
QT_MOC_LITERAL(5, 50, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(6, 74, 17), // "broadcastDatagram"
QT_MOC_LITERAL(7, 92, 8), // "datagram"
QT_MOC_LITERAL(8, 101, 12), // "QHostAddress"
QT_MOC_LITERAL(9, 114, 9), // "dstAdress"
QT_MOC_LITERAL(10, 124, 7) // "dstPort"

    },
    "UdpSocket\0updateProjs\0\0updateFiles\0"
    "updateFileLogs\0processPendingDatagrams\0"
    "broadcastDatagram\0datagram\0QHostAddress\0"
    "dstAdress\0dstPort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    3,   53,    2, 0x08 /* Private */,
       6,    2,   60,    2, 0x28 /* Private | MethodCloned */,
       6,    1,   65,    2, 0x28 /* Private | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::LongLong, QMetaType::QByteArray, 0x80000000 | 8, QMetaType::UShort,    7,    9,   10,
    QMetaType::LongLong, QMetaType::QByteArray, 0x80000000 | 8,    7,    9,
    QMetaType::LongLong, QMetaType::QByteArray,    7,

       0        // eod
};

void UdpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpSocket *_t = static_cast<UdpSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateProjs(); break;
        case 1: _t->updateFiles(); break;
        case 2: _t->updateFileLogs(); break;
        case 3: _t->processPendingDatagrams(); break;
        case 4: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 5: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 6: { qint64 _r = _t->broadcastDatagram((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UdpSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocket::updateProjs)) {
                *result = 0;
            }
        }
        {
            typedef void (UdpSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocket::updateFiles)) {
                *result = 1;
            }
        }
        {
            typedef void (UdpSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocket::updateFileLogs)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject UdpSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpSocket.data,
      qt_meta_data_UdpSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UdpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UdpSocket.stringdata0))
        return static_cast<void*>(const_cast< UdpSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void UdpSocket::updateProjs()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void UdpSocket::updateFiles()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void UdpSocket::updateFileLogs()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
struct qt_meta_stringdata_TcpClient_t {
    QByteArrayData data[5];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClient_t qt_meta_stringdata_TcpClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpClient"
QT_MOC_LITERAL(1, 10, 4), // "send"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "goOnSend"
QT_MOC_LITERAL(4, 25, 8) // "numBytes"

    },
    "TcpClient\0send\0\0goOnSend\0numBytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    1,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    4,

       0        // eod
};

void TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClient *_t = static_cast<TcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send(); break;
        case 1: _t->goOnSend((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpClient.data,
      qt_meta_data_TcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClient.stringdata0))
        return static_cast<void*>(const_cast< TcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TcpServer_t {
    QByteArrayData data[4];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpServer_t qt_meta_stringdata_TcpServer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpServer"
QT_MOC_LITERAL(1, 10, 16), // "acceptConnection"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10) // "readClient"

    },
    "TcpServer\0acceptConnection\0\0readClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpServer *_t = static_cast<TcpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->acceptConnection(); break;
        case 1: _t->readClient(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TcpServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpServer.data,
      qt_meta_data_TcpServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpServer.stringdata0))
        return static_cast<void*>(const_cast< TcpServer*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
