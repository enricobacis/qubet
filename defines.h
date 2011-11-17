#ifndef DEFINES_H
#define DEFINES_H

#define QUBET_VERSION "0.4-a"

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

#define MOUSE_MOVED_NONE        0
#define MOUSE_MOVED_DOWN        1
#define MOUSE_MOVED_FULL        2

#define LEVEL                   500
#define OBSTACLES               510

#define LEVEL_HEIGHT            0.2f
#define LEVEL_WIDTH_DEFAULT     9
#define LEVEL_LENGTH_DEFAULT    150
#define LEVEL_GRAVITY_DEFAULT   10

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
