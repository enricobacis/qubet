#include "qubet.h"

Qubet::Qubet(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer), parent),
    drawTimer(NULL),
    menu(NULL),
    game(NULL),
    levelEditor(NULL),
    audioManager(NULL),
    alphabet(NULL),
    width(WIDTH),
    height(HEIGHT),
    mouseMovedMode(1)
{
    // Inizialization is done in the initializeGL() function.
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

    if (alphabet != NULL)
        alphabet->~Alphabet();
}

GLvoid Qubet::initializeGL()
{
    currentText = "Caricamento ...";

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
}

GLvoid Qubet::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    drawScene();
    swapBuffers();

    if (!loadDone)
        initQubet();
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
    if (mouseMovedMode != 0)
        emit mouseMoved(event, getPickedName(event->x(), event->y()));
}

GLvoid Qubet::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);

    QWidget::keyPressEvent(event);
}

GLvoid Qubet::initQubet()
{
    loadDone = true;
    setFocusPolicy(Qt::StrongFocus);
    audioManager = new AudioManager(this);
    connectAudio(this);

    if (!load())
        errorLoading();
    else
        loadingCompleted();

    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(draw()));
    drawTimer->start(30);
}

GLvoid Qubet::connectInputEvents(const QObject *receiver)
{
    connect(this, SIGNAL(itemClicked(QList<GLuint>)), receiver, SLOT(itemClicked(QList<GLuint>)));
    connect(this, SIGNAL(keyPressed(QKeyEvent*)), receiver, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoved(QMouseEvent*, QList<GLuint>)), receiver, SLOT(mouseMoved(QMouseEvent*, QList<GLuint>)));
    connect(this, SIGNAL(mouseReleased(QMouseEvent*)), receiver, SLOT(mouseReleased(QMouseEvent*)));
    connect(receiver, SIGNAL(setMouseMovementTracking(int)), this, SLOT(setMouseMovementTracking(int)));
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
    connect(sender, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(sender, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(sender, SIGNAL(playEffect(int)), audioManager, SLOT(playEffect(int)));
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
    connect(menu, SIGNAL(playArcade(GLint, GLint)), this, SLOT(playArcade(GLint, GLint)));
    connect(menu, SIGNAL(showLevelEditor()), this, SLOT(showLevelEditor()));

    connectAudio(menu);
}

GLvoid Qubet::showMenu()
{
    setMouseMovementTracking(MOUSE_MOVED_NONE);
    menu = new Menu(skinsList, levelsList, iconsList, alphabet, this);
    connectMenu();
    emit playAmbientMusic("resources/music/menu.mp3");
    currentView = MENU_VIEW;
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

        if (!loadAlphabet())
            return false;

        if (!loadIcons())
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
    QFile file("resources/skins/skins.xml");
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
        QString path = "resources/skins/";

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
    QDomDocument document("levels");
    QFile file("resources/levels/levels.xml");
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
    QDomElement levelElement = rootElement.firstChildElement("level");

    while(!levelElement.isNull())
    {
        Level *level = new Level(id, levelElement.attribute("filename", ""), this);
        level->setName(levelElement.attribute("name", ""));

        levelsList.insert(id++, level);
        levelElement = levelElement.nextSiblingElement("level");
    }

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
    alphabet = new Alphabet();

    QString lettersPath = "resources/letters";

    QDir letters(lettersPath);
    letters.setFilter(QDir::Dirs);
    letters.setSorting(QDir::Name);

    QChar letter;
    QString currentPath;

    for (uint i = 0; i < letters.count(); i++)
    {
        letter = letters[i].at(0);
        currentPath = lettersPath + "/" + letter;

        QDir textures(currentPath);
        textures.setFilter(QDir::Files);
        textures.setSorting(QDir::Name);

        for (uint j = 0; j < textures.count(); j++)
            alphabet->appendLetterTexture(letter, bindTexture(QImage(currentPath + "/" + textures[j])));
    }
    return true;
}

GLboolean Qubet::loadIcons()
{
    QString iconsPath = "resources/icons/";

    QDomDocument document("icons");
    QFile file(iconsPath + "icons.xml");
    if (!file.open(QIODevice::ReadOnly))
        return false;

    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }

    file.close();

    QDomElement rootElement = document.documentElement();
    QDomElement iconElement = rootElement.firstChildElement("icon");

    while (!iconElement.isNull())
    {
        GLint key = iconElement.attribute("name", "0").toInt();
        GLuint textureID = bindTexture(QImage(iconsPath + iconElement.attribute("filename")));

        iconsList.insert(key, textureID);
        iconElement = iconElement.nextSiblingElement("icon");
    }

    return true;
}

void Qubet::draw()
{
    paintGL();
}

void Qubet::playStory(GLint skinId)
{
    game = new Game(skinsList.value(skinId), levelsList, obstacleModelsList, this);

    connectGame();

    game->startGame();
    currentView = GAME_VIEW;

    menuClosed();
}

void Qubet::playArcade(GLint skinId, GLint levelId)
{
    game = new Game(skinsList.value(skinId), levelsList.value(levelId), obstacleModelsList, this);

    connectGame();

    game->startGame();
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
    //menuClosed();
    currentView = LEVELEDITOR_VIEW;
    levelEditor = new LevelEditor(obstacleModelsList, levelsList, iconsList, alphabet, this);
    connectInputEvents(levelEditor);
    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));
    connectAudio(levelEditor);
}

void Qubet::levelEditorClosed()
{
    levelEditor->~LevelEditor();
    levelEditor = NULL;

    showMenu();
}

void Qubet::setMouseMovementTracking(int mode)
{
    mouseMovedMode = mode;

    switch (mode)
    {
    case 0:
    case 1:
        setMouseTracking(false);
        break;

    case 2:
        setMouseTracking(true);
        break;
    }
}
