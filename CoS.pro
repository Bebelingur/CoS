#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T14:34:21
#
#-------------------------------------------------

<<<<<<< HEAD
QT       += core gui sql
=======

QT       += core gui sql


>>>>>>> 73f0b5c745c3dc935014751346c24557030ca3cc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    services.cpp

HEADERS  += mainwindow.h \
    comptype.h \
    data.h \
    infotype.h \
    relations.h \
    relationstype.h \
    services.h

FORMS    += mainwindow.ui
