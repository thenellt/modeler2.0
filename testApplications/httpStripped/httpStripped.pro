#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T13:40:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = httpStripped
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp

HEADERS  += mainwindow.h \
    map.h

FORMS    += mainwindow.ui
