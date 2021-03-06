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
    settingsdialog.cpp \
    network.cpp \
    neuron.cpp \
    converterinputdata.cpp \
    controllermaps.cpp \
    viewmaps.cpp \
    instructiondialog.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    network.h \
    neuron.h \
    converterinputdata.h \
    controllermaps.h \
    viewmaps.h \
    instructiondialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    instructiondialog.ui

RESOURCES += \
    my_res.qrc
