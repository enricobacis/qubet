#-------------------------------------------------
#                  Qubet Project
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = Qubet
TEMPLATE = app

unix:!macx {
    INCLUDEPATH += "/usr/include"
    LIBS += -L/usr/lib
    LIBS += -lglut
    LIBS += -lGL
    LIBS += -lGLU
    LIBS += -lIL
    LIBS += -lGLEW
}

win32 {
    INCLUDEPATH += "./include"
    LIBS += -L$$PWD/lib/GL
    LIBS += -L$$PWD/lib/IL
    LIBS += -lfreeglut
    LIBS += -lglu32
    LIBS += -lopengl32
    LIBS += -lDevIL
    LIBS += -lglew32
    LIBS += -lILU
    LIBS += -lILUT

    externals.path = $$OUT_PWD
    externals.files += $$PWD/externals/win/*
    INSTALLS += externals
}

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
    utilities.cpp \
    texture.cpp \
    shader.cpp

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
    texture.h \
    shader.h

RESOURCES += \
    resources.qrc
