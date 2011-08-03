#-------------------------------------------------
#
# Project created by QtCreator 2010-12-30T11:05:17
#
#-------------------------------------------------

QT       += core gui

TARGET = crysisbench
TEMPLATE = app
target.path=/usr/local/bin
INSTALLS=target

LIBS += -lpsapi

CONFIG += static

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Xsleep.h

FORMS    += mainwindow.ui
