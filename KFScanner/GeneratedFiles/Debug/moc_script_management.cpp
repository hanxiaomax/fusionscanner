/****************************************************************************
** Meta object code from reading C++ file 'script_management.h'
**
** Created: Tue Jun 2 14:55:35 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../script_management.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'script_management.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_script_Dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      36,   14,   14,   14, 0x08,
      57,   14,   14,   14, 0x08,
      78,   14,   14,   14, 0x08,
      99,   14,   14,   14, 0x08,
     125,   14,   14,   14, 0x08,
     148,   14,   14,   14, 0x08,
     163,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_script_Dialog[] = {
    "script_Dialog\0\0on_AddRbtn_clicked()\0"
    "on_AddVbtn_clicked()\0on_AddLbtn_clicked()\0"
    "on_AddTbtn_clicked()\0on_newScriptBtn_clicked()\0"
    "on_deleteBtn_clicked()\0updateScript()\0"
    "readScript()\0"
};

void script_Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        script_Dialog *_t = static_cast<script_Dialog *>(_o);
        switch (_id) {
        case 0: _t->on_AddRbtn_clicked(); break;
        case 1: _t->on_AddVbtn_clicked(); break;
        case 2: _t->on_AddLbtn_clicked(); break;
        case 3: _t->on_AddTbtn_clicked(); break;
        case 4: _t->on_newScriptBtn_clicked(); break;
        case 5: _t->on_deleteBtn_clicked(); break;
        case 6: _t->updateScript(); break;
        case 7: _t->readScript(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData script_Dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject script_Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_script_Dialog,
      qt_meta_data_script_Dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &script_Dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *script_Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *script_Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_script_Dialog))
        return static_cast<void*>(const_cast< script_Dialog*>(this));
    if (!strcmp(_clname, "Ui::sctiptDialog"))
        return static_cast< Ui::sctiptDialog*>(const_cast< script_Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int script_Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
