#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T00:15:50
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app
#QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += "./"

SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    board.cpp \
    dice.cpp \
    localgame.cpp \
    block.cpp \
    eventblock.cpp \
    subjectblock.cpp \
    cornerblock.cpp \
    playerqueue.cpp \
    firefridayblock.cpp \
    sellpopup.cpp \
    qgameitem.cpp \
    scene/ingamescene.cpp \
    scene/logoscene.cpp \
    scene/creditscene.cpp \
    scene/mainscene.cpp \
    scene/readyscene.cpp \
    pausepanel.cpp

HEADERS  += mainwindow.h \
    player.h \
    board.h \
    dice.h \
    localgame.h \
    block.h \
    eventblock.h \
    subjectblock.h \
    cornerblock.h \
    playerqueue.h \
    firefridayblock.h \
    sellpopup.h \
    types.h \
    qgameitem.h \
    scene/ingamescene.h \
    scene/logoscene.h \
    scene/creditscene.h \
    scene/mainscene.h \
    scene/readyscene.h \
    pausepanel.h

FORMS    += mainwindow.ui \
    sellpopup.ui

RESOURCES += \
    resources.qrc
