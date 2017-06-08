QT += core
QT -= gui

CONFIG += c++11

TARGET = gdapp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    common/basicmodule.cpp \
    common/abstractframeproducer.cpp \
    common/abstractframeconsumer.cpp \
    common/abstractgesturedetector.cpp \
    common/abstractgesturelistener.cpp \
    gda/abstractgda.cpp \
    gda/common/abstractgesturedescriptor.cpp \
    gda/keypose/abstractposedescriptor.cpp \
    gda/keypose/keyposegesturedescriptor.cpp \
    gda/keypose/keyposegda.cpp

HEADERS += \
    common/basicmodule.h \
    common/abstractframeproducer.h \
    common/abstractframeconsumer.h \
    common/abstractgesturedetector.h \
    common/abstractgesturelistener.h \
    gda/abstractgda.h \
    gda/common/abstractgesturedescriptor.h \
    gda/keypose/abstractposedescriptor.h \
    gda/keypose/keyposegesturedescriptor.h \
    gda/keypose/keyposegda.h

include(libs.pri)
