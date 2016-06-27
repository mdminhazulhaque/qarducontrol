QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport
TARGET = qarducontrol
TEMPLATE = app
SOURCES += main.cpp\
        window.cpp\
        aboutdialog.cpp
HEADERS  += window.h\
        aboutdialog.h
FORMS    += window.ui\
        aboutdialog.ui
