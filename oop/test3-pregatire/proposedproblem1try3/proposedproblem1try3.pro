QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proposedproblem1try3
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           song.cpp \
           songcontroller.cpp

HEADERS += mainwindow.h \
           song.h \
           songcontroller.h
