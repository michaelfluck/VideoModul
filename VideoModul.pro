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
    camera.cpp \
    picproc.cpp \
    dataaquisition.cpp \
    xmlreader.cpp

HEADERS += \
    camera.h \
    picproc.h \
    const_global.h \
    dataaquisition.h \
    xmlreader.h

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
