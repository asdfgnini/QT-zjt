/****************************************************************************
** Meta object code from reading C++ file 'tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../network02/network/tcpserver.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSTCPServerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTCPServerENDCLASS = QtMocHelpers::stringData(
    "TCPServer",
    "on_newConnection",
    "",
    "on_acceptError",
    "QAbstractSocket::SocketError",
    "socketError",
    "on_but_connect_clicked",
    "on_disconnected",
    "on_readyRead",
    "on_but_clearRecv_clicked",
    "on_but_clearSend_clicked",
    "on_check_hexRecv_clicked",
    "checked",
    "on_check_hexSend_clicked",
    "on_but_send_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTCPServerENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[10];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[29];
    char stringdata5[12];
    char stringdata6[23];
    char stringdata7[16];
    char stringdata8[13];
    char stringdata9[25];
    char stringdata10[25];
    char stringdata11[25];
    char stringdata12[8];
    char stringdata13[25];
    char stringdata14[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTCPServerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTCPServerENDCLASS_t qt_meta_stringdata_CLASSTCPServerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "TCPServer"
        QT_MOC_LITERAL(10, 16),  // "on_newConnection"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 14),  // "on_acceptError"
        QT_MOC_LITERAL(43, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(72, 11),  // "socketError"
        QT_MOC_LITERAL(84, 22),  // "on_but_connect_clicked"
        QT_MOC_LITERAL(107, 15),  // "on_disconnected"
        QT_MOC_LITERAL(123, 12),  // "on_readyRead"
        QT_MOC_LITERAL(136, 24),  // "on_but_clearRecv_clicked"
        QT_MOC_LITERAL(161, 24),  // "on_but_clearSend_clicked"
        QT_MOC_LITERAL(186, 24),  // "on_check_hexRecv_clicked"
        QT_MOC_LITERAL(211, 7),  // "checked"
        QT_MOC_LITERAL(219, 24),  // "on_check_hexSend_clicked"
        QT_MOC_LITERAL(244, 19)   // "on_but_send_clicked"
    },
    "TCPServer",
    "on_newConnection",
    "",
    "on_acceptError",
    "QAbstractSocket::SocketError",
    "socketError",
    "on_but_connect_clicked",
    "on_disconnected",
    "on_readyRead",
    "on_but_clearRecv_clicked",
    "on_but_clearSend_clicked",
    "on_check_hexRecv_clicked",
    "checked",
    "on_check_hexSend_clicked",
    "on_but_send_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTCPServerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    1,   75,    2, 0x08,    2 /* Private */,
       6,    0,   78,    2, 0x08,    4 /* Private */,
       7,    0,   79,    2, 0x08,    5 /* Private */,
       8,    0,   80,    2, 0x08,    6 /* Private */,
       9,    0,   81,    2, 0x08,    7 /* Private */,
      10,    0,   82,    2, 0x08,    8 /* Private */,
      11,    1,   83,    2, 0x08,    9 /* Private */,
      13,    1,   86,    2, 0x08,   11 /* Private */,
      14,    0,   89,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TCPServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTCPServerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTCPServerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTCPServerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TCPServer, std::true_type>,
        // method 'on_newConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_acceptError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'on_but_connect_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_readyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_but_clearRecv_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_but_clearSend_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_check_hexRecv_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_check_hexSend_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_but_send_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TCPServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCPServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_newConnection(); break;
        case 1: _t->on_acceptError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 2: _t->on_but_connect_clicked(); break;
        case 3: _t->on_disconnected(); break;
        case 4: _t->on_readyRead(); break;
        case 5: _t->on_but_clearRecv_clicked(); break;
        case 6: _t->on_but_clearSend_clicked(); break;
        case 7: _t->on_check_hexRecv_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->on_check_hexSend_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->on_but_send_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *TCPServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTCPServerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TCPServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
