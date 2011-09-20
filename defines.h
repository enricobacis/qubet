#ifndef DEFINES_H
#define DEFINES_H

#define QUBET_VERSION "0.1-a"

#define STEPS 3

#define WIDTH 600
#define HEIGHT 400
#define MOVE_X 100
#define MOVE_Y 100

#define BUFSIZE 512

/**
 * @brief Enum used for currentView
 */
enum { LOADING, MENU_VIEW, GAME_VIEW, LEVELEDITOR_VIEW };

/**
 * @brief Enum used for gameType
 */
enum { STORY_MODE, ARCADE_MODE };

#endif // DEFINES_H
