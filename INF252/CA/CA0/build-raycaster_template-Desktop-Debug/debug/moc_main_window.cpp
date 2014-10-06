/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../INF252_raycaster_template/main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      25,   11,   11,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      61,   56,   11,   11, 0x0a,
      89,   83,   11,   11, 0x0a,
     116,  112,   11,   11, 0x0a,
     139,  136,   11,   11, 0x0a,
     171,  136,   11,   11, 0x0a,
     211,  136,   11,   11, 0x0a,
     238,  136,   11,   11, 0x0a,
     270,  136,   11,   11, 0x0a,
     305,  299,   11,   11, 0x0a,
     337,  136,   11,   11, 0x0a,
     365,  136,   11,   11, 0x0a,
     391,  136,   11,   11, 0x0a,
     422,  136,   11,   11, 0x0a,
     457,   11,   11,   11, 0x0a,
     467,   11,   11,   11, 0x0a,
     476,   11,   11,   11, 0x0a,
     492,  485,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0loadVolume()\0openTFEditor()\0"
    "updateContent()\0axis\0changeSlicerAxis(int)\0"
    "slice\0changeSlicerSlice(int)\0exp\0"
    "changeContrast(int)\0id\0"
    "changeDvrDynamicResolution(int)\0"
    "changeDvrGradientInterpolationMode(int)\0"
    "changeDvrGradientMode(int)\0"
    "changeDvrInterpolationMode(int)\0"
    "changeDvrProjectionMode(int)\0value\0"
    "changeDvrRayCastingStep(double)\0"
    "changeDvrRenderingMode(int)\0"
    "changeDvrShadingType(int)\0"
    "changeDvrStaticResolution(int)\0"
    "changeDvrTransferFunctionType(int)\0"
    "resetTF()\0loadTF()\0saveTF()\0enable\0"
    "logTF(bool)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->loadVolume(); break;
        case 1: _t->openTFEditor(); break;
        case 2: _t->updateContent(); break;
        case 3: _t->changeSlicerAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeSlicerSlice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->changeDvrDynamicResolution((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeDvrGradientInterpolationMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->changeDvrGradientMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeDvrInterpolationMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changeDvrProjectionMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->changeDvrRayCastingStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->changeDvrRenderingMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->changeDvrShadingType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->changeDvrStaticResolution((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->changeDvrTransferFunctionType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->resetTF(); break;
        case 17: _t->loadTF(); break;
        case 18: _t->saveTF(); break;
        case 19: _t->logTF((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
