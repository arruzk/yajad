#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T23:29:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yajad_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlitesearcher.cpp \
    databasemanager.cpp \
    radical.cpp

HEADERS  += mainwindow.hpp \
    sqlitesearcher.hpp \
    databasemanager.hpp \
    radical.h

FORMS    += mainwindow.ui \
    radical.ui
