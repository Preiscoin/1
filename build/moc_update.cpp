/****************************************************************************
** Meta object code from reading C++ file 'update.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/update.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'update.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpdateManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   27,   27,   27, 0x05,
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   27,   27,   27, 0x08,
      50,   27,   27,   27, 0x08,
      66,   98,   27,   27, 0x08,
     123,   27,   27,   27, 0x08,
     142,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UpdateManager[] = {
    "UpdateManager\0latest(bool)\0\0downloaded()\0"
    "update()\0startDownload()\0"
    "downloadProgress(qint64,qint64)\0"
    "bytesReceived,bytesTotal\0downloadFinished()\0"
    "downloadReadyRead()\0"
};

void UpdateManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpdateManager *_t = static_cast<UpdateManager *>(_o);
        switch (_id) {
        case 0: _t->latest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->downloaded(); break;
        case 2: _t->update(); break;
        case 3: _t->startDownload(); break;
        case 4: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->downloadFinished(); break;
        case 6: _t->downloadReadyRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UpdateManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UpdateManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UpdateManager,
      qt_meta_data_UpdateManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpdateManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpdateManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpdateManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateManager))
        return static_cast<void*>(const_cast< UpdateManager*>(this));
    return QObject::qt_metacast(_clname);
}

int UpdateManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UpdateManager::latest(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpdateManager::downloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
