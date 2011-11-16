#ifndef GAME_H
#define GAME_H

#include "positioncontroller.h"
#include "actionlist.h"

/**
 * @brief It is the Game Class.
 *
 * @version 1.0
 * @author \#34
 */
class Game : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Cunstructor fot the Story Mode.
     *
     * @param _skin
     * @param _levelsList
     * @param _parent
     * @param _audioEnabled
     */
    explicit Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent = 0, bool _audioEnabled = true);

    /**
     * @brief Cunstructor fot the Arcade Mode.
     *
     * @param _skin
     * @param _level
     * @param _parent
     * @param _audioEnabled
     */
    explicit Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, Level *_level, QObject *_parent = 0, bool _audioEnabled = true);

    /**
     * @brief Destroyer of Game Object.
     *
     */
    ~Game();

    /**
     * @brief Function to get invoked when the game start.
     *
     */
    void startGame();

    /**
     * @brief Method to draw the game.
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    void draw(GLboolean simplifyForPicking = false);


private:
    QObject *parent; /**< It is the parent of a game Object. */
    QMap<GLint,GLuint> iconsList;  /**< It is the iconsList provided by Qubet object. */
    Alphabet *alphabet; /**< It is the alphabet provided by Qubet. */
    Skin *skin; /**< it is the cube skin pointer. */
    Level *level; /**< It is the current level pointer. */
    QMap<GLint,Level*> levelsList; /**< It is the story levelList. */
    bool audioEnabled; /**< It is the audioEnabled boolean value. */
    Cube *cube; /**< It is the cube pointer. */
    PositionController *positionController; /**< It is the positionController pointer. */
    GLint state; /**< It is the current state value. */
    GLint gameType; /**< It is the game type value. */
    GLint currentLevel; /**< It is the current level value. */
    GLint deaths; /**< It is the death counter value. */
    ActionList *currentActions; /**< It is the list of the current menu steps. */
    GLfloat angleRotVolumeCube;  /**< It is the current rotation angle of the volume icon. */
    Skin *volumeSkin; /**< It is the skin of the volume button */
    Vector3f *cameraOffset; /**< It is the camera offset for the editor. */
    Vector3f *levelOffset; /**< It is the offset of the Level */

    /**
     * @brief initialize the game.
     */
    void initGame();

    /**
     * @brief start playing game.
     */
    void playLevel();

    /**
     * @brief go to the next level.
     */
    void nextLevel();

    /**
     * @brief go to pause mode.
     *
     */
    void pauseGame();

    /**
     * @brief continue the game from pause mode.
     *
     */
    void continueGame();

    /**
     * @brief quit the game and returns to menu.
     *
     */
    void quitGame();


private slots:

    /**
     * @brief Slot invoked when the user clicks on a item.
     *
     * @param event is the QMouseEvent.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void itemClicked(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Slot invoked when the user releases the mouse button.
     *
     * @param event is the QMouseEvent*.
     */
    void mouseReleased(QMouseEvent *event);

    /**
     * @brief Slot invoked when the user moves the mouse.
     *
     * @param event is the QMouseEvent*.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void mouseMoved(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Slot invoked when the user scrolls the wheel of the mouse button.
     *
     * @param event is the QWheelEvent*.
     */
    void wheelScrolled(QWheelEvent *event);

    /**
     * @brief Slot invoked when the user presses a key on the keyboard.
     *
     * @param event is the QKeyEvent*.
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief slot invoked when the cube has a collision with an obstacle.
     *
     */
    void collided();

    /**
     * @brief slot invoked when level is completed.
     *
     */
    void levelCompleted();


signals:

    /**
     * @brief signal emitted to pause the game.
     *
     */
    void pauseGameSignal();

    /**
     * @brief signal emitted to continue the game.
     *
     */
    void continueGameSignal();

    /**
     * @brief signal emitted to close the game.
     *
     */
    void gameClosedSignal();

    /**
     * @brief This signal is emitted to set the Qubet's Mouse Move Tracking sensibility.
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

    void keyPressedSignal(QKeyEvent *event);

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

    /**
     * @brief Signal emitted to set the Skybox.
     *
     * @param skyboxName is the name of the Skybox to apply.
     */
    void setSkybox(QString skyboxName);

};

#endif // GAME_H
