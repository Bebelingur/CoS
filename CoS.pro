#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T14:34:21
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoS5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    services.cpp \
    editdialog.cpp \
    editcompdialog.cpp

HEADERS  += mainwindow.h \
    comptype.h \
    data.h \
    infotype.h \
    relationstype.h \
    services.h \
    editdialog.h \
    editcompdialog.h

FORMS    += mainwindow.ui \
    editdialog.ui \
    editcompdialog.ui

CONFIG += C++11

RESOURCES += \
    resources.qrc
