#ifndef LEVELEDITOR_DEFINES_H
#define LEVELEDITOR_DEFINES_H

// Names used in the LevelEditor View
// This name will be in the format 3xx


#define BUTTON_VOLUME               300
#define LENGHT_DISPLAY              301
#define WIDTH_DISPLAY               302
#define BUTTON_ENLARGE              303
#define BUTTON_REDUCE               304
#define BUTTON_LENGHTEN             305
#define BUTTON_SHORTEN              306
#define LENGHT_LABEL                307
#define WIDTH_LABEL                 308
#define CREATE_BUTTON               309

#define MIN_LEVEL_LENGHT            10
#define MAX_LEVEL_LENGHT            300

#define MIN_LEVEL_WIDTH             3
#define MAX_LEVEL_WIDTH             30

/**
 * @brief Enum used for Editor's actions
 */
enum { DO_NOTHING,
       INITIAL_ACTION,
       ROTATE_VOLUMECUBE
     };

/**
 * @brief Enum used for Editor's currentView
 */
enum { SET_PARAM_VIEW, OTHER_VIEW};


#endif // LEVELEDITOR_DEFINES_H
