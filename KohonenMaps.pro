#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T19:28:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KohonenMaps
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    instructiondialog.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    instructiondialog.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    instructiondialog.ui \
    settingsdialog.ui

RESOURCES += \
    my_res.qrc