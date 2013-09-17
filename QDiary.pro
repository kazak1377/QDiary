#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T17:41:44
#
#-------------------------------------------------

QT       += core gui quick sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml webkitwidgets

TARGET = QDiary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbworker.cpp \
    postwindow.cpp

HEADERS  += mainwindow.h \
    dbworker.h \
    postwindow.h

FORMS    += mainwindow.ui \
    postwindow.ui

OTHER_FILES +=
