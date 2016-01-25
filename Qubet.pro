###############################################################################
#                                                                             #
#                                 Qubet Project                               #
#                                      #34                                    #
#                                                                             #
#    Qubet  -  Copyright (C) 2011 - 2016                                      #
#                                                                             #
#    Enrico Bacis                                                             #
#    Daniele Ciriello                                                         #
#                                                                             #
#    Musics by Binarpilot <binaerpilot.no>                                    #
#    Sound FX by SoundBible and Super Mario                                   #
#                                                                             #
#    Qubet is free software: you can redistribute it and/or modify            #
#    it under the terms of the GNU General Public License as published by     #
#    the Free Software Foundation, either version 3 of the License, or        #
#    (at your option) any later version.                                      #
#                                                                             #
#    This program is distributed in the hope that it will be useful,          #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of           #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
#    GNU General Public License for more details.                             #
#                                                                             #
#    You should have received a copy of the GNU General Public License        #
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.    #
#                                                                             #
###############################################################################


QT += core gui
QT += opengl
QT += xml
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:!macx {
    LIBS += -lGLU
} macx {
    LDFLAGS += -framework OpenGL
}

INCLUDEPATH += $$PWD/include
DESTDIR      = bin
OBJECTS_DIR  = objs
MOC_DIR      = objs

TARGET = Qubet
TEMPLATE = app

data.path = /usr/share/qubet
data.files = Qubet resources

launcher.path = /usr/share/applications
launcher.files = qubet.desktop

INSTALLS += data launcher

DEFINES += USE_DISPLAY_LISTS_FOR_LETTERS

CONFIG(debug, debug|release) { DEFINES += _DEBUG }

SOURCES += \
    src/main.cpp\
    src/game.cpp \
    src/cube.cpp \
    src/positioncontroller.cpp \
    src/obstacle.cpp \
    src/level.cpp \
    src/audiomanager.cpp \
    src/menu.cpp \
    src/leveleditor.cpp \
    src/qubet.cpp \
    src/window.cpp \
    src/utilities.cpp \
    src/skin.cpp \
    src/alphabet.cpp \
    src/letter.cpp \
    src/cubestring.cpp \
    src/actionlist.cpp \
    src/cubestringlist.cpp \
    src/skybox.cpp

HEADERS  += \
    include/vector3f.h \
    include/game.h \
    include/cube.h \
    include/positioncontroller.h \
    include/obstacle.h \
    include/level.h \
    include/audiomanager.h \
    include/menu.h \
    include/leveleditor.h \
    include/defines.h \
    include/qubet.h \
    include/window.h \
    include/utilities.h \
    include/game_defines.h \
    include/leveleditor_defines.h \
    include/menu_defines.h \
    include/skin.h \
    include/alphabet.h \
    include/letter.h \
    include/cubestring.h \
    include/actionlist.h \
    include/cubestringlist.h \
    include/effects_defines.h \
    include/skybox.h \
    include/cube_defines.h

OTHER_FILES += \
    resources/skins/skins.xml \
    resources/sound/music/menu.wav \
    resources/levels/levels.xml \
    resources/icons/icons.xml
