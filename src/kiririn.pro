#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T18:08:40
#
#-------------------------------------------------

QT       += core gui sql

TARGET = kiririn
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loader.cpp \
    items/searchinfo.cpp \
    parsers/sankakuparser.cpp \
    parsers/parser.cpp \
    grabber.cpp \
    items/job.cpp \
    jobmanager.cpp \
    items/picinfo.cpp \
    items/postinfo.cpp

HEADERS  += mainwindow.h \
    loader.h \
    items/searchinfo.h \
    parsers/sankakuparser.h \
    parsers/parser.h \
    grabber.h \
    items/job.h \
    jobmanager.h \
    items/postinfo.h \
    items/picinfo.h

FORMS    += mainwindow.ui

LIBS += ../build/libcurl.dll

