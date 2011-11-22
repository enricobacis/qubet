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


#ifndef LEVELEDITOR_DEFINES_H
#define LEVELEDITOR_DEFINES_H

// Names used in the LevelEditor View
// This name will be in the format 3xx

#define BUTTON_VOLUME               300
#define LENGTH_LABEL                301
#define WIDTH_LABEL                 302
#define BUTTON_ENLARGE              303
#define BUTTON_REDUCE               304
#define BUTTON_LENGTHEN             305
#define BUTTON_SHORTEN              306
#define LENGTH_STRING               307
#define WIDTH_STRING                308
#define LABEL_SET_LEVEL_NAME        309
#define BUTTON_BACK                 310
#define BUTTON_NEXT                 311
#define FORM_SET_LEVEL_NAME         312
#define GRAVITY_LABEL               313
#define GRAVITY_STRING              314
#define BUTTON_GRAVITY_PLUS         315
#define BUTTON_GRAVITY_MINUS        316
#define BUTTON_SAVE                 317
#define BUTTON_CANCEL               318
#define BUTTON_CLEAR                319
#define BUTTON_EXIT                 320

#define TOOLBAR                     325
#define OBSTACLE_0                  330
#define OBSTACLE_1                  331
#define OBSTACLE_2                  332
#define OBSTACLE_3                  333

#define MIN_LEVEL_LENGTH            150
#define MAX_LEVEL_LENGTH            900

#define MIN_LEVEL_WIDTH             3
#define MAX_LEVEL_WIDTH             15

#define MIN_GRAVITY                 4
#define MAX_GRAVITY                 20

#define TYPE_OBSTACLE               1

/**
 * @brief Enum used for Editor's actions
 */
enum { // Primary Actions
       DO_NOTHING,
       INITIAL_MOVEMENT,
       GO_TO_SET_NAME_VIEW,
       GO_TO_SET_PARAM_VIEW,
       GO_TO_SET_GRAVITY_VIEW,
       GO_TO_EDITING_LEVEL_VIEW,
       EXIT_TO_MENU,

      // Secondary Actions
      ROTATE_VOLUMECUBE
     };

/**
 * @brief Enum used for Editor's currentView
 */
enum { SET_NAME_VIEW, SET_PARAM_VIEW, SET_GRAVITY_VIEW, EDITING_LEVEL_VIEW};

#endif // LEVELEDITOR_DEFINES_H
