#-------------------------------------------------
#
# Project created by QtCreator 2019-11-19T11:58:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elapsedTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    worker.h

FORMS    += mainwindow.ui
