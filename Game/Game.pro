QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QT += multimedia

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemy.cpp \
    level.cpp \
    main.cpp \
    mainwindow.cpp \
    midmenu.cpp \
    rocket.cpp \
    gameitem.cpp \
    obstacles.cpp \
    startmenu.cpp


HEADERS += \
    enemy.h \
    level.h \
    mainwindow.h \
    midmenu.h \
    rocket.h \
    gameitem.h \
    obstacles.h \
    startmenu.h

FORMS += \
    mainwindow.ui \
    midmenu.ui \
    startmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D/lib/ -lbox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D/lib/ -lbox2d
else:unix: LIBS += -L$$PWD/Box2D/lib/ -lbox2

INCLUDEPATH += $$PWD/Box2D
DEPENDPATH += $$PWD/Box2D

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D/lib/ -lbox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D/lib/ -lbox2d
else:unix: LIBS += -L$$PWD/Box2D/lib/ -lbox2

INCLUDEPATH += $$PWD/Box2D
DEPENDPATH += $$PWD/Box2D

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2d
else:unix: LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/lib/ -lBox2

INCLUDEPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug
DEPENDPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MinGW_64_bit-Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop-Debug/lib/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop-Debug/lib/ -lBox2d
else:unix: LIBS += -L$$PWD/build-Box2D-Desktop-Debug/lib/ -lBox2

INCLUDEPATH += $$PWD/build-Box2D-Desktop-Debug
DEPENDPATH += $$PWD/build-Box2D-Desktop-Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MSVC2019_64bit-Debug/lib/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MSVC2019_64bit-Debug/lib/ -lBox2d
else:unix: LIBS += -L$$PWD/build-Box2D-Desktop_Qt_6_6_0_MSVC2019_64bit-Debug/lib/ -lBox2

INCLUDEPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MSVC2019_64bit-Debug
DEPENDPATH += $$PWD/build-Box2D-Desktop_Qt_6_6_0_MSVC2019_64bit-Debug

RESOURCES += \
    resources.qrc
