#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T10:47:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    scanner.cpp \
    node.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    parser.h \
    scanner.h \
    node.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui
