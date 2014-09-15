#-------------------------------------------------
#
# Project created by QtCreator 2011-08-03T14:59:51
#
#-------------------------------------------------

QT += core \
    gui \
    opengl \
    qt3support

TARGET = raycaster_template
TEMPLATE = app


SOURCES += main.cpp \
    Volume.cpp \
    main_window.cpp \
    gl_cube_widget.cpp \
    gl_dvr_widget.cpp \
    gl_slicer_widget.cpp \
    gl_tf_widget.cpp \
    TransferFunction.cpp

HEADERS  += Volume.h     \
    Vector3.h \
    Matrix4.h \
    Vector3.h \
    Matrix4.h \
    gl_cube_widget.h \
    gl_dvr_widget.h \
    gl_slicer_widget.h \
    gl_tf_widget.h \
    main_window.h \
    TransferFunction.h

FORMS    +=


QMAKE_CXXFLAGS += -std=c++11
# disable warning for unreferenced variables
# QMAKE_CXXFLAGS += /wd4100 	# Works only in Windows, there should be an equivalent for linux and mac

