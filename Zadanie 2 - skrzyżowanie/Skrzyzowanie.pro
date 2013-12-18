#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T11:33:22
# Tylko dla QT większego niż 5.0
#-------------------------------------------------

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skrzyzowanie
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sygnalizator.cpp \
    staloczasowy.cpp \
    skrzyzowanie.cpp \
    inteligentne.cpp \
    auto.cpp

HEADERS  += mainwindow.h \
    sygnalizator.h \
    staloczasowy.h \
    skrzyzowanie.h \
    inteligentne.h \
    auto.h

FORMS    += mainwindow.ui

#endif
