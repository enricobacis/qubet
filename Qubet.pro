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
    alpfhabet.cpp \
    letter.cpp

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
    alpfhabet.h \
    letter.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    resources/skins/skins.xml \
