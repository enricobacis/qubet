#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

// Names used in the Game View
// This name will be in the format 2xx

#define BUTTON_VOLUME               200
#define STATE_LABEL                 201
#define QUIT_LABEL                  202

enum { // Primary Actions
       DO_NOTHING,
       MOVE_TO_LEVEL,
       EXIT_FROM_LEVEL,
       COUNTDOWN,

      // Secondary Actions
      ROTATE_VOLUMECUBE
     };

#endif // GAME_DEFINES_H
