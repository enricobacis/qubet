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


#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

// Names used in the Game View
// This name will be in the format 2xx

#define BUTTON_VOLUME               200
#define STATE_LABEL                 201
#define QUIT_LABEL                  202

enum { // Primary Actions
       DO_NOTHING,
       COUNTDOWN,
       MOVE_TO_LEVEL,
       MOVE_TO_NEXT_LEVEL,
       GO_TO_RESULTS_SCREEN,
       EXIT_TO_MENU,

      // Secondary Actions
      ROTATE_VOLUMECUBE
     };

#endif // GAME_DEFINES_H
