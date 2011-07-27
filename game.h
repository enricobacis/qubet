#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>

#include <GL/gl.h>

#include "vector3f.h"
#include "cube.h"
#include "level.h"
#include "positioncontroller.h"

/**
 * @brief
 *
 */
class Game : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param _gameType
     * @param _skin
     * @param
     * @param _obstacleModelsList
     * @param parent
     */
    explicit Game(GLint _gameType, QImage *_skin, QMap<Vector3f*, GLint> &_obstacleModelsList, QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~Game();

    /**
     * @brief
     *
     * @param QMap<QString
     * @param _levelsList
     */
    void newGameStory(QMap<QString, GLint> &_levelsList);
    /**
     * @brief
     *
     * @param filename
     */
    void newGameArcade(QString filename);
    /**
     * @brief
     *
     */
    void draw();

private:
    QMap<QString, GLint> levelsList; /**< TODO */
    QMap<Vector3f*, GLint> obstacleModelsList; /**< TODO */
    QImage *skin; /**< TODO */
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

    /**
     * @brief
     *
     */
    void run();

private slots:
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
    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *e);
    /**
     * @brief
     *
     * @param id
     */
    void itemClicked(GLint id);

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
