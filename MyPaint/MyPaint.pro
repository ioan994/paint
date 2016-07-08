#-------------------------------------------------
#
# Project created by QtCreator 2014-08-01T12:11:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPaint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    geoobj.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    geoobj.h

FORMS    += mainwindow.ui
