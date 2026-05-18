QT       += core gui widgets sql

CONFIG += c++17

TEMPLATE = app
TARGET = calendar

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/database.cpp \
    src/eventdialog.cpp \
    src/categorydialog.cpp \
    src/colorcelldelegate.cpp \
    src/categorybadgedelegate.cpp

HEADERS += \
    src/mainwindow.h \
    src/database.h \
    src/eventdialog.h \
    src/categorydialog.h \
    src/colorcelldelegate.h \
    src/categorybadgedelegate.h

FORMS += \
    src/mainwindow.ui \
    src/eventdialog.ui \
    src/categorydialog.ui
