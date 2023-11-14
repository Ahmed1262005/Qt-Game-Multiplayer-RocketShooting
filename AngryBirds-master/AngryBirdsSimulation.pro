#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T17:48:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AngryBirdsSimulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    terence.cpp \
    simulator.cpp \
    scenemanager.cpp \
    piggs.cpp \
    physicitem.cpp \
    myquerycallback.cpp \
    mycontactlistener.cpp \
    material.cpp \
    mainwindow.cpp \
    main.cpp \
    logo.cpp \
    fixtureitem.cpp \
    chunck.cpp \
    bomb.cpp \
    blue.cpp \
    blocks.cpp \
    redbird.cpp

HEADERS  += mainwindow.h \
    world.h \
    terence.h \
    simulator.h \
    scenemanager.h \
    redbird.h \
    piggs.h \
    physicitem.h \
    myquerycallback.h \
    mycontactlistener.h \
    material.h \
    mainwindow.h \
    logo.h \
    fixtureitem.h \
    defs.h \
    chunck.h \
    bomb.h \
    blue.h \
    blocks.h

FORMS    += mainwindow.ui \
    mainwindow.ui

RESOURCES += \
    rc.qrc
LIBS += Box2D.lib
