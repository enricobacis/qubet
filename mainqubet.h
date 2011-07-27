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
#include "loader.h"
#include "leveleditor.h"
#include "defines.h"

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
    QMap<Vector3f*, GLint> obstacleModelsList;
    QTimer drawTimer;
    Loader *loader;
    Menu *menu;
    Game *game;
    LevelEditor *levelEditor;
    AudioManager *audioManager;
    void loadingStepCompleted();
    void loadingCompleted();

private slots:
    void skinsLoaded();
    void levelsLoaded();
    void obstacleModelsLoaded();
    void draw();
    void playStory(GLint skinId);
    void playArcade(GLint skinId, QString levelFilename);
    void showLevelEditor();
    void showMenu();
    void gameClosed();
    void levelEditorClosed();

};

#endif // MAINQUBET_H
