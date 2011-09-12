#include "qubet.h"

Qubet::Qubet(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer), parent),
    loadingSteps(STEPS),
    drawTimer(NULL),
    loader(NULL),
    menu(NULL),
    game(NULL),
    levelEditor(NULL),
    audioManager(NULL),
    width(STD_WIDTH),
    height(STD_HEIGHT)
{
    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(draw()));
    drawTimer->start(30);

    audioManager = new AudioManager(this);
    loader = new Loader(skinsList, obstacleModelsList, levelsList, this);

    connect(loader, SIGNAL(levelsLoaded()), this, SLOT(levelsLoaded()));
    connect(loader, SIGNAL(skinsLoaded()), this, SLOT(skinsLoaded()));
    connect(loader, SIGNAL(obstacleModelsLoaded()), this, SLOT(obstacleModelsLoaded()));
    connect(loader, SIGNAL(errorLoading()), this, SLOT(errorLoading()));

    loader->load();
}

Qubet::~Qubet()
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
}

void Qubet::initializeGL()
{
}

void Qubet::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt( 0.0,  0.0, -5.0,
               0.0,  0.0,  0.0,
               0.0,  1.0,  0.0);

    if (!currentText.isEmpty())
        renderText(width/2 - currentText.length()*2.5 , height - 50, currentText);

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

    swapBuffers();
}

void Qubet::resizeGL(int _width, int _height)
{
    width = _width;
    height = _height;

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void Qubet::mousePressEvent(QMouseEvent *event)
{

}

void Qubet::mouseMoveEvent(QMouseEvent *event)
{

}

void Qubet::keyPressEvent(QKeyEvent *event)
{

}

void Qubet::loadingStepCompleted()
{
    --loadingSteps;

    if (loadingSteps == 0)
        loadingCompleted();
}

void Qubet::loadingCompleted()
{
    showMenu();
}

void Qubet::connectGame()
{
    connect(game, SIGNAL(gameClosed()), this, SLOT(gameClosed()));

    connect(game, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(game, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(game, SIGNAL(pauseAmbientMusic()), audioManager, SLOT(pauseAmbientMusic()));
    connect(game, SIGNAL(continueAmbientMusic()), audioManager, SLOT(continueAmbientMusic()));
    connect(game, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));
}

void Qubet::showMenu()
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

void Qubet::menuClosed()
{
    menu->deleteLater();
    menu = NULL;
}

void Qubet::draw()
{
    paintGL();
}

void Qubet::skinsLoaded()
{
    currentText = "Skins caricate.";
    loadingStepCompleted();
}

void Qubet::levelsLoaded()
{
    currentText = "Livelli caricati.";
    loadingStepCompleted();
}

void Qubet::obstacleModelsLoaded()
{
    currentText = "Modelli di Ostacoli caricati.";
    loadingStepCompleted();
}

void Qubet::errorLoading()
{
    currentText = "Errore di caricamento.";
}

void Qubet::playStory(GLint skinId)
{
    game = new Game(STORY_MODE, skinsList.value(skinId), obstacleModelsList, this);

    connectGame();

    game->newGameStory(levelsList);
    currentView = GAME_VIEW;

    menuClosed();
}

void Qubet::playArcade(GLint skinId, QString levelFilename)
{
    game = new Game(ARCADE_MODE, skinsList[skinId], obstacleModelsList, this);

    connectGame();

    game->newGameArcade(levelFilename);
    currentView = GAME_VIEW;

    menuClosed();
}

void Qubet::gameClosed()
{
    game->deleteLater();
    game = NULL;

    showMenu();
}

void Qubet::showLevelEditor()
{
    levelEditor = new LevelEditor(obstacleModelsList, levelsList, this);

    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));

    connect(levelEditor, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(levelEditor, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(levelEditor, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));

    currentView = LEVELEDITOR_VIEW;

    menuClosed();
}

void Qubet::levelEditorClosed()
{
    levelEditor->deleteLater();
    levelEditor = NULL;

    showMenu();
}
