#-------------------------------------------------
#
# Project created by QtCreator 2014-10-03T08:26:28
#
#-------------------------------------------------

QT += core gui

linux:QT += bluetooth
#for boost::shared_mutex
linux:LIBS += -lboost_thread -lboost_system -lpthread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = command_center
TEMPLATE = app

#CONFIG += c++11

QT += serialport

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        gui.cpp \
    core.cpp \
    message.cpp \
    btinterface.cpp \
    data.cpp \
    serial.cpp

HEADERS  += gui.h \
    core.h \
    glob.h \
    message.h \
    btinterface.h \
    data.h \
    serial.h

FORMS    += gui.ui
