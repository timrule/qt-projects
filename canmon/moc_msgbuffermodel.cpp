/****************************************************************************
** Meta object code from reading C++ file 'msgbuffermodel.h'
**
** Created: Tue Feb 11 13:16:00 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "msgbuffermodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msgbuffermodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MsgBufferModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      24,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   15,   15,   15, 0x0a,
      46,   42,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MsgBufferModel[] = {
    "MsgBufferModel\0\0start()\0stop()\0"
    "timerHit()\0msg\0newMsg(canMessage*)\0"
};

void MsgBufferModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MsgBufferModel *_t = static_cast<MsgBufferModel *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        case 2: _t->timerHit(); break;
        case 3: _t->newMsg((*reinterpret_cast< canMessage*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MsgBufferModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MsgBufferModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_MsgBufferModel,
      qt_meta_data_MsgBufferModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MsgBufferModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MsgBufferModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MsgBufferModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MsgBufferModel))
        return static_cast<void*>(const_cast< MsgBufferModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int MsgBufferModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MsgBufferModel::start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MsgBufferModel::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
