#include "mainqubet.h"
#include "ui_mainqubet.h"

MainQubet::MainQubet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainQubet),
    loadingSteps(STEPS)
{
    ui->setupUi(this);

    loader = new Loader(this);

    connect(loader, SIGNAL(levelsLoaded()), this, SLOT(levelsLoaded()));
    connect(loader, SIGNAL(skinsLoaded()), this, SLOT(skinsLoaded()));
    connect(loader, SIGNAL(obstacleModelsLoaded()), this, SLOT(obstacleModelsLoaded()));

    loader->loadLevels(levelsList);
    loader->loadSkins(skinsList);
    loader->loadObstacleModels(obstacleModelsList);
}

MainQubet::~MainQubet()
{
    drawTimer.stop();
    drawTimer.deleteLater();

    loader->deleteLater();

    delete ui;
}

void MainQubet::loadingStepCompleted()
{
    --loadingSteps;

    if (loadingSteps == 0)
    {
        loadingCompleted();
    }
}

void MainQubet::loadingCompleted()
{
    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(draw()));
    drawTimer.start(30);
}

void MainQubet::skinsLoaded()
{
    loadingStepCompleted();
}

void MainQubet::levelsLoaded()
{
    loadingStepCompleted();
}

void MainQubet::obstacleModelsLoaded()
{
    loadingStepCompleted();
}

void MainQubet::draw()
{
    switch(currentView)
    {
    case MENU_VIEW:
        menu->draw();
        break;

    case GAME_VIEW:
        game->draw();
        break;

    case LEVELEDITOR_VIEW:
        levelEditor->draw();
        break;
    }
}

void MainQubet::playStory(GLint skinId)
{
    game = new Game(STORY_MODE, skinsList[skinId], obstacleModelsList, this);
    connect(game, SIGNAL(gameClosed()), this, SLOT(gameClosed()));

    game->newGameStory(levelsList);
    currentView = GAME_VIEW;
}

void MainQubet::playArcade(GLint skinId, QString levelFilename)
{
    game = new Game(ARCADE_MODE, skinsList[skinId], obstacleModelsList, this);
    connect(game, SIGNAL(gameClosed()), this, SLOT(gameClosed()));

    game->newGameArcade(levelFilename);
    currentView = GAME_VIEW;
}

void MainQubet::showLevelEditor()
{
    levelEditor = new LevelEditor(obstacleModelsList, levelsList, this);
    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));

    currentView = LEVELEDITOR_VIEW;
}

void MainQubet::showMenu()
{

}

void MainQubet::levelEditorClosed()
{

}

void MainQubet::gameClosed()
{

}
