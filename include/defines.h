//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#ifndef DEFINES_H
#define DEFINES_H

#define QUBET_VERSION "1.0"

#define WIDTH                   600
#define HEIGHT                  400
#define MOVE_X                  100
#define MOVE_Y                  100

#define BUFSIZE                 512

#define X_PLUS                  0
#define X_MINUS                 1
#define Y_PLUS                  2
#define Y_MINUS                 3
#define Z_PLUS                  4
#define Z_MINUS                 5

#define VOLUME_ON               400
#define VOLUME_OFF              401

#define ASPHALT                 410
#define GRID                    411

#define MOUSE_MOVED_NONE        0
#define MOUSE_MOVED_DOWN        1
#define MOUSE_MOVED_FULL        2

#define LEVEL                   500
#define OBSTACLES               510

#define LEVEL_HEIGHT            0.2f
#define LEVEL_WIDTH_DEFAULT     9
#define LEVEL_LENGTH_DEFAULT    450
#define LEVEL_GRAVITY_DEFAULT   4

#define OBSTACLE_CUBE_SMALL     0
#define OBSTACLE_I              1
#define OBSTACLE_L              2
#define OBSTACLE_CUBE_BIG       3

/**
 * @brief Enum used for currentView
 */
enum { LOADING, MENU_VIEW, GAME_VIEW, LEVELEDITOR_VIEW, NO_VIEW };

/**
 * @brief Enum used for gameType
 */
enum { STORY_MODE, ARCADE_MODE, EDITOR_MODE };

enum { COLOR_DISABLED, COLOR_RED, COLOR_GREEN, COLOR_BLUE };

// Re-define for compatibility purposes
#ifndef GL_CLAMP_TO_EDGE
    #define GL_CLAMP_TO_EDGE      0x812F
#endif

#endif // DEFINES_H
