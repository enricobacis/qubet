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

class Game : public QThread
{
    Q_OBJECT

public:
    explicit Game(GLint _gameType, QImage *_skin, QMap<Vector3f, GLint> *_obstacleModelsList, QObject *parent = 0);
    ~Game();

    void newGameStory(QMap<QString, GLint> &_levelList);
    void newGameArcade(QString filename);
    void draw();
    void start();

private:
    QMap<QString, GLint> *levelList;
    QMap<Vector3f, GLint> *obstacleModelsList;
    QImage *skin;
    Cube *cube;
    Level *level;
    PositionController *positionController;
    GLint state;
    GLint gameType;
    GLint currentLevel;
    GLint deaths;

    void playLevel(GLint levelId);
    void nextLevel(GLint currentLevelId);
    void pauseGame();
    void continueGame();
    void quitGame();
    void run();

private slots:
    void collided();
    void levelCompleted();
    void keyPressed(QKeyEvent *e);
    void itemClicked(GLint id);

signals:
    void pauseGame();
    void continueGame();
    void enableAudio(bool enabled);
    void playAmbientMusic(QString filename);
    void pauseAmbientMusic();
    void continueAmbientMusic();
    void playEffect(GLint effectId);

};

#endif // GAME_H
