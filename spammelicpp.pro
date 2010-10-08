QT += core \
    network
QT -= gui
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
TARGET = 

include(listeners/listeners.pri)

HEADERS += bot.h \
    irc.h \
    listener.h \
    event_dispatcher.h \
    event.h \
    message.h \
    irc_stream.h \
    messagequeue.h
SOURCES += bot.cpp \
    irc.cpp \
    main.cpp \
    event_dispatcher.cpp \
    message.cpp \
    irc_stream.cpp \
    messagequeue.cpp
