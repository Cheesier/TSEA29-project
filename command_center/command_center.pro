#-------------------------------------------------
#
# Project created by QtCreator 2014-10-03T08:26:28
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = command_center
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        gui.cpp \
    core.cpp \
    message.cpp

HEADERS  += gui.h \
    core.h \
    glob.h \
    message.h

FORMS    += gui.ui
