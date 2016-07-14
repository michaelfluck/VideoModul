#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T11:42:46
#
#-------------------------------------------------

QT       += core
QT       += xml
QT       -= gui

TARGET = VideoModul
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    picproc.cpp \
    dataaquisition.cpp \
    xmlreader.cpp \
    gpio.cpp \
    video.cpp \
    fuelgauge.cpp \
    ledproc.cpp

HEADERS += \
    camera.h \
    picproc.h \
    const_global.h \
    dataaquisition.h \
    xmlreader.h \
    gpio.h \
    video.h \
    fuelgauge.h \
    ledproc.h

INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local/include

LIBS += -L/usr/lib
LIBS += -L/usr/local/lib

LIBS += -lopencv_core \
    -lopencv_highgui \
    -lopencv_nonfree \
    -lopencv_imgproc \
    -lopencv_objdetect \
    -lopencv_features2d \
    -lopencv_video \
    -lraspicam \
    -lraspicam_cv

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpigpio

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

