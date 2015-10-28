#-------------------------------------------------
#
# Project created by QtCreator 2015-08-07T09:53:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLBase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    baseglwidget.cpp \
    draw.cpp \
    object3d.cpp

HEADERS  += mainwindow.h \
    baseglwidget.h \
    draw.h \
    object3d.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc \
    obj.qrc
