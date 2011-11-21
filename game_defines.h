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
