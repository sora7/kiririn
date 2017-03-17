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
    boorutest.cpp \
    grabber.cpp \
    items/job.cpp \
    jobmanager.cpp \
    items/picinfo.cpp \
    items/postinfo.cpp \
    parsers/sankakuparser.cpp \
    parsers/mishimmieparser.cpp \
    parsers/fourchanhouseparser.cpp \
    parsers/shimmieparser.cpp \
    parsers/idolcomplexparser.cpp \
    parsers/konachanparser.cpp \
    parsers/sankakuchannelparser.cpp \
    parsers/booruparser.cpp \
    parsers/yandereparser.cpp

HEADERS  += mainwindow.h \
    loader.h \
    items/searchinfo.h \
    grabber.h \
    items/job.h \
    jobmanager.h \
    items/postinfo.h \
    items/picinfo.h \
    boorutest.h \
    parsers/sankakuparser.h \
    parsers/mishimmieparser.h \
    parsers/fourchanhouseparser.h \
    parsers/shimmieparser.h \
    parsers/idolcomplexparser.h \
    parsers/konachanparser.h \
    parsers/sankakuchannelparser.h \
    parsers/booruparser.h \
    parsers/yandereparser.h

FORMS    += mainwindow.ui

LIBS += ../build/libcurl.dll

