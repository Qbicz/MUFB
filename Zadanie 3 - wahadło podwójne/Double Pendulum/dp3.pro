#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T20:05:52
#
#-------------------------------------------------

QT       += core gui
QT       += gui declarative
QT       += opengl
QT += printsupport

TARGET = dp3
TEMPLATE += app


SOURCES += main.cpp\
        mainwindow.cpp \
        widget.cpp \
        glwidget.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
        widget.h \
        glwidget.h \
        funkcje.h \
        qcustomplot.h

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/opengl/dp3
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS dp3.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/dp3
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)

FORMS    += mainwindow.ui
