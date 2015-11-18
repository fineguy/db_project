#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T23:49:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = database
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    session.cpp \
    mainwindow.cpp

HEADERS  += loginwindow.hpp \
    session.hpp \
    mainwindow.hpp \
    consts.hpp

FORMS    += loginwindow.ui \
    mainwindow.ui
