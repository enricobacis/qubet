#ifndef QUBET_H
#define QUBET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QMap>

#include <GL/gl.h>

#include "vector3f.h"
#include "loader.h"
#include "menu.h"
#include "game.h"
#include "cube.h"
#include "audiomanager.h"
#include "leveleditor.h"
#include "defines.h"


/**
 * @brief
 *
 */
class Qubet : public QGLWidget
{
    Q_OBJECT

public:
    // Object Management

    /**
     * @brief Create a Qubet object, which is a QGLWidget that contains the game.
     *
     * It also start the loading of game variables and initializes the objects used
     * in the game. To start a new instance of Qubet Game you have only to create
     * this object, it does all for you.
     *
     * @param parent is a callback variable to the parent of the widget
     */
    explicit Qubet(QWidget *parent = 0);

    /**
     * @brief Destroy a Qubet object.
     *
     * It will stop rendering, stop the game, safely stop threads and waits for
     * them, so when this function returns you have safely deletes the Qubet instance.
     * This is a syncronous function in order to return only when all operations
     * for the Qubet Widget closure has been terminated.
     */
    ~Qubet();


protected:
    // OpenGL Management

    /**
     * @brief Initialize the Qt OpenGL
     *
     * It is used to manage the OpenGL instance.
     */
    void initializeGL();

    /**
     * @brief Paint the OpenGL scene.
     *
     * This is the most important function since it draws on the screen the game.
     */
    void paintGL();

    /**
     * @brief Resize the OpenGL Window.
     *
     * @param width is the new width of the window.
     * @param height is the new height of the window.
     */
    void resizeGL(int width, int height);

    /**
     * @brief This function is called when the player clicks inside the game window.
     *
     * @param event is the Qt mouse press event.
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief This function is called when the player move the mouse inside the game window.
     *
     * @param eventis the Qt mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief This function is called when the player press a key and the
     *        game window has the focus.
     *
     * @param event is the Qt key press event.
     */
    void keyPressEvent(QKeyEvent *event);


private:
    // Variables

    GLint loadingSteps; /**< It is used to keep track of he current loading step */
    GLint currentView; /**< It is used to keep track of the current view (menu, game, leveleditor) */
    QMap<GLint,QImage*> skinsList; /**< It is the QMap that contains ids and skin images */
    QMap<GLint,QString> levelsList; /**< It is the QMap that contains ids and the names of level files */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< It is the QMap that contains ids and the dimensions of Obstacles */
    QTimer *drawTimer; /**< It is the QTimer to re-draw the scene */
    Loader *loader; /**< It is the Loader pointer */
    Menu *menu; /**< It is the Menu pointer */
    Game *game; /**< It is the Game pointer */
    LevelEditor *levelEditor; /**< It is the LevelEditor pointer */
    AudioManager *audioManager; /**< It is the AudioManager pointer */


    // General Purpose Management

    /**
     * @brief This function is called when a loading step is completed.
     *
     * When all loading steps will be completed this function calls the
     * function loadingCompleted().
     */
    void loadingStepCompleted();

    /**
     * @brief This function is called automatically from loadingStepCompleted()
     *        when all loading steps has been completed.
     *
     * It will show the menu.
     */
    void loadingCompleted();

    /**
     * @brief This function (only for convenience) is used to link all the
     *        game slots to their signals.
     */
    void connectGame();

    /**
     * @brief This function is used to tell the paintGL function to show the Menu.
     */
    void showMenu();

    /**
     * @brief This function is called when the player chooses an option from the
     *        Menu, so this is no more necessary and will be destroyed.
     *
     * Keep in mind that you have to show something else to show on the screen
     * using the currentView variable before to delete the current Menu instance.
     */
    void menuClosed();

private slots:
    // Link to Objects

    /**
     * @brief This is a duplicated function to call paintGL, but this can
     *        be used as a slot.
     */
    void draw();

    /**
     * @brief This function is a slot linked to the Loader and called when
     *        the skins has been loaded.
     */
    void skinsLoaded();

    /**
     * @brief This function is a slot linked to the Loader and called when
     *        the levels has been loaded.
     */
    void levelsLoaded();

    /**
     * @brief This function is a slot linked to the Loader and called when
     *        the obstacleModels has been loaded.
     */
    void obstacleModelsLoaded();

    /**
     * @brief This function is a slot linked to the Loader and called when
     *        there is an error in loading files from Loader.
     */
    void errorLoading();

    /**
     * @brief This function is a slot linked to the Menu and called when
     *        the player chooses to play the Story Mode.
     *
     * @param skinId It is the id of the selected skin.
     */
    void playStory(GLint skinId);

    /**
     * @brief This function is a slot linked to the Menu and called when
     *        the player chooses to play the Arcade Mode.
     *
     * @param skinId It is the id of the selected skin.
     * @param levelFilename  It is the filename of the selected level.
     */
    void playArcade(GLint skinId, QString levelFilename);

    /**
     * @brief This function is a slot linked to the Game and called when
     *        the player chooses to close the current Game instance.
     */
    void gameClosed();

    /**
     * @brief This function is a slot linked to the Menu and called when
     *        the player chooses to enter the Level Editor.
     */
    void showLevelEditor();

    /**
     * @brief This function is a slot linked to the LevelEditor and called when
     *        the player chooses to close the current LevelEditor instance.
     */
    void levelEditorClosed();

};

#endif // QUBET_H
