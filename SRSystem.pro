#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T17:45:19
#
#-------------------------------------------------

QT       += core gui  multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SRSystem
TEMPLATE = app

INCLUDEPATH +=  $$PWD/Lib/QCustomPlot/ \
                $$PWD/Source/ \
                $$PWD/GeneratedFiles/

HEADERS += \
    Lib/fftw3/fftw3.h \
    Lib/QCustomPlot/qcustomplot.h \
    Source/centroid.h \
    Source/codebook.h \
    Source/database.h \
    Source/device.h \
    Source/endpoint_detector.h \
    Source/iobserver.h \
    Source/main_form.h \
    Source/mfcc_processor.h \
    Source/point.h \
    Source/sr_engine.h \
    Source/util.h

SOURCES += \
    Lib/QCustomPlot/qcustomplot.cpp \
    Source/centroid.cpp \
    Source/codebook.cpp \
    Source/database.cpp \
    Source/device.cpp \
    Source/endpoint_detector.cpp \
    Source/main.cpp \
    Source/main_form.cpp \
    Source/mfcc_processor.cpp \
    Source/point.cpp \
    Source/sr_engine.cpp \
    Source/util.cpp

FORMS += \
    Forms/main_form.ui

unix|win32: LIBS += -L$$PWD/Lib/fftw3/ -llibfftw3-3

INCLUDEPATH += $$PWD/Lib/fftw3
DEPENDPATH += $$PWD/Lib/fftw3
