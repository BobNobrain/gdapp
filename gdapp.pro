QT += core
QT += network
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
    gda/keypose/keyposegda.cpp \
    common/gesturelibrary.cpp \
    fp/webcameraframeproducer.cpp \
    common/util/displayframeconsumer.cpp \
    common/pipebuilder.cpp \
    gda/neuro/neurogda.cpp \
    gda/neuro/neuralnet.cpp \
    gda/neuro/caffeneuralnet.cpp \
    gda/neuro/image227keyposedescriptor.cpp \
    gda/stub/stubgda.cpp \
    gl/loggergesturelistener.cpp \
    gl/appclosegesturelistener.cpp \
    fp/netcameraframeproducer.cpp

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
    gda/keypose/keyposegda.h \
    common/gesturelibrary.h \
    fp/webcameraframeproducer.h \
    common/util/displayframeconsumer.h \
    common/pipebuilder.h \
    gda/neuro/neurogda.h \
    gda/neuro/neuralnet.h \
    gda/neuro/caffeneuralnet.h \
    gda/neuro/image227keyposedescriptor.h \
    gda/stub/stubgda.h \
    gl/loggergesturelistener.h \
    gl/appclosegesturelistener.h \
    fp/netcameraframeproducer.h

include(libs.pri)
