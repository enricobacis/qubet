#include "qubet.h"
#include "defines.h"
#include <QDomElement>

Qubet::Qubet(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer), parent),
    currentView(NO_VIEW),
    drawTimer(NULL),
    menu(NULL),
    game(NULL),
    levelEditor(NULL),
    audioManager(NULL),
    alphabet(NULL),
    skybox(NULL),
    explosionShader(NULL),
    width(WIDTH),
    height(HEIGHT),
    mouseMovedMode(MOUSE_MOVED_DOWN),
    loadDone(false),
    currentNewLevelNumber(0)
{
    alphabet = new Alphabet();
    explosionShader = new QGLShaderProgram(this);

    // Inizialization is done in the initializeGL() and paintGL() functions.
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

    GLuint textureID;
    for (QMap<GLint,Skin*>::iterator i = skinsList.begin(); i != skinsList.end(); i++)
    {
        if (i.value() != NULL)
        {
            for (int j = 0; j < 6; j++)
            {
                textureID = dynamic_cast<Skin*>(i.value())->getTexture(j);
                glDeleteTextures(1, &textureID);
            }
        }
    }
    skinsList.~QMap();

    for (QMap<GLint,Level*>::iterator i = levelsList.begin(); i != levelsList.end(); i++)
    {
        if (i.value() != NULL)
            dynamic_cast<Level*>(i.value())->~Level();
    }
    levelsList.~QMap();

    for (QMap<GLint,GLuint>::iterator i = iconsList.begin(); i != iconsList.end(); i++)
    {
        if (i.value() != 0)
            glDeleteTextures(1, &i.value());
    }
    iconsList.~QMap();

    for (QMap<QString,Skybox*>::iterator i = skyboxesList.begin(); i != skyboxesList.end(); i++)
    {
        if (i.value() != NULL)
            dynamic_cast<Skybox*>(i.value())->~Skybox();
    }
    skyboxesList.~QMap();
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
    glEnable(GL_LIGHT1);

    GLfloat lposition0[] = {0.0f, 0.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lposition0);
    GLfloat ldir0[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, ldir0);

    GLfloat lposition1[] = {-8.0f, 5.0f, 6.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, lposition1);
    GLfloat ldir1[] = {1.0f, -1.0f, -1.0f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, ldir1);

    GLfloat ambientLight0[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuseLight0[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specularLight0[] = {0.8f, 0.8f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

    GLfloat ambientLight1[]  = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat diffuseLight1[]  = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat specularLight1[] = {0.4f, 0.4f, 0.4f, 1.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

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
    emit itemClicked(event, getPickedName(event->x(), event->y()));
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

GLvoid Qubet::wheelEvent(QWheelEvent *event)
{
    emit wheelScrolled(event);
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
    connect(this, SIGNAL(itemClicked(QMouseEvent*, QList<GLuint>)), receiver, SLOT(itemClicked(QMouseEvent*, QList<GLuint>)));
    connect(this, SIGNAL(keyPressed(QKeyEvent*)), receiver, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoved(QMouseEvent*, QList<GLuint>)), receiver, SLOT(mouseMoved(QMouseEvent*, QList<GLuint>)));
    connect(this, SIGNAL(mouseReleased(QMouseEvent*)), receiver, SLOT(mouseReleased(QMouseEvent*)));
    connect(this, SIGNAL(wheelScrolled(QWheelEvent*)), receiver, SLOT(wheelScrolled(QWheelEvent*)));
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
    // TODO : Ricordarsi di rimettere l'introduzione successivamente
    showMenu(false);
}

GLvoid Qubet::errorLoading()
{
    currentText = "Errore di caricamento.";
}

GLvoid Qubet::connectAudio(const QObject *sender)
{
    connect(sender, SIGNAL(enableAudio(bool)), audioManager, SLOT(enableAudio(bool)));
    connect(sender, SIGNAL(playAmbientMusic(QString)), audioManager, SLOT(playAmbientMusic(QString)));
    connect(sender, SIGNAL(stopAmbientMusic()), audioManager, SLOT(stopAmbientMusic()));
    connect(sender, SIGNAL(playEffect(QString)), audioManager, SLOT(playEffect(QString)));
}

GLvoid Qubet::connectMenu()
{
    connectInputEvents(menu);

    connect(menu, SIGNAL(playStory(GLint)), this, SLOT(playStory(GLint)));
    connect(menu, SIGNAL(playArcade(GLint, GLint)), this, SLOT(playArcade(GLint, GLint)));
    connect(menu, SIGNAL(showLevelEditor(GLint)), this, SLOT(showLevelEditor(GLint)));

    connectAudio(menu);
}

GLvoid Qubet::connectLevelEditor()
{
    connectInputEvents(levelEditor);

    connect(levelEditor, SIGNAL(addLevelToLevelsList(Level*)), this, SLOT(addLevelToLevelsList(Level*)));
    connect(levelEditor, SIGNAL(levelEditorClosed()), this, SLOT(levelEditorClosed()));

    connectAudio(levelEditor);
}

GLvoid Qubet::connectGame()
{
    connectInputEvents(game);

    connect(game, SIGNAL(gameClosedSignal()), this, SLOT(gameClosed()));

    connectAudio(game);
}

GLvoid Qubet::showMenu(bool showIntro)
{
    setMouseMovementTracking(MOUSE_MOVED_NONE);
    menu = new Menu(skinsList, levelsList, iconsList, alphabet, this, audioManager->isAudioEnabled(), showIntro);
    connectMenu();

    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    currentView = MENU_VIEW;
}

GLvoid Qubet::closeMenu()
{
    if (menu != NULL)
    {
        menu->~Menu();
        menu = NULL;
    }
}

GLvoid Qubet::drawScene(GLboolean simplifyForPicking)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glInitNames();

    gluLookAt( 0.0,  0.0,  20.0,
               0.0,  0.0,  0.0,
               0.0,  1.0,  0.0);

    if (!simplifyForPicking)
    {
        skyboxAngle += 0.1f;
        if (skyboxAngle >= 360.0f)
            skyboxAngle -= 360.0f;

        if (skybox != NULL)
        {
            glPushMatrix();
                glRotatef(skyboxAngle, 0.0f, 1.0f, 0.0f);
                skybox->draw();
            glPopMatrix();
        }

        if (!currentText.isEmpty())
            renderText(width/2 - currentText.length()*2.5 , height - 50, currentText);
    }

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
    if (!loadLevels())
        return false;

#ifndef _DEBUG

    if (!loadSkins())
        return false;

    if (!loadAlphabet())
        return false;

    if (!loadIcons())
        return false;

    if (!loadSkyboxes())
        return false;

    loadShader();

#endif

    return true;
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

    QDomElement rootElement = document.documentElement();
    QDomElement levelElement = rootElement.firstChildElement("level");
    QString name;
    QString filename;

    while(!levelElement.isNull())
    {
        filename = levelElement.attribute("filename", "");
        Level *level = new Level(filename, this);

        name = levelElement.attribute("name", "");
        if (name.isEmpty())
            name = filename.left(filename.lastIndexOf("."));

        level->setName(name);

        ++currentNewLevelNumber;
        GLint levelNumber = levelElement.attribute("story_number", "-1").toInt();

        if (levelNumber == -1)
        {
            levelNumber = currentNewLevelNumber;
            level->setIsInStory(false);
        }
        else
        {
            level->setIsInStory(true);
        }

        levelsList.insert(levelNumber, level);
        levelElement = levelElement.nextSiblingElement("level");
    }

    return true;
}

GLboolean Qubet::loadAlphabet()
{
    QString lettersPath = "resources/letters";

    QDir letters(lettersPath);
    letters.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
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

GLboolean Qubet::loadSkyboxes()
{
    QString skyboxesPath = "resources/skyboxes/";

    QDir skyboxes(skyboxesPath);
    skyboxes.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    skyboxes.setSorting(QDir::Name);

    QString skyboxName;
    Skin *skyboxSkin;
    Skybox *skybox;
    QString currentPath;

    for (uint i = 0; i < skyboxes.count(); i++)
    {
        skyboxName = skyboxes[i];
        currentPath = skyboxesPath + "/" + skyboxName + "/";

        skyboxSkin = new Skin(skyboxName);
        skyboxSkin->setComment("The " + skyboxName + " skybox.");

        skyboxSkin->setTextureXPlus (bindTexture(QImage(currentPath + "x+.jpg")));
        skyboxSkin->setTextureXMinus(bindTexture(QImage(currentPath + "x-.jpg")));
        skyboxSkin->setTextureYPlus (bindTexture(QImage(currentPath + "y+.jpg")));
        skyboxSkin->setTextureYMinus(bindTexture(QImage(currentPath + "y-.jpg")));
        skyboxSkin->setTextureZPlus (bindTexture(QImage(currentPath + "z+.jpg")));
        skyboxSkin->setTextureZMinus(bindTexture(QImage(currentPath + "z-.jpg")));

        skybox = new Skybox(skyboxSkin);

        skyboxesList.insert(skyboxName, skybox);
    }

    return true;
}

GLboolean Qubet::loadShader()
{
    bool successVert = explosionShader->addShaderFromSourceFile(QGLShader::Vertex,   "resources/shaders/toon/toon.vert");
    bool successFrag = explosionShader->addShaderFromSourceFile(QGLShader::Fragment, "resources/shaders/toon/toon.frag");

    return (successVert && successFrag);
}

void Qubet::draw()
{
    paintGL();
}

void Qubet::playStory(GLint skinId)
{
    game = new Game(iconsList, alphabet, skinsList.value(skinId), levelsList, this, audioManager->isAudioEnabled(), explosionShader);

    connectGame();

    game->startGame();

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    currentView = GAME_VIEW;

    closeMenu();
}

void Qubet::playArcade(GLint skinId, GLint levelId)
{
    game = new Game(iconsList, alphabet, skinsList.value(skinId), levelsList.value(levelId), this, audioManager->isAudioEnabled(), explosionShader);

    connectGame();

    game->startGame();

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    currentView = GAME_VIEW;

    closeMenu();
}

void Qubet::gameClosed()
{
    currentView = NO_VIEW;

    showMenu(false);

    if (game != NULL)
    {
        game->~Game();
        game = NULL;
    }
}

void Qubet::showLevelEditor(GLint _levelId)
{
    setMouseMovementTracking(MOUSE_MOVED_FULL);

    Level *level;

    if (_levelId == 0)
        level = NULL;
    else
        level = levelsList.value(_levelId);

    levelEditor = new LevelEditor(iconsList, alphabet, this, level, audioManager->isAudioEnabled());
    connectLevelEditor();

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    currentView = LEVELEDITOR_VIEW;

    closeMenu();
}

void Qubet::addLevelToLevelsList(Level *_level)
{
    levelsList.insert(++currentNewLevelNumber, _level);
}

void Qubet::levelEditorClosed()
{
    currentView = NO_VIEW;

    showMenu(false);

    if (levelEditor != NULL)
    {
        levelEditor->~LevelEditor();
        levelEditor = NULL;
    }
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

void Qubet::setSkybox(QString skyboxName)
{
    skybox = skyboxesList.value(skyboxName);
}
