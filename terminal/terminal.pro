#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T21:07:53
#
#-------------------------------------------------

QT       += core gui
QT      += core

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    QT += serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = terminal
TEMPLATE = app


SOURCES += main.cpp\
        terminal.cpp

HEADERS  += terminal.h
