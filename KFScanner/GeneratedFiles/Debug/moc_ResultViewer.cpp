/****************************************************************************
** Meta object code from reading C++ file 'ResultViewer.h'
**
** Created: Mon Dec 21 10:25:28 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ResultViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResultViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   13,   31,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ResultViewer[] = {
    "ResultViewer\0\0delete_pressed()\0bool\0"
    "remove_point()\0"
};

void ResultViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ResultViewer *_t = static_cast<ResultViewer *>(_o);
        switch (_id) {
        case 0: _t->delete_pressed(); break;
        case 1: { bool _r = _t->remove_point();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ResultViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ResultViewer::staticMetaObject = {
    { &QGLViewer::staticMetaObject, qt_meta_stringdata_ResultViewer,
      qt_meta_data_ResultViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResultViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResultViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResultViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResultViewer))
        return static_cast<void*>(const_cast< ResultViewer*>(this));
    return QGLViewer::qt_metacast(_clname);
}

int ResultViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ResultViewer::delete_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
