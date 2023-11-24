QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemy.cpp \
    gameitem.cpp \
    level.cpp \
    main.cpp \
    mainwindow.cpp \
<<<<<<< HEAD
    rocket.cpp  \
    gameitem.cpp \
    obstacles.cpp
=======
    obstacles.cpp \
    rocket.cpp
>>>>>>> 596ff39a9c0284bcd05885049663f82d5fcb7b51

HEADERS += \
    enemy.h \
    gameitem.h \
    level.h \
    mainwindow.h \
<<<<<<< HEAD
    rocket.h    \
    gameitem.h  \
    obstacles.h
=======
    obstacles.h \
    rocket.h
>>>>>>> 596ff39a9c0284bcd05885049663f82d5fcb7b51

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2d
else:unix: LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2

INCLUDEPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug
DEPENDPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug
