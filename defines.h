#ifndef DEFINES_H
#define DEFINES_H

#define QUBET_VERSION "0.1-a"

#define WIDTH               600
#define HEIGHT              400
#define MOVE_X              100
#define MOVE_Y              100

#define BUFSIZE             512

#define X_PLUS              0
#define X_MINUS             1
#define Y_PLUS              2
#define Y_MINUS             3
#define Z_PLUS              4
#define Z_MINUS             5

#define VOLUME_ON           400
#define VOLUME_OFF          401

/**
 * @brief Enum used for currentView
 */
enum { LOADING, MENU_VIEW, GAME_VIEW, LEVELEDITOR_VIEW };

/**
 * @brief Enum used for gameType
 */
enum { STORY_MODE, ARCADE_MODE, EDITOR_MODE };

#endif // DEFINES_H
