#-------------------------------------------------
#
# Project created by QtCreator 2014-08-30T13:10:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogWidget
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        logwidgetmainwindow.cpp \
    logmodelextended.cpp \
    logmodeldata.cpp \
    logmodeldelegate.cpp \
    filelogwidget.cpp

HEADERS  += logwidgetmainwindow.h \
    logmodelextended.h \
    logmodeldata.h \
    logmodeldelegate.h \
    filelogwidget.h

FORMS    += logwidgetmainwindow.ui \
    filelogwidget.ui
