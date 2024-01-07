/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../demo02/thread/worker.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWorkerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWorkerENDCLASS = QtMocHelpers::stringData(
    "Worker",
    "resultReady",
    "",
    "uchar*",
    "p",
    "w",
    "h",
    "worker_new_frame",
    "on_doSomething",
    "Media*",
    "media",
    "out_buffer"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWorkerENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[7];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[2];
    char stringdata5[2];
    char stringdata6[2];
    char stringdata7[17];
    char stringdata8[15];
    char stringdata9[7];
    char stringdata10[6];
    char stringdata11[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWorkerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWorkerENDCLASS_t qt_meta_stringdata_CLASSWorkerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Worker"
        QT_MOC_LITERAL(7, 11),  // "resultReady"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 6),  // "uchar*"
        QT_MOC_LITERAL(27, 1),  // "p"
        QT_MOC_LITERAL(29, 1),  // "w"
        QT_MOC_LITERAL(31, 1),  // "h"
        QT_MOC_LITERAL(33, 16),  // "worker_new_frame"
        QT_MOC_LITERAL(50, 14),  // "on_doSomething"
        QT_MOC_LITERAL(65, 6),  // "Media*"
        QT_MOC_LITERAL(72, 5),  // "media"
        QT_MOC_LITERAL(78, 10)   // "out_buffer"
    },
    "Worker",
    "resultReady",
    "",
    "uchar*",
    "p",
    "w",
    "h",
    "worker_new_frame",
    "on_doSomething",
    "Media*",
    "media",
    "out_buffer"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWorkerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   32,    2, 0x06,    1 /* Public */,
       7,    0,   39,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    2,   40,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 3,   10,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSWorkerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWorkerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWorkerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Worker, std::true_type>,
        // method 'resultReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'worker_new_frame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_doSomething'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Media *, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>
    >,
    nullptr
} };

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->worker_new_frame(); break;
        case 2: _t->on_doSomething((*reinterpret_cast< std::add_pointer_t<Media*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(unsigned char * , int , int );
            if (_t _q_method = &Worker::resultReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)();
            if (_t _q_method = &Worker::worker_new_frame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWorkerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Worker::resultReady(unsigned char * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::worker_new_frame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSControllerENDCLASS = QtMocHelpers::stringData(
    "Controller",
    "startRunning",
    "",
    "Media*",
    "media",
    "uchar*",
    "out_buffer",
    "send_IMG",
    "p",
    "w",
    "h",
    "newframe",
    "on_receivResult",
    "on_newframe"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSControllerENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[6];
    char stringdata5[7];
    char stringdata6[11];
    char stringdata7[9];
    char stringdata8[2];
    char stringdata9[2];
    char stringdata10[2];
    char stringdata11[9];
    char stringdata12[16];
    char stringdata13[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSControllerENDCLASS_t qt_meta_stringdata_CLASSControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "Controller"
        QT_MOC_LITERAL(11, 12),  // "startRunning"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 6),  // "Media*"
        QT_MOC_LITERAL(32, 5),  // "media"
        QT_MOC_LITERAL(38, 6),  // "uchar*"
        QT_MOC_LITERAL(45, 10),  // "out_buffer"
        QT_MOC_LITERAL(56, 8),  // "send_IMG"
        QT_MOC_LITERAL(65, 1),  // "p"
        QT_MOC_LITERAL(67, 1),  // "w"
        QT_MOC_LITERAL(69, 1),  // "h"
        QT_MOC_LITERAL(71, 8),  // "newframe"
        QT_MOC_LITERAL(80, 15),  // "on_receivResult"
        QT_MOC_LITERAL(96, 11)   // "on_newframe"
    },
    "Controller",
    "startRunning",
    "",
    "Media*",
    "media",
    "uchar*",
    "out_buffer",
    "send_IMG",
    "p",
    "w",
    "h",
    "newframe",
    "on_receivResult",
    "on_newframe"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSControllerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    1 /* Public */,
       7,    3,   49,    2, 0x06,    4 /* Public */,
      11,    0,   56,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    3,   57,    2, 0x0a,    9 /* Public */,
      13,    0,   64,    2, 0x0a,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Controller, std::true_type>,
        // method 'startRunning'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Media *, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>,
        // method 'send_IMG'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'newframe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_receivResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_newframe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Controller *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startRunning((*reinterpret_cast< std::add_pointer_t<Media*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[2]))); break;
        case 1: _t->send_IMG((*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->newframe(); break;
        case 3: _t->on_receivResult((*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->on_newframe(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Controller::*)(Media * , unsigned char * );
            if (_t _q_method = &Controller::startRunning; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Controller::*)(unsigned char * , int , int );
            if (_t _q_method = &Controller::send_IMG; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Controller::*)();
            if (_t _q_method = &Controller::newframe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Controller::startRunning(Media * _t1, unsigned char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::send_IMG(unsigned char * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::newframe()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
