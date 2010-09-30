QT += core network
QT -= gui
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
TARGET = 
HEADERS += bot.h \
    irc.h \
    listener.h \
    event_dispatcher.h \
    event.h \
    message.h
SOURCES += bot.cpp \
    irc.cpp \
    main.cpp \
    event_dispatcher.cpp \
    message.cpp
