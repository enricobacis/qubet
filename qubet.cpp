#include "qubet.h"

Qubet::Qubet(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer), parent),
    drawTimer(NULL),
    menu(NULL),
    game(NULL),
    levelEditor(NULL),
    audioManager(NULL),
    width(WIDTH),
    height(HEIGHT)
{
    // OpenGL dependencies will be initialized in InitializeGL function.

    setFocusPolicy(Qt::StrongFocus);
    audioManager = new AudioManager(this);
    setMouseTracking(true);
}

Qubet::~Qubet()
{
    if (drawTimer != NULL)
        drawTimer->stop();

    if (audioManager != NULL)
        audioManager->~AudioManager();

    if (game != NULL)
        game->~Game();

    if (levelEditor != NULL)
        levelEditor->~LevelEditor();

    if (menu != NULL)
        menu->~Menu();
}

GLvoid Qubet::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lposition[] = {0.0f, 0.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lposition);
    GLfloat ldir[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, ldir);

    GLfloat ambientLight[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuseLight[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specularLight[] = {0.8f, 0.8f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    glShadeModel(GL_SMOOTH);

    currentText = "Caricamento ...";

    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(draw()));
    drawTimer->start(30);

    if (!load())
        errorLoading();
    else
        loadingCompleted();
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

GLvoid Qubet::loadingCompleted()
{
    currentText.clear();
    showMenu();
}

GLvoid Qubet::errorLoading()
{
    currentText = "Errore di caricamento.";
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
    connectMenu();
    currentView = MENU_VIEW;
    menu->playAudio();
}

GLvoid Qubet::menuClosed()
{
    menu->~Menu();
    menu = NULL;
}

GLvoid Qubet::drawScene(GLboolean simplifyForPicking)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glInitNames();

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

GLboolean Qubet::load()
{
    try
    {
        if (!loadSkins())
            return false;

        if (!loadLevels())
            return false;

        if (!loadObstacleModels())
            return false;

        return true;
    }
    catch (...)
    {
        return false;
    }

}

GLboolean Qubet::loadSkins()
{
    QDomDocument document("skins");
    QFile file(":/skins/resources/skins/skins.xml");
    if (!file.open(QIODevice::ReadOnly))
        return false;

    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }

    file.close();

    GLint id = 1;
    QDomElement rootElement = document.documentElement();
    QDomElement skinElement = rootElement.firstChildElement("skin");

    while(!skinElement.isNull())
    {
        QString path = ":/skins/resources/skins/";

        Skin *skin = new Skin(skinElement.attribute("name", "Unknown"));
        skin->setComment(skinElement.attribute("comment"));

        if (skinElement.hasAttribute("folder"))
            path = path + skinElement.attribute("folder") + "/";

        if (skinElement.attribute("autofind", "false") == "true")
        {

            QString extension = skinElement.attribute("extension", "png");
            skin->setTextureXPlus (bindTexture(QImage(path + "x+." + extension)));
            skin->setTextureXMinus(bindTexture(QImage(path + "x-." + extension)));
            skin->setTextureYPlus (bindTexture(QImage(path + "y+." + extension)));
            skin->setTextureYMinus(bindTexture(QImage(path + "y-." + extension)));
            skin->setTextureZPlus (bindTexture(QImage(path + "z+." + extension)));
            skin->setTextureZMinus(bindTexture(QImage(path + "z-." + extension)));
        }
        else if (skinElement.hasAttribute("repeat"))
        {
            skin->setTextureForAllFaces(bindTexture(QImage(path + skinElement.attribute("repeat"))));
        }
        else
        {
            skin->setTextureXPlus (bindTexture(QImage(path + skinElement.attribute("x_plus"))));
            skin->setTextureXMinus(bindTexture(QImage(path + skinElement.attribute("x_minus"))));
            skin->setTextureYPlus (bindTexture(QImage(path + skinElement.attribute("y_plus"))));
            skin->setTextureYMinus(bindTexture(QImage(path + skinElement.attribute("y_minus"))));
            skin->setTextureZPlus (bindTexture(QImage(path + skinElement.attribute("z_plus"))));
            skin->setTextureZMinus(bindTexture(QImage(path + skinElement.attribute("z_minus"))));
        }

        skinsList.insert(id++, skin);
        skinElement = skinElement.nextSiblingElement("skin");
    }

    if (!loadCustomSkins())
        return false;

    return true;
}

GLboolean Qubet::loadCustomSkins()
{
    // future implementation
    return true;
}

GLboolean Qubet::loadObstacleModels()
{
    // TODO

    if (!loadCustomObstacleModels())
        return false;

    return true;
}

GLboolean Qubet::loadCustomObstacleModels()
{
    // future implementation
    return true;
}

GLboolean Qubet::loadLevels()
{
    // TODO
    if (!loadCustomLevels())
        return false;

    return true;
}

GLboolean Qubet::loadCustomLevels()
{
    // future implementation
    return true;
}

GLboolean Qubet::loadAlphabet()
{
    return true;
}

void Qubet::draw()
{
    paintGL();
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
