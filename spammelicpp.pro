QT += core
QT -= gui

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

TARGET = 

HEADERS += bot.h \
        irc.h \
        listener.h

SOURCES += bot.cpp \
        irc.cpp \
        main.cpp
