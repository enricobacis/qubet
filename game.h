#ifndef GAME_H
#define GAME_H

#include <QtOpenGL>
#include <QMap>
#include <QKeyEvent>

#include "game_defines.h"

#include "cube.h"
#include "level.h"
#include "positioncontroller.h"
#include "skin.h"

#include "vector3f.h"


/**
 * @brief
 *
 */
class Game : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param _gameType
     * @param _skin
     * @param _obstacleModelsList
     * @param _parent
     */
    explicit Game(GLint _gameType, Skin *_skin, QMap<GLint,QString> &_levelsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent = 0);

    /**
     * @brief
     *
     */
    ~Game();

    /**
     * @brief
     *
     */
    void newGameStory();

    /**
     * @brief
     *
     * @param filename
     */
    void newGameArcade(QString filename);


    /**
     * @brief Method to draw the game.
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    void draw(GLboolean simplifyForPicking = false);


private:
    QObject *parent; /**< TODO */
    QMap<GLint,QString> levelsList; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    Skin *skin; /**< TODO */
    Cube *cube; /**< TODO */
    Level *level; /**< TODO */
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
     */
    void mouseMoved(QMouseEvent *event);

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
     * @param enabled
     */
    void enableAudio(bool enabled);

    /**
     * @brief
     *
     * @param filename
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief
     *
     */
    void pauseAmbientMusic();

    /**
     * @brief
     *
     */
    void continueAmbientMusic();

    /**
     * @brief
     *
     * @param effectId
     */
    void playEffect(GLint effectId);

    /**
     * @brief
     *
     */
    void gameClosed();

};

#endif // GAME_H
