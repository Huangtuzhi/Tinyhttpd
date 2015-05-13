#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T12:29:02
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = tinyhttpd
CONFIG   += console
CONFIG   -= app_bundle

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
    database.cpp

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
    database.h

DISTFILES += \
    mime.txt

LIBS += \
    /usr/local/lib/libhiredis.so
