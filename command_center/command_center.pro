#-------------------------------------------------
#
# Project created by QtCreator 2014-10-03T08:26:28
#
#-------------------------------------------------

QT += core gui

linux:QT += bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = command_center
TEMPLATE = app

#CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        gui.cpp \
    core.cpp \
    message.cpp \
    btinterface.cpp

HEADERS  += gui.h \
    core.h \
    glob.h \
    message.h \
    btinterface.h

FORMS    += gui.ui
