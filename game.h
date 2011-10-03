#ifndef GAME_H
#define GAME_H

#include "positioncontroller.h"
#include "skybox.h"

/**
 * @brief
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
     * @param _skyboxesList
     * @param _skin
     * @param _levelsList
     * @param _parent
     * @param _audioEnabled
     * @param _skybox
     */
    explicit Game(QMap<QString,Skybox*> _skyboxesList, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent = 0, bool _audioEnabled = true, Skybox *_skybox = NULL);

    /**
     * @brief
     *
     * @param _skyboxesList
     * @param _skin
     * @param _level
     * @param _parent
     * @param _audioEnabled
     * @param _skybox
     */
    explicit Game(QMap<QString,Skybox*> _skyboxesList, Skin *_skin, Level *_level, QObject *_parent = 0, bool _audioEnabled = true, Skybox *_skybox = NULL);

    /**
     * @brief
     *
     */
    ~Game();

    /**
     * @brief
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
    QObject *parent; /**< TODO */
    QMap<QString,Skybox*> skyboxesList; /**< TODO */
    Skin *skin; /**< TODO */
    Level *level; /**< TODO */
    QMap<GLint,Level*> levelsList; /**< TODO */
    bool audioEnabled; /**< TODO */
    Skybox *skybox; /**< TODO */
    Cube *cube; /**< TODO */
    PositionController *positionController; /**< TODO */
    GLint state; /**< TODO */
    GLint gameType; /**< TODO */
    GLint currentLevel; /**< TODO */
    GLint deaths; /**< TODO */

    /**
     * @brief
     *
     * @param levelId
     */
    void playLevel(GLint levelId);

    /**
     * @brief
     *
     * @param currentLevelId
     */
    void nextLevel(GLint currentLevelId);

    /**
     * @brief
     *
     */
    void pauseGame();

    /**
     * @brief
     *
     */
    void continueGame();

    /**
     * @brief
     *
     */
    void quitGame();


private slots:

    /**
     * @brief Slot called when the user clicks on a item.
     *
     * @param listNames is the QList<GLuint> of item's names.
     */
    void itemClicked(QList<GLuint> listNames);

    /**
     * @brief Slot called when the user releases the mouse button.
     *
     * @param event is the QMouseEvent*.
     */
    void mouseReleased(QMouseEvent *event);

    /**
     * @brief Slot called when the user moves the mouse.
     *
     * @param event is the QMouseEvent*.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void mouseMoved(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Slot called when the user presses a key on the keyboard.
     *
     * @param event is the QKeyEvent*.
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief
     *
     */
    void collided();

    /**
     * @brief
     *
     */
    void levelCompleted();


signals:

    /**
     * @brief
     *
     */
    void pauseGameSignal();

    /**
     * @brief
     *
     */
    void continueGameSignal();

    /**
     * @brief
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

#endif // GAME_H
