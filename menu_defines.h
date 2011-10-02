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
       ROTATE_VOLUMECUBE, ROTATE_SKYBOX
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
