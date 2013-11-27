#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T00:15:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


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
    qgameobject.cpp

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
    qgameobject.h \
    types.h

FORMS    += mainwindow.ui \
    sellpopup.ui

RESOURCES += \
    resources.qrc
