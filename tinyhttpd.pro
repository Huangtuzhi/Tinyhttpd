#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T12:29:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += widgets

TARGET = tinyhttpd
CONFIG   -= app_bundle
CONFIG   += console
CONFIG += c++11

TEMPLATE = app


SOURCES +=\
    server.cpp \
    request.cpp \
    response.cpp \
    responsefile.cpp \
    responsedirectory.cpp \
    mime.cpp \
    main.cpp \
    serverthread.cpp \
    common.cpp \
    log.cpp \
    settings.cpp \
    database.cpp \
    monitorui.cpp \
    starter.cpp

HEADERS  += \
    server.h \
    request.h \
    response.h \
    httpstatus.h \
    common.h \
    responsefile.h \
    responsedirectory.h \
    mime.h \
    serverthread.h \
    log.h \
    settings.h \
    database.h \
    monitorui.h \
    starter.h

DISTFILES += \
    mime.txt

LIBS += \
    /usr/local/lib/libhiredis.so

FORMS += \
    monitorui.ui

RESOURCES += \
    icon.qrc
