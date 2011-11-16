###################################################
#                  Qubet Project                  #
#                       #34                       #
###################################################

QT += core gui
QT += opengl
QT += xml
QT += phonon

TARGET = Qubet
TEMPLATE = app

DEFINES += USE_DISPLAY_LISTS_FOR_LETTERS

CONFIG(debug, debug|release) { DEFINES += _DEBUG }

SOURCES += \
    main.cpp\
    game.cpp \
    cube.cpp \
    positioncontroller.cpp \
    obstacle.cpp \
    level.cpp \
    audiomanager.cpp \
    menu.cpp \
    leveleditor.cpp \
    qubet.cpp \
    window.cpp \
    utilities.cpp \
    skin.cpp \
    alphabet.cpp \
    letter.cpp \
    cubestring.cpp \
    actionlist.cpp \
    cubestringlist.cpp \
    skybox.cpp

HEADERS  += \
    vector3f.h \
    game.h \
    cube.h \
    positioncontroller.h \
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
    menu_defines.h \
    skin.h \
    alphabet.h \
    letter.h \
    cubestring.h \
    actionlist.h \
    cubestringlist.h \
    effects_defines.h \
    skybox.h \
    cube_defines.h

OTHER_FILES += \
    resources/skins/skins.xml \
    resources/sound/music/menu.wav \
    resources/levels/levels.xml \
    resources/icons/icons.xml
