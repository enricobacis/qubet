#include "menu.h"
#include "menu_defines.h"

Menu::Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,Level*> &_levelsList, QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent) :
    parent(_parent),
    currentSkin(1),
    currentLevel(0),
    skinsList(_skinsList),
    levelsList(_levelsList),
    iconsList(_iconsList),
    alphabet(_alphabet),
    isMoving(true),
    gameType(0),
    angleRotCube(0),
    spinCube(0),
    angleRotVolumeCube(0),
    audioEnabled(true),
    volumeSkin(NULL),
    currentView(MAIN_VIEW),
    storyButton(NULL),
    arcadeButton(NULL),
    editorButton(NULL),
    backButton(NULL),
    playButton(NULL),
    levelsButton(NULL)
{
    currentActions = new ActionList(INITIAL_MOTION);
    cameraOffset = new Vector3f(0.0, 0.0, 10.0);

    storyButton = new CubeString("story", 3, BUTTON_PLAY_STORY, alphabet);
    arcadeButton = new CubeString("arcade", 3, BUTTON_PLAY_ARCADE, alphabet);
    editorButton = new CubeString("editor", 3, BUTTON_LEVEL_EDITOR, alphabet);
    backButton = new CubeString("back", 1, BUTTON_BACK, alphabet);
    playButton = new CubeString("play", 1, BUTTON_NEXT, alphabet);
    levelsButton = new CubeString("levels", 1, BUTTON_NEXT, alphabet);
    editButton = new CubeString("edit", 1, BUTTON_NEXT, alphabet);

    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2, SKIN_NAME, alphabet);
    levelName = new CubeStringList("non tirarmi la maglietta", 12.0, 7.0, LEVEL_NAME, alphabet);

    QList< QPair<QString,GLuint> > list;
    list.append(QPair<QString,GLuint>("The Cube Studios", 150));
    list.append(QPair<QString,GLuint>("Distribution", 151));
    list.append(QPair<QString,GLuint>("presents", 152));

    cubeStudiosLabel = new CubeStringList(list, 1.5, alphabet);
    cubeStudiosLabel->setCurrentAngle(0, -20);
    cubeStudiosLabel->startStringListRotation(10, 4);

    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);
}

Menu::~Menu()
{
    if (storyButton != NULL)
        storyButton->~CubeString();

    if (arcadeButton != NULL)
        arcadeButton->~CubeString();

    if (editorButton != NULL)
        editorButton->~CubeString();

    if (backButton != NULL)
        backButton->~CubeString();

    if (playButton != NULL)
        playButton->~CubeString();

    if (levelsButton != NULL)
        levelsButton->~CubeString();

    if (editButton != NULL)
        editButton->~CubeString();

    if (skinName != NULL)
        skinName->~CubeString();

    if (levelName != NULL)
        levelName->~CubeStringList();

    if (volumeSkin != NULL)
        volumeSkin->~Skin();

    //parent->disconnect(this);
}

GLvoid Menu::draw(GLboolean simplifyForPicking)
{
    // Calcolo nuovo Frame

    if (!simplifyForPicking)
    {
        QList<int> actions = currentActions->getAllActions();

        while (!actions.isEmpty())
        {
            // Primary Actions

            GLint step = actions.takeFirst();
            switch (step)
            {
            case INITIAL_MOTION:
                cameraOffset->z -= 0.5;

                if (cameraOffset->z == 0)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    currentView = MAIN_VIEW;
                    isMoving = false;
                }

                break;

            case GO_TO_MAIN_VIEW:
                if (gameType == EDITOR_MODE)
                {
                    cameraOffset->x -= 0.5;
                    cameraOffset->y -= 1;
                }
                else
                {
                    cameraOffset->x -= 1;
                }

                if(cameraOffset->x == 0)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    currentView = MAIN_VIEW;
                    isMoving = false;
                }
                break;

            case GO_TO_SKINS_VIEW:
                if (currentView == LEVELS_VIEW)
                {
                    cameraOffset->x += 0.5;
                    cameraOffset->y -= 1;
                }
                else
                {
                    cameraOffset->x += 1;
                }
                if (cameraOffset->x == 30)
                {
                    currentActions->setPrimaryAction(ROTATE_SKINCUBE);
                    currentView = SKINS_VIEW;
                    isMoving = false;
                }

                break;

            case GO_TO_LEVELS_VIEW:
                if (currentView == MAIN_VIEW)
                {
                   cameraOffset->x += 0.5;
                   cameraOffset->y += 1;
                }
                else
                {
                    cameraOffset->x -= 0.5;
                    cameraOffset->y += 1;
                }
                if (cameraOffset->x == 15)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    currentView = LEVELS_VIEW;
                    isMoving = false;
                }
                break;

            case ROTATE_SKINCUBE:
                angleRotCube += 2;

                if (angleRotCube >= 360)
                    angleRotCube = GLint(angleRotCube) % 360;

                break;

            case PREVIOUS_SKIN:
            case NEXT_SKIN:
                spinCube += 2;
                angleRotCube += 2 + (spinCube <= 30 ? spinCube : 60 - spinCube);

                if (spinCube == 30)
                {
                    if (step == PREVIOUS_SKIN)
                        previousSkin();
                    else
                        nextSkin();
                }
                else if (spinCube == 60)
                {
                    spinCube = 0;
                    isMoving = false;
                    currentActions->setPrimaryAction(ROTATE_SKINCUBE);
                }

                break;

            case EXIT_FROM_LEVELS:
                cameraOffset->y += 2;
                if (cameraOffset->y == 90)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);

                    if (gameType == ARCADE_MODE)
                    {
                        //emit playArcade(currentSkin, currentLevel);
                    }
                    else if (gameType == EDITOR_MODE)
                        emit showLevelEditor();
                }
                break;

            case EXIT_FROM_SKINS:
                cameraOffset->x += 2;
                if (cameraOffset->x == 90)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    //emit playStory(currentSkin);
                }

                break;

            // Secondary Actions

            case ROTATE_VOLUMECUBE:
                angleRotVolumeCube += 5;

                if ((GLint(angleRotVolumeCube) % 360) == 0)
                    angleRotVolumeCube = 0;

                if ((GLint(angleRotVolumeCube) % 90) == 0)
                    currentActions->removeSecondaryAction(ROTATE_VOLUMECUBE);

                break;
            }
        }
    }

    // Disegno il menu

    if (!(isMoving && simplifyForPicking))
    {
        glPushName(BUTTON_VOLUME);
        glPushMatrix();
            glTranslatef(9.5, 6.0, 3.0);
            glRotatef(angleRotVolumeCube, -1.0, 0.0, 0.0);
            drawPrism(0.8, 0.8, 0.8, volumeSkin, true);
        glPopMatrix();
        glPopName();

        glPushMatrix();

            glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);

            glTranslatef(0.0, 5.0, 0.0);
            storyButton->draw(simplifyForPicking);

            glTranslatef(0.0, -10.0, 0.0);
            editorButton->draw(simplifyForPicking);

            glTranslatef(0.0, 5.0, 0.0);
            arcadeButton->draw(simplifyForPicking);

            glPushMatrix();
                glTranslatef(30.0, 4.0, 0.0);

                skinName->draw(simplifyForPicking);
                QString comment = skinsList.value(currentSkin)->getComment();
                dynamic_cast<QGLWidget*>(parent)->renderText(-comment.length()*0.1225, -2.5, 0.0, comment);

                glTranslatef(0.0, -6.0, 0.0);

                glPushName(SKIN_CUBE);
                glPushMatrix();
                    glRotatef(angleRotCube, 0.0, -1.0, 0.0);
                    drawPrism(3.0, 3.0, 3.0, skinsList.value(currentSkin));
                glPopMatrix();
                glPopName();

                glPushName(BUTTON_PREVIOUS_SKIN);
                glTranslatef(-5.0, 0.0, 0.0);
                glBegin(GL_TRIANGLES);
                    glVertex3f(-1.0,  0.0,  0.0);
                    glVertex3f( 1.0,  1.0,  0.0);
                    glVertex3f( 1.0, -1.0,  0.0);
                glEnd();
                glPopName();

                glTranslatef(-3.0, -4.0, 0.0);
                backButton->draw(simplifyForPicking);
                glPopName();

                glPushName(BUTTON_NEXT_SKIN);
                glTranslatef(13.0, 4.0, 0.0);
                glBegin(GL_TRIANGLES);
                    glVertex3f( 1.0,  0.0,  0.0);
                    glVertex3f(-1.0,  1.0,  0.0);
                    glVertex3f(-1.0, -1.0,  0.0);
                glEnd();
                glPopName();

                glTranslatef(3.0, -4.0, 0.0);
                if(gameType == STORY_MODE)
                    playButton->draw(simplifyForPicking);
                else
                    levelsButton->draw(simplifyForPicking);

            glPopMatrix();

            glPushMatrix();
                glTranslatef(15.0, 31.0, 0.0);

                levelName->draw(simplifyForPicking);

                glPushName(BUTTON_PREVIOUS_LEVEL);
                glTranslatef(-9.0, 0.0, 0.0);
                glBegin(GL_TRIANGLES);
                    glVertex3f(-1.0,  0.0,  0.0);
                    glVertex3f( 1.0,  1.0,  0.0);
                    glVertex3f( 1.0, -1.0,  0.0);
                glEnd();
                glPopName();

                glTranslatef(1.0, -7.0, 0.0);
                backButton->draw(simplifyForPicking);

                glPushName(BUTTON_NEXT_LEVEL);
                glTranslatef(17.0, 7.0, 0.0);
                glBegin(GL_TRIANGLES);
                    glVertex3f( 1.0,  0.0,  0.0);
                    glVertex3f(-1.0,  1.0,  0.0);
                    glVertex3f(-1.0, -1.0,  0.0);
                glEnd();
                glPopName();

                glTranslatef(-1.0, -7.0, 0.0);
                if (gameType == ARCADE_MODE)
                    playButton->draw(simplifyForPicking);
                else if (gameType == EDITOR_MODE)
                    editButton->draw(simplifyForPicking);

            glPopMatrix();

        glPopMatrix();
    }

    //cubeStudiosLabel->draw(simplifyForPicking);
}

GLvoid Menu::playAudio()
{
    emit playAmbientMusic(":/music/resources/music/menu.mp3");
}

GLvoid Menu::previousSkin()
{
    if (currentSkin == 1)
        currentSkin = skinsList.count();
    else
        currentSkin -= 1;

    skinName->~CubeString();
    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2, SKIN_NAME, alphabet);
}

GLvoid Menu::nextSkin()
{
    if (skinsList.find(currentSkin + 1) == skinsList.end())
        currentSkin = 1;
    else
        currentSkin += 1;

    skinName->~CubeString();
    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2, SKIN_NAME, alphabet);
}

GLvoid Menu::previousLevel()
{
    if ((gameType == ARCADE_MODE) && (currentLevel == 1))
        currentLevel = levelsList.count();
    else if (currentLevel == 0)
        currentLevel = levelsList.count();
    else
        currentLevel -= 1;

    levelName->~CubeStringList();
    levelName = new CubeStringList(((currentLevel == 0) ? "new level" : levelsList.value(currentLevel)->getName()), 12.0, 7.0, LEVEL_NAME, alphabet);
}

GLvoid Menu::nextLevel()
{
    if (levelsList.find(currentLevel + 1) == levelsList.end())
        currentLevel = ((gameType == ARCADE_MODE) ? 1 : 0) ;
    else
        currentLevel += 1;

    levelName->~CubeStringList();
    levelName = new CubeStringList(((currentLevel == 0) ? "new level" : levelsList.value(currentLevel)->getName()), 12.0, 7.0, LEVEL_NAME, alphabet);
}

GLvoid Menu::buttonPlayStoryTriggered()
{
    if (currentView == MAIN_VIEW)
    {
        gameType = STORY_MODE;
        isMoving = true;
        currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
    }
}

GLvoid Menu::buttonPlayArcadeTriggered()
{
    if (currentView == MAIN_VIEW)
    {
        gameType = ARCADE_MODE;
        isMoving = true;
        currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
    }
}

GLvoid Menu::buttonEditorTriggered()
{
    if (currentView == MAIN_VIEW)
    {
        currentLevel = 0;
        gameType = EDITOR_MODE;
        isMoving = true;
        currentActions->setPrimaryAction(GO_TO_LEVELS_VIEW);
    }
}

GLvoid Menu::buttonBackTriggered()
{
    if (currentView == SKINS_VIEW)
    {
        isMoving = true;
        currentActions->setPrimaryAction(GO_TO_MAIN_VIEW);
    }
    else if (currentView == LEVELS_VIEW)
    {
        if (gameType == EDITOR_MODE)
        {
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_MAIN_VIEW);
        }
        else
        {
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
        }
    }
}

GLvoid Menu::buttonNextTriggered()
{
    if (currentView == SKINS_VIEW)
    {
        if (gameType == STORY_MODE)
        {
            isMoving = true;
            currentActions->setPrimaryAction(EXIT_FROM_SKINS);
        }
        else if  (gameType == ARCADE_MODE)
        {
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_LEVELS_VIEW);

            // Evito di mostrare l'elemento "new" se la modalita' e' ARCADE (e non EDITOR)
            if (currentLevel == 0)
                nextLevel();
        }
    }
    else if (currentView == LEVELS_VIEW)
    {
        isMoving = true;
        currentActions->setPrimaryAction(EXIT_FROM_LEVELS);
    }
}

GLvoid Menu::buttonPreviousSkinTriggered()
{
    if (currentView == SKINS_VIEW)
    {
        isMoving = true;
        currentActions->setPrimaryAction(PREVIOUS_SKIN);
    }
}

GLvoid Menu::buttonNextSkinTriggered()
{
    if (currentView == SKINS_VIEW)
    {
        isMoving = true;
        currentActions->setPrimaryAction(NEXT_SKIN);
    }
}

void Menu::itemClicked(QList<GLuint> listNames)
{
    if (isMoving)
        return;

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case BUTTON_VOLUME:
            if ((GLint(angleRotVolumeCube) % 90) == 0)
            {
                audioEnabled = !audioEnabled;
                emit enableAudio(audioEnabled);
                currentActions->appendSecondaryAction(ROTATE_VOLUMECUBE);
            }
            break;

        case BUTTON_PLAY_STORY:
            buttonPlayStoryTriggered();
            break;

        case BUTTON_PLAY_ARCADE:
            buttonPlayArcadeTriggered();
            break;

        case BUTTON_LEVEL_EDITOR:
            buttonEditorTriggered();
            break;

        case BUTTON_PREVIOUS_SKIN:
            buttonPreviousSkinTriggered();
            break;

        case BUTTON_NEXT_SKIN:
            buttonNextSkinTriggered();
            break;

        case BUTTON_BACK:
            buttonBackTriggered();
            break;

        case BUTTON_NEXT:
            buttonNextTriggered();
            break;

        case BUTTON_PREVIOUS_LEVEL:
            previousLevel();
            break;

        case BUTTON_NEXT_LEVEL:
            nextLevel();
            break;
        }
    }
}

void Menu::mouseReleased(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void Menu::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{
    Q_UNUSED(event);

    if (isMoving)
        return;

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case BUTTON_PLAY_STORY:
            if (!storyButton->isRotating(listNames.at(1)))
                storyButton->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case BUTTON_PLAY_ARCADE:
            if (!arcadeButton->isRotating(listNames.at(1)))
                arcadeButton->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case BUTTON_LEVEL_EDITOR:
            if (!editorButton->isRotating(listNames.at(1)))
                editorButton->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case SKIN_NAME:
            if (!skinName->isRotating(listNames.at(1)))
                skinName->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case LEVEL_NAME:
            if (!levelName->isRotating(listNames.at(1), listNames.at(2)))
                levelName->startLetterRotation(listNames.at(1), listNames.at(2), 6, 1);
            break;
        }
    }
}

void Menu::keyPressed(QKeyEvent *event)
{
    int key = event->key();

    if ((key == Qt::Key_Escape) || (key == Qt::Key_Backspace))
    {
        buttonBackTriggered();
    }
    else if ((key == Qt::Key_Enter) || (key == Qt::Key_Return))
    {
        if (currentView == MAIN_VIEW)
            buttonPlayStoryTriggered();
        else
            buttonNextTriggered();
    }
    else if (key == Qt::Key_Left)
    {
        if (currentView == SKINS_VIEW)
            buttonPreviousSkinTriggered();
        else if (currentView == LEVELS_VIEW)
            previousLevel();
    }
    else if (key == Qt::Key_Right)
    {
        if (currentView == SKINS_VIEW)
            buttonNextSkinTriggered();
        else if (currentView == LEVELS_VIEW)
            nextLevel();
    }
    else if (key == Qt::Key_S)
    {
        if (currentView == MAIN_VIEW)
            buttonPlayStoryTriggered();
    }
    else if (key == Qt::Key_A)
    {
        if (currentView == MAIN_VIEW )
            buttonPlayArcadeTriggered();
    }
    else if (key == Qt::Key_E)
    {
        if (currentView == MAIN_VIEW)
            buttonEditorTriggered();
    }
    else if (key == Qt::Key_Shift && key == Qt::Key_Enter)
    {
        if (currentView == MAIN_VIEW )
            buttonPlayArcadeTriggered();
    }
    else if (key == Qt::Key_Shift && key == Qt::Key_Enter && key == Qt::Key_Control)
    {
        if (currentView == MAIN_VIEW )
            buttonEditorTriggered();
    }
}
