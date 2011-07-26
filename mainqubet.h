#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QTimer>

#include <GL/gl.h>

#include "vector3f.h"
#include "menu.h"
#include "game.h"
#include "audiomanager.h"

namespace Ui {
    class MainQubet;
}

class MainQubet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainQubet(QWidget *parent = 0);
    ~MainQubet();

private:
    Ui::MainQubet *ui;
    GLint loadingSteps;
    GLint currentView;
    QMap<QImage*, GLint> skinsList;
    QMap<QString, GLint> levelsList;
    QMap<Vector3f, GLint> obstacleModelsList;
    QTimer drawTimer;
    Menu *menu;
    Game *game;
    AudioManager *audioManager;
    void loadingStepCompleted();
    void loadingCompleted();
    void drawAll();

private slots:
    void skinsLoaded();
    void levelsLoaded();
    void obstacleModelsLoaded();
    void playStory(GLint skinId);
    void playArcade(GLint skinId, QString levelFilename);
    void levelEditor();
    void showMenu();

private:

};

#endif // MAINQUBET_H
