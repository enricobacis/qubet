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
    width(WIDTH),
    height(HEIGHT)
{
    setFocusPolicy(Qt::StrongFocus);

    currentText = "Caricamento ...";

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

    this->setMouseTracking(TRUE);

    initializeGL();
}

Qubet::~Qubet()
{
    if (drawTimer != NULL)
        drawTimer->stop();

    if (audioManager != NULL)
        audioManager->~AudioManager();

    if (loader != NULL)
        loader->~Loader();

    if (game != NULL)
        game->~Game();

    if (levelEditor != NULL)
        levelEditor->~LevelEditor();

    if (menu != NULL)
        menu->~Menu();
}

GLvoid Qubet::initializeGL()
{

}

GLvoid Qubet::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    drawScene();
    swapBuffers();
}

GLvoid Qubet::resizeGL(GLint _width, GLint _height)
{
    width = _width;
    height = _height;
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat) width / (GLfloat) height, 0.1f, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

GLvoid Qubet::mousePressEvent(QMouseEvent *event)
{
    emit itemClicked(getPickedName(event->x(), event->y()));
}

GLvoid Qubet::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}

GLvoid Qubet::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event, getPickedName(event->x(), event->y()));
}

GLvoid Qubet::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);

    QWidget::keyPressEvent(event);
}

GLvoid Qubet::connectInputEvents(const QObject *receiver)
{
    connect(this, SIGNAL(itemClicked(QList<GLuint>)), receiver, SLOT(itemClicked(QList<GLuint>)));
    connect(this, SIGNAL(keyPressed(QKeyEvent*)), receiver, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoved(QMouseEvent*, QList<GLuint>)), receiver, SLOT(mouseMoved(QMouseEvent*, QList<GLuint>)));
    connect(this, SIGNAL(mouseReleased(QMouseEvent*)), receiver, SLOT(mouseReleased(QMouseEvent*)));
}

QList<GLuint> Qubet::getPickedName(GLint mouseX, GLint mouseY)
{
    QList<GLuint> listNames;

    // Impostiamo il buffer per la selezione
    GLuint selectBuffer[BUFSIZE];
    glSelectBuffer(BUFSIZE, selectBuffer);

    // Salviamo nella variabile viewport la viewport corrente [x, y, w, h]
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Passiamo in modalita' selezione
    glRenderMode(GL_SELECT);

    // Modifichiamo la proiezione attuale
    // Vogliamo disegnare solo un piccolo quadrato intorno al mouse
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        gluPickMatrix(mouseX, viewport[3] - mouseY, 1, 1, viewport);
        gluPerspective(45, (GLfloat)viewport[2]/(GLfloat)viewport[3], 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);

    // Ridisegniamo la scena semplificata (in selection mode)
    // (questo avverra' nel back buffer e quindi non si vedra'.
    drawScene(true);

    // Ripristiniamo le precondizioni
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
        glFlush();

    // Tornando in modalita' RENDER ci viene detto quanti oggetti sono stati disegnati
    GLint hits = glRenderMode(GL_RENDER);

    // Algoritmo per cercare l'oggetto disegnato piu' vicino alla camera
    GLint itemLine = 0;
    GLuint minZ = 0;
    GLuint currentZ = 0;

    for (GLint i = 0; i < hits ; i++)
    {
        // Aggiorniamo la Z minima
        currentZ = selectBuffer[itemLine + 1];

        if ((minZ == 0) || (currentZ < minZ))
        {
            minZ = currentZ;

            // Svuotiamo la lista dei nomi correnti
            listNames.clear();
        }

        // Aggiungo tutti i nomi dell'oggetto alla lista dei nomi
        // (i nomi iniziano dopo 3 righe)
        for (GLuint i = 0; i < selectBuffer[itemLine]; i++)
        {
            listNames.append(selectBuffer[itemLine + 3 + i]);
        }

        // sposto la linea corrente al prossimo oggetto.
        itemLine += (3 + selectBuffer[itemLine]);
    }

    return listNames;
}

GLvoid Qubet::loadingStepCompleted()
{
    --loadingSteps;

    if (loadingSteps == 0)
        loadingCompleted();
}

GLvoid Qubet::loadingCompleted()
{
    loader->~Loader();
    loader = NULL;
    currentText.clear();

    showMenu();
}

GLvoid Qubet::connectAudio(const QObject *sender)
{
    connect(sender, SIGNAL(enableAudio(GLboolean)), audioManager, SLOT(enableAudio(GLboolean)));
    connect(sender, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(sender, SIGNAL(pauseAmbientMusic()), audioManager, SLOT(pauseAmbientMusic()));
    connect(sender, SIGNAL(continueAmbientMusic()), audioManager, SLOT(continueAmbientMusic()));
    connect(sender, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));
}

GLvoid Qubet::connectGame()
{
    connectAudio(game);
    connect(game, SIGNAL(gameClosed()), this, SLOT(gameClosed()));
}

GLvoid Qubet::connectMenu()
{
    connectInputEvents(menu);

    connect(menu, SIGNAL(playStory(GLint)), this, SLOT(playStory(GLint)));
    connect(menu, SIGNAL(playArcade(GLint, QString)), this, SLOT(playArcade(GLint, QString)));
    connect(menu, SIGNAL(showLevelEditor()), this, SLOT(showLevelEditor()));

    connect(menu, SIGNAL(enableAudio(GLboolean)), audioManager, SLOT(enableAudio(GLboolean)));
    connect(menu, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(menu, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));
}

GLvoid Qubet::showMenu()
{
    menu = new Menu(skinsList, levelsList, this);
    currentView = MENU_VIEW;
    connectMenu();
}

GLvoid Qubet::menuClosed()
{
    menu->~Menu();
    menu = NULL;
}

GLvoid Qubet::drawScene(GLboolean simplifyForPicking)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glInitNames();

    glLoadIdentity();
    gluLookAt( 0.0,  0.0,  20.0,
               0.0,  0.0,  0.0,
               0.0,  1.0,  0.0);

    if (!currentText.isEmpty() && !simplifyForPicking)
        renderText(width/2 - currentText.length()*2.5 , height - 50, currentText);

    switch(currentView)
    {
    case MENU_VIEW:
        menu->draw(simplifyForPicking);
        break;

    case GAME_VIEW:
        game->draw(simplifyForPicking);
        break;

    case LEVELEDITOR_VIEW:
        levelEditor->draw(simplifyForPicking);
        break;
    }
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
    currentText = "Ostacoli caricati.";
    loadingStepCompleted();
}

void Qubet::errorLoading()
{
    currentText = "Errore di caricamento.";
}

void Qubet::playStory(GLint skinId)
{
    game = new Game(STORY_MODE, skinsList.value(skinId), levelsList, obstacleModelsList, this);

    connectGame();

    game->newGameStory();
    currentView = GAME_VIEW;

    menuClosed();
}

void Qubet::playArcade(GLint skinId, QString levelFilename)
{
    game = new Game(ARCADE_MODE, skinsList[skinId], levelsList, obstacleModelsList, this);

    connectGame();

    game->newGameArcade(levelFilename);
    currentView = GAME_VIEW;

    menuClosed();
}

void Qubet::gameClosed()
{
    game->~Game();
    game = NULL;

    showMenu();
}

void Qubet::showLevelEditor()
{
    levelEditor = new LevelEditor(obstacleModelsList, levelsList, this);

    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));

    connect(levelEditor, SIGNAL(enableAudio(GLboolean)), audioManager, SLOT(enableAudio(GLboolean)));
    connect(levelEditor, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(levelEditor, SIGNAL(playEffect(GLint)), audioManager, SLOT(playEffect(GLint)));

    currentView = LEVELEDITOR_VIEW;

    menuClosed();
}

void Qubet::levelEditorClosed()
{
    levelEditor->~LevelEditor();
    levelEditor = NULL;

    showMenu();
}
