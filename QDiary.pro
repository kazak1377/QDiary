#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T17:41:44
#
#-------------------------------------------------

QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml webkitwidgets

TARGET = QDiary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlworker.cpp

HEADERS  += mainwindow.h \
    xmlworker.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    pref.qml
