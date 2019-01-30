#-------------------------------------------------
#
# Project created by QtCreator 2019-01-23T13:25:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileIndexer
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    searchfiles.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    searchfiles.h \
    controller.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
