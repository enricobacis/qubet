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


#ifndef MENU_DEFINES_H
#define MENU_DEFINES_H

// Names used in the Menu View
// This name will be in the format 1xx

#define BUTTON_VOLUME               100
#define BUTTON_PLAY_STORY           101
#define BUTTON_PLAY_ARCADE          102
#define BUTTON_LEVEL_EDITOR         103
#define BUTTON_BACK                 104
#define BUTTON_NEXT                 105
#define SKIN_NAME                   106
#define SKIN_CUBE                   107
#define BUTTON_PREVIOUS_SKIN        108
#define BUTTON_NEXT_SKIN            109
#define BUTTON_NEXT_LEVEL           110
#define BUTTON_PREVIOUS_LEVEL       111
#define LEVEL_NAME                  112

/**
 * @brief Enum used for Menu's actions
 */
enum { // Primary Actions
       DO_NOTHING,
       INITIAL_MOTION,
       CUBE_STUDIO_DISTRIBUTION, TEAM_34_PROJECT, QUBET,
       GO_TO_MAIN_VIEW, GO_TO_SKINS_VIEW, GO_TO_LEVELS_VIEW,
       ROTATE_SKINCUBE,
       PREVIOUS_SKIN, NEXT_SKIN,
       EXIT_FROM_LEVELS, EXIT_FROM_SKINS,

       // Secondary Actions
       ROTATE_VOLUMECUBE
     };

/**
 * @brief Enum used for Menu's currentView
 */
enum { INTRODUCTION, MAIN_VIEW, SKINS_VIEW, LEVELS_VIEW };

/**
 * @brief Enum used for Menu's currentSection
 */
enum { INTRO_SECTION, MENU_SECTION };


#endif // MENU_DEFINES_H
