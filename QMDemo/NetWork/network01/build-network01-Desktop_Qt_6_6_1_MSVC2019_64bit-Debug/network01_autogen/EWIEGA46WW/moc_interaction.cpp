/****************************************************************************
** Meta object code from reading C++ file 'interaction.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../network01/interaction.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interaction.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSInteractionENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSInteractionENDCLASS = QtMocHelpers::stringData(
    "Interaction",
    "signvalue",
    "",
    "value",
    "send",
    "hex",
    "connt",
    "ip",
    "port",
    "state",
    "setstate"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSInteractionENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[12];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[5];
    char stringdata5[4];
    char stringdata6[6];
    char stringdata7[3];
    char stringdata8[5];
    char stringdata9[6];
    char stringdata10[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInteractionENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSInteractionENDCLASS_t qt_meta_stringdata_CLASSInteractionENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "Interaction"
        QT_MOC_LITERAL(12, 9),  // "signvalue"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 5),  // "value"
        QT_MOC_LITERAL(29, 4),  // "send"
        QT_MOC_LITERAL(34, 3),  // "hex"
        QT_MOC_LITERAL(38, 5),  // "connt"
        QT_MOC_LITERAL(44, 2),  // "ip"
        QT_MOC_LITERAL(47, 4),  // "port"
        QT_MOC_LITERAL(52, 5),  // "state"
        QT_MOC_LITERAL(58, 8)   // "setstate"
    },
    "Interaction",
    "signvalue",
    "",
    "value",
    "send",
    "hex",
    "connt",
    "ip",
    "port",
    "state",
    "setstate"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInteractionENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   47,    2, 0x02,    3 /* Public */,
       6,    2,   50,    2, 0x02,    5 /* Public */,
       9,    0,   55,    2, 0x02,    8 /* Public */,
      10,    1,   56,    2, 0x02,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject Interaction::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSInteractionENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInteractionENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInteractionENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Interaction, std::true_type>,
        // method 'signvalue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'connt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'state'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setstate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void Interaction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Interaction *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signvalue((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->send((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->connt((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: { bool _r = _t->state();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setstate((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Interaction::*)(QString );
            if (_t _q_method = &Interaction::signvalue; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Interaction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interaction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInteractionENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Interaction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Interaction::signvalue(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
