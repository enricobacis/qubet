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

/**
 * @mainpage Qubet
 *
 * @section intro_section Introduction
 *
 * Qubet is a universitary project made by Enrico Bacis and Daniele Ciriello for the Graphical Informatics course at University of Bergamo.
 *
 * Qubet is a simple game developed using OpenGL and Qt where a Cube have to reach the end of different levels avoiding obstacles.
 *
 * It is distributed under GNU GPLv3 license.
 *
 * It uses Doxygen to manage the documentation.
 *
 * @section download_section Download
 *
 * You can download this project in either <a href="https://github.com/enricobacis/qubet/zipball/master">zip</a> or <a href="https://github.com/enricobacis/qubet/tarball/master">tar</a> formats.
 *
 * You can also clone the project with <a href="http://git-scm.com">Git</a> by running:
 * @code $ git clone git://github.com/enricobacis/qubet @endcode
 *
 * Get the source code on <a href="https://github.com/enricobacis/qubet">GitHub</a>.
 *
 * @section install_section Installation
 *
 * 1. Compile the code using Qt Creator.
 *
 * 2. Copy the resources folder where the binary has been compiled.
 *
 * 3. Enjoy.
 *
 * @section authors_section Authors
 *
 * Enrico Bacis
 *
 * Daniele Ciriello
 *
 * Musics by <a href="http://binaerpilot.no">Binarpilot</a>
 *
 * Sound FX by SoundBible and Super Mario
 *
 * @section contacts_section Contacts
 *
 * You can contact us on <a href="https://github.com/enricobacis/qubet">GitHub</a>.
 */


#ifndef QUBET_H
#define QUBET_H

#include "menu.h"
#include "game.h"
#include "audiomanager.h"
#include "leveleditor.h"

/**
 * @brief This class rapresents an instance of the QGLWidget Qubet.
 *        It is the game.
 *
 * @version 1.0
 * @author \#34
 */
class Qubet : public QGLWidget
{
    Q_OBJECT

public:
    // Object Management

    /**
     * @brief Create a Qubet object, which is a QGLWidget that contains the game.
     *
     * @post It also start the loading of game variables and initializes the objects
     * used in the game. To start a new instance of Qubet Game you have only to create
     * this object, it does all for you.
     *
     * @param parent is a callback variable to the parent of the widget.
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
    GLvoid initializeGL();

    /**
     * @brief Paint the OpenGL scene.
     *
     * This is the most important function since it draws on the screen the game.
     */
    GLvoid paintGL();

    /**
     * @brief Resize the OpenGL Window.
     *
     * @param _width is the new width of the window.
     * @param _height is the new height of the window.
     */
    GLvoid resizeGL(GLint _width, GLint _height);

    /**
     * @brief This function is invoked when the player clicks inside the game window.
     *
     * @param event is the QMouseEvent*.
     */
    GLvoid mousePressEvent(QMouseEvent *event);

    /**
     * @brief This function is invoked when the player releases the mouse click.
     *
     * @param event is the QMouseEvent*.
     */
    GLvoid mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief This function is invoked when the player moves the mouse inside the game window.
     *
     * @param event is the QMouseEvent*.
     */
    GLvoid mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief This function is invoked when the player scrolls the wheel of the mouse inside the game window.
     *
     * @param event is the QWheelEvent*.
     */
    GLvoid wheelEvent(QWheelEvent *event);

    /**
     * @brief This function is invoked when the player presses a key.
     *
     * @param event is the QKeyEvent*.
     */
    GLvoid keyPressEvent(QKeyEvent *event);


private:

    // Variables

    GLint currentView; /**< It is used to keep track of the current view (menu, game, leveleditor). */
    QString currentText; /**< It is the current string showed on the screen. */
    QMap<GLint,Skin*> skinsList; /**< It is the QMap that contains ids and skin images. */
    QMap<GLint,Level*> levelsList; /**< It is the QMap that contains ids and the names of level files. */
    QMap<GLint,GLuint> iconsList; /**< It is the QMap that contains ids of the icons' texture. */
    QMap<QString,Skybox*> skyboxesList; /**< It is the Qmap that contains the available skyboxes. */
    QTimer *drawTimer; /**< It is the QTimer to re-draw the scene. */
    Menu *menu; /**< It is the Menu pointer. */
    Game *game; /**< It is the Game pointer. */
    LevelEditor *levelEditor; /**< It is the LevelEditor pointer. */
    AudioManager *audioManager; /**< It is the AudioManager pointer. */
    Alphabet *alphabet; /**< It is the current Alphabet. */
    Skybox *skybox; /**< It is the current Skybox. */
    GLfloat skyboxAngle; /**< It is the Skybox rotation angle. */
    QGLShaderProgram *explosionShader; /**< It is the current explosion Shader. */
    Skin *asphaltSkin; /**< It is the asphalt Skin. */

    GLint width; /**< It is the current widget width. */
    GLint height; /**< It is the current widget height. */
    GLint mouseMovedMode; /**< It is the variable that states which mouse mode is enabled. See the documentation of setMouseMovementTracking(int mode) for the available modes.*/
    bool loadDone; /**< It is the variable that states if the load has already be done. */
    GLint currentNewLevelNumber; /**< It is the current level value. */


    // Initialization

    /**
     * @brief It is used after the first show of the qubet window to initialize Qubet.
     */
    GLvoid initQubet();

    // Signal <-> Slot Management

    /**
     * @brief This methos connects mouse and keyboard events to
     *        the receiver object to forward user's input to
     *        the current view.
     *
     * @pre You have to create the receiver and the receiver have
     *      to reimplement mouse and keyboard slots.
     *
     * @param receiver is the receiver const QObject*.
     */
    GLvoid connectInputEvents(const QObject *receiver);

    /**
     * @brief This method connects audio signals of the sender
     *        to their slots in AudioManager.
     *
     * @param sender is the sender const QObject*.
     */
    GLvoid connectAudio(const QObject *sender);

    /**
     * @brief This function is used to connect all the menu slots to their signals.
     */
    GLvoid connectMenu();

    /**
     * @brief This function is used to connect all the levelEditor slots to their signals.
     */
    GLvoid connectLevelEditor();

    /**
     * @brief This function is used to connect all the game slots to their signals.
     */
    GLvoid connectGame();


    // Picking Management

    /**
     * @brief This method returns a list of the names of the foreground item
     *        at mouse coordinates (mouseX, mouseY).
     *
     * @param mouseX is the mouse coordinate of x.
     * @param mouseY is the mouse coordinate of y.
     *
     * @returns a list of the names of the item on (mouseX, mouseY).
     */
    QList<GLuint> getPickedName(GLint mouseX, GLint mouseY);


    // General Purpose Management

    /**
     * @brief This function has to be invoked when the loading is finished.
     *
     * @post It will show the menu.
     */
    GLvoid loadingCompleted();

    /**
     * @brief This function has to be invoked when something in the loading
     *        process goes wrong.
     */
    GLvoid errorLoading();

    /**
     * @brief This function is used to states the paintGL function to show the Menu.
     *
     * @param showIntro is the variable that states if thw intro has to been showed. [default = true]
     */
    GLvoid showMenu(bool showIntro = true);

    /**
     * @brief This function is invoked when the player chooses an option from the
     *        Menu, so this is no more necessary and will be destroyed.
     *
     * @pre Keep in mind that you have to show something else to show on the screen
     * using the currentView variable before to delete the current Menu instance.
     */
    GLvoid closeMenu();

    /**
     * @brief This function is used to draw the scene on the QGLWidget.
     *        It is used by PaintGL that calls this and then do
     *        the swap of the buffers. You can use this function either to
     *        draw the scene in the background buffer or to draw the scene
     *        to use the picking and then not to swap buffers.
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    GLvoid drawScene(GLboolean simplifyForPicking = false);


    // Loading Functions

    /**
     * @brief Load skins, levels and obstacles in Qubet.
     *
     * @returns true if the load is successful, else false.
     */
    GLboolean load();

    /**
     * @brief Load the skins from the resource file.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadSkins();

    /**
     * @brief Load the levels from the resource file.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadLevels();

    /**
     * @brief Load the alphabet.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadAlphabet();

    /**
     * @brief Load the icons.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadIcons();

    /**
     * @brief Load the skyboxes.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadSkyboxes();

    /**
     * @brief Load the Shader.
     *
     * @returns true if load is successful, else false.
     */
    GLboolean loadShader();


private slots:
    // Link to Objects

    /**
     * @brief This is a duplicated function to call paintGL, but this can
     *        be used as a slot.
     */
    void draw();

    /**
     * @brief This function is a slot linked to the Menu and invoked when
     *        the player chooses to play the Story Mode.
     *
     * @param skinId It is the id of the selected skin.
     */
    void playStory(GLint skinId);

    /**
     * @brief This function is a slot linked to the Menu and invoked when
     *        the player chooses to play the Arcade Mode.
     *
     * @param skinId It is the id of the selected skin.
     * @param levelId It is the id of the selected level.
     */
    void playArcade(GLint skinId, GLint levelId);

    /**
     * @brief This function is a slot linked to the Game and invoked when
     *        the player chooses to close the current Game instance.
     */
    void gameClosed();

    /**
     * @brief This function is a slot linked to the Menu and invoked when
     *        the player chooses to enter the Level Editor.
     *
     * @param _levelId is the levelId you want to edit.
     */
    void showLevelEditor(GLint _levelId);

    /**
     * @brief Slot invoked to add a level to the levelList.
     *
     * @param _level is the Level to add.
     */
    void addLevelToLevelsList(Level *_level);

    /**
     * @brief This function is a slot linked to the LevelEditor and invoked when
     *        the player chooses to close the current LevelEditor instance.
     */
    void levelEditorClosed();

    /**
     * @brief This slot is to set the Mouse Move Tracking sensibility.
     *        The modes are:
     *          0 - no signal emitted.
     *          1 - the signal mouseMoved is emitted only when the mouse is moved
     *              and one of the mouse buttons are clicked.
     *          2 - the signal mouseMoved is emitted always when the mouse is
     *              moved.
     *
     * @param mode It is the selected mode.
     */
    void setMouseMovementTracking(int mode);

    /**
     * @brief This slot is invoked to set the Skybox.
     *
     * @param skyboxName is the name of the Skybox to apply.
     */
    void setSkybox(QString skyboxName);


signals:

    /**
     * @brief Signal emitted when the user clicks on a item.
     *
     * @param event is the QMouseEvent.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void itemClicked(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Signal emitted when the user releases the mouse button.
     *
     * @param event is the QMouseEvent*.
     */
    void mouseReleased(QMouseEvent *event);

    /**
     * @brief Signal emitted when the user moves the mouse.
     *
     * @param event is the QMouseEvent*.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void mouseMoved(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Signal emitted when the user scrolls the wheel of the mouse.
     *
     * @param event is the QWheelEvent*.
     */
    void wheelScrolled(QWheelEvent *event);

    /**
     * @brief Signal emitted when the user presses a key on the keyboard.
     *
     * @param event is the QKeyEvent*.
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief Signal emitted to enable or disable the audio.
     *
     * @param enabled is the variable that states if the audio is to enable or not.
     */
    void enableAudio(bool enabled);

    /**
     * @brief Signal emitted to play the ambient music.
     *
     * @param filename is the filename to play.
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief Signal emitted to stop the current ambient music.
     */
    void stopAmbientMusic();

    /**
     * @brief Signal emitted to play an effect.
     *
     * @param effectName is the name of the effect to play.
     */
    void playEffect(QString effectName);

};

#endif // QUBET_H
