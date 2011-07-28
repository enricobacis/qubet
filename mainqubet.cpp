#include "mainqubet.h"
#include "ui_mainqubet.h"

MainQubet::MainQubet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainQubet),
    loadingSteps(STEPS),
    drawTimer(NULL),
    loader(NULL),
    menu(NULL),
    game(NULL),
    levelEditor(NULL),
    audioManager(NULL)
{
    ui->setupUi(this);
    setWindowTitle("Qubet " + QString(QUBET_VERSION));

    audioManager = new AudioManager(this);
    loader = new Loader(skinsList, obstacleModelsList, levelsList, this);

    connect(loader, SIGNAL(levelsLoaded()), this, SLOT(levelsLoaded()));
    connect(loader, SIGNAL(skinsLoaded()), this, SLOT(skinsLoaded()));
    connect(loader, SIGNAL(obstacleModelsLoaded()), this, SLOT(obstacleModelsLoaded()));
    connect(loader, SIGNAL(errorLoading()), this, SLOT(errorLoading()));

    loader->load();
}

MainQubet::~MainQubet()
{
    delete ui;
}

void MainQubet::closeEvent(QCloseEvent *event)
{
    if (drawTimer != NULL)
    {
        drawTimer->stop();
        drawTimer->deleteLater();
    }

    if (audioManager != NULL)
        audioManager->deleteLater();

    if (loader != NULL)
        loader->deleteLater();

    if (game != NULL)
        game->deleteLater();

    if (levelEditor != NULL)
        levelEditor->deleteLater();

    if (menu != NULL)
        menu->deleteLater();

    event->accept();
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

void MainQubet::errorLoading()
{

}

void MainQubet::loadingStepCompleted()
{
    --loadingSteps;

    if (loadingSteps == 0)
        loadingCompleted();
}

void MainQubet::loadingCompleted()
{
    showMenu();

    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(draw()));
    drawTimer->start(30);
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
    game = new Game(STORY_MODE, skinsList.value(skinId), obstacleModelsList, this);

    connectGame();

    game->newGameStory(levelsList);
    currentView = GAME_VIEW;

    menuClosed();
}

void MainQubet::playArcade(GLint skinId, QString levelFilename)
{
    game = new Game(ARCADE_MODE, skinsList[skinId], obstacleModelsList, this);

    connectGame();

    game->newGameArcade(levelFilename);
    currentView = GAME_VIEW;

    menuClosed();
}

void MainQubet::connectGame()
{
    connect(game, SIGNAL(gameClosed()), this, SLOT(gameClosed()));

    connect(game, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(game, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(game, SIGNAL(pauseAmbientMusic()), audioManager, SLOT(pauseAmbientMusic()));
    connect(game, SIGNAL(continueAmbientMusic()), audioManager, SLOT(continueAmbientMusic()));
    connect(game, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));
}

void MainQubet::showLevelEditor()
{
    levelEditor = new LevelEditor(obstacleModelsList, levelsList, this);

    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));

    connect(levelEditor, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(levelEditor, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(levelEditor, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));

    currentView = LEVELEDITOR_VIEW;

    menuClosed();
}

void MainQubet::showMenu()
{
    menu = new Menu(skinsList, levelsList, this);

    connect(menu, SIGNAL(playStory(GLint)), this, SLOT(playStory(GLint)));
    connect(menu, SIGNAL(playArcade(GLint, QString)), this, SLOT(playArcade(GLint, QString)));
    connect(menu, SIGNAL(showLevelEditor()), this, SLOT(showLevelEditor()));

    connect(menu, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(menu, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(menu, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));

    currentView = MENU_VIEW;
}

void MainQubet::levelEditorClosed()
{
    levelEditor->deleteLater();
    levelEditor = NULL;

    showMenu();
}

void MainQubet::gameClosed()
{
    game->deleteLater();
    game = NULL;

    showMenu();
}

void MainQubet::menuClosed()
{
    menu->deleteLater();
    menu = NULL;
}
