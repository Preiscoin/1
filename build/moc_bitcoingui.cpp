/****************************************************************************
** Meta object code from reading C++ file 'bitcoingui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/bitcoingui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bitcoingui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BitcoinGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   34,   40,   40, 0x0a,
      41,   63,   40,   40, 0x0a,
      82,  107,   40,   40, 0x0a,
     114,  134,   40,   40, 0x0a,
     150,  186,   40,   40, 0x0a,
     210,  240,   40,   40, 0x2a,
     260,  281,   40,   40, 0x0a,
     301,  320,   40,   40, 0x0a,
     327,  383,   40,   40, 0x0a,
     413,   40,   40,   40, 0x08,
     432,   40,   40,   40, 0x08,
     449,   40,   40,   40, 0x08,
     467,   40,   40,   40, 0x08,
     489,   40,   40,   40, 0x08,
     512,  539,   40,   40, 0x08,
     544,   40,   40,   40, 0x28,
     564,  539,   40,   40, 0x08,
     592,   40,   40,   40, 0x28,
     613,  539,   40,   40, 0x08,
     643,   40,   40,   40, 0x28,
     666,   40,   40,   40, 0x08,
     683,   40,   40,   40, 0x08,
     698,  726,   40,   40, 0x08,
     740,   40,   40,   40, 0x28,
     764,   40,   40,   40, 0x08,
     779,   40,   40,   40, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BitcoinGUI[] = {
    "BitcoinGUI\0setNumConnections(int)\0"
    "count\0\0setNumBlocks(int,int)\0"
    "count,nTotalBlocks\0setEncryptionStatus(int)\0"
    "status\0setMining(bool,int)\0mining,hashrate\0"
    "message(QString,QString,uint,bool*)\0"
    "title,message,style,ret\0"
    "message(QString,QString,uint)\0"
    "title,message,style\0askFee(qint64,bool*)\0"
    "nFeeRequired,payFee\0handleURI(QString)\0"
    "strURI\0incomingTransaction(QString,int,qint64,QString,QString)\0"
    "date,unit,amount,type,address\0"
    "gotoOverviewPage()\0gotoMiningPage()\0"
    "gotoHistoryPage()\0gotoAddressBookPage()\0"
    "gotoReceiveCoinsPage()\0"
    "gotoSendCoinsPage(QString)\0addr\0"
    "gotoSendCoinsPage()\0gotoSignMessageTab(QString)\0"
    "gotoSignMessageTab()\0gotoVerifyMessageTab(QString)\0"
    "gotoVerifyMessageTab()\0optionsClicked()\0"
    "aboutClicked()\0showNormalIfMinimized(bool)\0"
    "fToggleHidden\0showNormalIfMinimized()\0"
    "toggleHidden()\0detectShutdown()\0"
};

void BitcoinGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BitcoinGUI *_t = static_cast<BitcoinGUI *>(_o);
        switch (_id) {
        case 0: _t->setNumConnections((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setNumBlocks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setEncryptionStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMining((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->message((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool*(*)>(_a[4]))); break;
        case 5: _t->message((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 6: _t->askFee((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 7: _t->handleURI((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->incomingTransaction((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 9: _t->gotoOverviewPage(); break;
        case 10: _t->gotoMiningPage(); break;
        case 11: _t->gotoHistoryPage(); break;
        case 12: _t->gotoAddressBookPage(); break;
        case 13: _t->gotoReceiveCoinsPage(); break;
        case 14: _t->gotoSendCoinsPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->gotoSendCoinsPage(); break;
        case 16: _t->gotoSignMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->gotoSignMessageTab(); break;
        case 18: _t->gotoVerifyMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->gotoVerifyMessageTab(); break;
        case 20: _t->optionsClicked(); break;
        case 21: _t->aboutClicked(); break;
        case 22: _t->showNormalIfMinimized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->showNormalIfMinimized(); break;
        case 24: _t->toggleHidden(); break;
        case 25: _t->detectShutdown(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BitcoinGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BitcoinGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BitcoinGUI,
      qt_meta_data_BitcoinGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BitcoinGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BitcoinGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BitcoinGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BitcoinGUI))
        return static_cast<void*>(const_cast< BitcoinGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BitcoinGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
