/****************************************************************************
** Meta object code from reading C++ file 'mainform.h'
**
** Created: Fri May 22 22:10:08 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainform[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      39,    9,    9,    9, 0x08,
      67,    9,    9,    9, 0x08,
      94,    9,    9,    9, 0x08,
     123,    9,    9,    9, 0x08,
     154,    9,    9,    9, 0x08,
     171,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mainform[] = {
    "mainform\0\0on_connectKinect_triggered()\0"
    "on_ToolstartBtn_triggered()\0"
    "on_ToolstopBtn_triggered()\0"
    "on_TooldeleteBtn_triggered()\0"
    "on_actionSaveCloud_triggered()\0"
    "resetToDefault()\0onShowCloudBtn()\0"
};

void mainform::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainform *_t = static_cast<mainform *>(_o);
        switch (_id) {
        case 0: _t->on_connectKinect_triggered(); break;
        case 1: _t->on_ToolstartBtn_triggered(); break;
        case 2: _t->on_ToolstopBtn_triggered(); break;
        case 3: _t->on_TooldeleteBtn_triggered(); break;
        case 4: _t->on_actionSaveCloud_triggered(); break;
        case 5: _t->resetToDefault(); break;
        case 6: _t->onShowCloudBtn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData mainform::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainform::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainform,
      qt_meta_data_mainform, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainform::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainform::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainform::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainform))
        return static_cast<void*>(const_cast< mainform*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainform::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
