#ifndef QUBET_H
#define QUBET_H

#include <QDomElement>

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
     * @brief This function is called when the player clicks inside the game window.
     *
     * @param event is the QMouseEvent*.
     */
    GLvoid mousePressEvent(QMouseEvent *event);

    /**
     * @brief This function is called when the player releases the mouse click.
     *
     * @param event is the QMouseEvent*.
     */
    GLvoid mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief This function is called when the player moves the mouse inside the game window.
     *
     * @param eventis the QMouseEvent*.
     */
    GLvoid mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief This function is called when the player presses a key.
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
    QMap<GLint,Vector3f*> obstacleModelsList; /**< It is the QMap that contains ids and the dimensions of Obstacles. */
    QMap<GLint,GLuint> iconsList; /**< It is the QMap that contains ids of the icons' texture. */
    QTimer *drawTimer; /**< It is the QTimer to re-draw the scene. */
    Menu *menu; /**< It is the Menu pointer. */
    Game *game; /**< It is the Game pointer. */
    LevelEditor *levelEditor; /**< It is the LevelEditor pointer. */
    AudioManager *audioManager; /**< It is the AudioManager pointer. */
    Alphabet *alphabet; /**< It is the current Alphabet */

    GLint width; /**< It is the current widget width. */
    GLint height; /**< It is the current widget height. */
    GLint mouseMovedMode; /**< It is the variable that tells which mouse mode is enabled. See the documentation of setMouseMovementTracking(int mode) for the available modes.*/


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
     * @brief This function is used to connect all the game slots to their signals.
     */
    GLvoid connectGame();

    /**
     * @brief This function is used to connect all the menu slots to their signals.
     */
    GLvoid connectMenu();


    // Picking Management

    /**
     * @brief This method returns a list of the names of the foreground item
     *        at mouse coordinates (mouseX, mouseY).
     *
     * @param mouseX is the mouse coordinate of x.
     * @param mouseY is the mouse coordinate of y.
     *
     * @return QList<GLuint> is a list of the names of the item on (mouseX, mouseY).
     */
    QList<GLuint> getPickedName(GLint mouseX, GLint mouseY);


    // General Purpose Management

    /**
     * @brief This function has to be called when the loading is finished.
     *
     * @post It will show the menu.
     */
    GLvoid loadingCompleted();

    /**
     * @brief This function has to be called when something in the loading
     *        process goes wrong.
     */
    GLvoid errorLoading();

    /**
     * @brief This function is used to tell the paintGL function to show the Menu.
     */
    GLvoid showMenu();

    /**
     * @brief This function is called when the player chooses an option from the
     *        Menu, so this is no more necessary and will be destroyed.
     *
     * @pre Keep in mind that you have to show something else to show on the screen
     * using the currentView variable before to delete the current Menu instance.
     */
    GLvoid menuClosed();

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
     * @return true if the load is successful, else false.
     */
    GLboolean load();

    /**
     * @brief Load the skins from the resource file.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadSkins();

    /**
     * @brief Load custom skins from folder.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadCustomSkins();

    /**
     * @brief Load the obstacleModels from the resource file.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadObstacleModels();

    /**
     * @brief Load custom obstacleModels from folder.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadCustomObstacleModels();

    /**
     * @brief Load the levels from the resource file.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadLevels();

    /**
     * @brief Load custom levels from folder.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadCustomLevels();

    /**
     * @brief Load the alphabet.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadAlphabet();

    /**
     * @brief Load the icons.
     *
     * @return true if load is successful, false elsewhere.
     */
    GLboolean loadIcons();


private slots:
    // Link to Objects

    /**
     * @brief This is a duplicated function to call paintGL, but this can
     *        be used as a slot.
     */
    void draw();

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
     * @param levelId It is the id of the selected level.
     */
    void playArcade(GLint skinId, GLint levelId);

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


signals:

    /**
     * @brief Signal emitted when the user clicks on a item.
     *
     * @param listNames is the QList<GLuint> of item's names.
     */
    void itemClicked(QList<GLuint> listNames);

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
     * @brief Signal emitted to play an effect.
     *
     * @param effectId is the id of the effect to play.
     */
    void playEffect(int effectId);

};

#endif // QUBET_H
