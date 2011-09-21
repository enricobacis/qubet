#-------------------------------------------------
#                  Qubet Project
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = Qubet
TEMPLATE = app

SOURCES += main.cpp\
    game.cpp \
    cube.cpp \
    positioncontroller.cpp \
    loader.cpp \
    obstacle.cpp \
    level.cpp \
    audiomanager.cpp \
    menu.cpp \
    leveleditor.cpp \
    qubet.cpp \
    window.cpp \
    utilities.cpp

HEADERS  += \
    vector3f.h \
    game.h \
    cube.h \
    positioncontroller.h \
    loader.h \
    obstacle.h \
    level.h \
    audiomanager.h \
    menu.h \
    leveleditor.h \
    defines.h \
    qubet.h \
    window.h \
    utilities.h \
    game_defines.h \
    leveleditor_defines.h \
    menu_defines.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    Doxyfile
