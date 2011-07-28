#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>
#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QMap>

#include <GL/gl.h>

#include "vector3f.h"
#include "menu.h"
#include "game.h"
#include "audiomanager.h"
#include "loader.h"
#include "leveleditor.h"
#include "qglqubetwidget.h"
#include "defines.h"

namespace Ui {
    class MainQubet;
}

/**
 * @brief
 *
 */
class MainQubet : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MainQubet(QWidget *parent = 0);

    /**
     * @brief
     *
     */
    ~MainQubet();

private:
    Ui::MainQubet *ui; /**< TODO */
    GLint loadingSteps; /**< TODO */
    GLint currentView; /**< TODO */
    QMap<GLint,QImage*> skinsList; /**< TODO */
    QMap<GLint,QString> levelsList; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    QTimer *drawTimer; /**< TODO */
    Loader *loader; /**< TODO */
    Menu *menu; /**< TODO */
    Game *game; /**< TODO */
    LevelEditor *levelEditor; /**< TODO */
    AudioManager *audioManager; /**< TODO */

    /**
     * @brief
     *
     * @param event
     */
    void closeEvent(QCloseEvent *event);

    /**
     * @brief
     *
     */
    void loadingStepCompleted();

    /**
     * @brief
     *
     */
    void loadingCompleted();

private slots:
    /**
     * @brief
     *
     */
    void skinsLoaded();

    /**
     * @brief
     *
     */
    void levelsLoaded();

    /**
     * @brief
     *
     */
    void obstacleModelsLoaded();

    /**
     * @brief
     *
     */
    void errorLoading();

    /**
     * @brief
     *
     */
    void draw();

    /**
     * @brief
     *
     * @param skinId
     */
    void playStory(GLint skinId);

    /**
     * @brief
     *
     * @param skinId
     * @param levelFilename
     */
    void playArcade(GLint skinId, QString levelFilename);

    /**
     * @brief
     *
     */
    void connectGame();

    /**
     * @brief
     *
     */
    void showLevelEditor();

    /**
     * @brief
     *
     */
    void showMenu();

    /**
     * @brief
     *
     */
    void gameClosed();

    /**
     * @brief
     *
     */
    void levelEditorClosed();

    /**
     * @brief
     *
     */
    void menuClosed();

};

#endif // MAINQUBET_H
