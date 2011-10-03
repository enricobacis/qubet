#include "menu.h"
#include "defines.h"
#include "menu_defines.h"
#include "effects_defines.h"

Menu::Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,Level*> &_levelsList, QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent, Skybox *_skybox) :
    parent(_parent),
    currentSkin(1),
    currentLevel(0),
    skinsList(_skinsList),
    levelsList(_levelsList),
    iconsList(_iconsList),
    skybox(_skybox),
    alphabet(_alphabet),
    isMoving(false),
    gameType(0),
    angleRotCube(0.0f),
    spinCube(0.0f),
    angleRotVolumeCube(0.0f),
    audioEnabled(true),
    volumeSkin(NULL),
    currentView(INTRODUCTION),
    currentSection(INTRO_SECTION),
    waitCounter(0),
    mainMenuButtons(NULL),
    backButton(NULL),
    playButton(NULL),
    levelsButton(NULL),
    cubeStudiosLabel(NULL),
    team34Label(NULL),
    qubetLabel(NULL)
{
    currentActions = new ActionList(CUBE_STUDIO_DISTRIBUTION);
    currentActions->appendSecondaryAction(ROTATE_SKYBOX);

    cameraOffset = new Vector3f(-90.0f, -30.0f, 18.0f);

    QList< QPair<QString,GLuint> > labelsList;
    labelsList.append(QPair<QString,GLuint>("story", BUTTON_PLAY_STORY));
    labelsList.append(QPair<QString,GLuint>("arcade", BUTTON_PLAY_ARCADE));
    labelsList.append(QPair<QString,GLuint>("editor", BUTTON_LEVEL_EDITOR));

    mainMenuButtons = new CubeStringList(labelsList, 18.0f, 12.0f, alphabet, 2.0f);

    backButton = new CubeString("back", 1.0f, alphabet, BUTTON_BACK);
    playButton = new CubeString("play", 1.0f, alphabet, BUTTON_NEXT);
    levelsButton = new CubeString("levels", 1.0f, alphabet, BUTTON_NEXT);
    editButton = new CubeString("edit", 1.0f, alphabet, BUTTON_NEXT);

    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2.0f, alphabet, SKIN_NAME);
    levelName = new CubeStringList("new level", 12.0f, 7.0f, alphabet, 2.0f, LEVEL_NAME);

    labelsList.clear();
    labelsList.append(QPair<QString,GLuint>("cube studios", 0));
    labelsList.append(QPair<QString,GLuint>("distribution", 0));
    labelsList.append(QPair<QString,GLuint>("presents", 0));

    cubeStudiosLabel = new CubeStringList(labelsList, 1.5f, alphabet);
    cubeStudiosLabel->setCurrentAngle(0.0f, -20.0f);
    cubeStudiosLabel->startStringListRotation(10.0f, 4.0f);

    labelsList.clear();
    labelsList.append(QPair<QString,GLuint>("a team 34", 0));
    labelsList.append(QPair<QString,GLuint>("project", 0));

    team34Label = new CubeStringList(labelsList, 1.5f, alphabet);
    team34Label->setCurrentAngle(0.0f, -20.0f);

    qubetLabel = new CubeString("qubet", 3.0f, alphabet);
    qubetLabel->setCurrentAngle(0.0f, -20.0f);

    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);
}

Menu::~Menu()
{
    this->disconnect(parent);
    parent->disconnect(this);

    if (mainMenuButtons != NULL)
        mainMenuButtons->~CubeStringList();

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

    if (cubeStudiosLabel != NULL)
        cubeStudiosLabel->~CubeStringList();

    if (team34Label != NULL)
        team34Label->~CubeStringList();

    if (qubetLabel != NULL)
        qubetLabel->~CubeString();

    if (volumeSkin != NULL)
        volumeSkin->~Skin();
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
            case CUBE_STUDIO_DISTRIBUTION:
                cameraOffset->z -= 1.0f;

                if (cameraOffset->z == 0.0f)
                {
                    waitCounter = 100;
                    currentActions->setPrimaryAction(TEAM_34_PROJECT);
                }

                break;

            case TEAM_34_PROJECT:
                if (waitCounter != 0)
                {
                    waitCounter--;

                    if (waitCounter == 0)
                        team34Label->startStringListRotation(10.0f, 4.0f);
                }
                else
                {
                    cameraOffset->x += 1;

                    if (cameraOffset->x == -60.0f)
                    {
                        waitCounter = 80;
                        currentActions->setPrimaryAction(QUBET);
                    }
                }

                break;

            case QUBET:
                if (waitCounter != 0)
                {
                    waitCounter--;

                    if (waitCounter == 0)
                        qubetLabel->startStringRotation(10.0f, 8.0f);
                }
                else
                {
                    cameraOffset->y += 1.0f;

                    if (cameraOffset->y == 0.0f)
                    {
                        waitCounter = 120;
                        currentActions->setPrimaryAction(GO_TO_MAIN_VIEW);
                    }
                }

                break;

            case GO_TO_MAIN_VIEW:
                if (waitCounter != 0)
                {
                    waitCounter--;
                }
                else
                {
                    if (currentView == INTRODUCTION)
                    {
                        cameraOffset->x += 2.0f;

                        if (cameraOffset->x == -30.0f)
                        {
                            currentSection = MENU_SECTION;
                            emit setMouseMovementTracking(MOUSE_MOVED_FULL);
                        }
                    }
                    else if (gameType == EDITOR_MODE)
                    {
                        cameraOffset->x -= 0.5f;
                        cameraOffset->y -= 1.0f;
                    }
                    else
                    {
                        cameraOffset->x -= 1.0f;
                    }

                    if(cameraOffset->x == 0.0f)
                    {
                        currentActions->setPrimaryAction(DO_NOTHING);
                        currentView = MAIN_VIEW;
                        isMoving = false;
                    }
                }
                break;

            case GO_TO_SKINS_VIEW:
                if (currentView == LEVELS_VIEW)
                {
                    cameraOffset->x += 0.5f;
                    cameraOffset->y -= 1.0f;
                }
                else
                {
                    cameraOffset->x += 1.0f;
                }
                if (cameraOffset->x == 30.0f)
                {
                    currentActions->setPrimaryAction(ROTATE_SKINCUBE);
                    currentView = SKINS_VIEW;
                    isMoving = false;
                }

                break;

            case GO_TO_LEVELS_VIEW:
                if (currentView == MAIN_VIEW)
                {
                   cameraOffset->x += 0.5f;
                   cameraOffset->y += 1.0f;
                }
                else
                {
                    cameraOffset->x -= 0.5f;
                    cameraOffset->y += 1.0f;
                }
                if (cameraOffset->x == 15.0f)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    currentView = LEVELS_VIEW;
                    isMoving = false;
                }
                break;

            case ROTATE_SKINCUBE:
                angleRotCube += 2.0f;

                if (angleRotCube >= 360.0f)
                    angleRotCube = GLint(angleRotCube) % 360;

                break;

            case PREVIOUS_SKIN:
            case NEXT_SKIN:
                spinCube += 2.0f;
                angleRotCube += 2.0f + (spinCube <= 30.0f ? spinCube : 60.0f - spinCube);

                if (spinCube == 30.0f)
                {
                    if (step == PREVIOUS_SKIN)
                        previousSkin();
                    else
                        nextSkin();
                }
                else if (spinCube == 60.0f)
                {
                    spinCube = 0.0f;
                    isMoving = false;
                    currentActions->setPrimaryAction(ROTATE_SKINCUBE);
                }

                break;

            case EXIT_FROM_LEVELS:
                cameraOffset->y += 2.0f;
                if (cameraOffset->y == 90.0f)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);

                    if (gameType == ARCADE_MODE)
                    {
                        emit playArcade(currentSkin, currentLevel);
                        return;
                    }
                    else if (gameType == EDITOR_MODE)
                    {
                        emit showLevelEditor();
                        return;
                    }
                }
                break;

            case EXIT_FROM_SKINS:
                cameraOffset->x += 2.0f;
                if (cameraOffset->x == 90.0f)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    emit playStory(currentSkin);
                    return;
                }

                break;

            // Secondary Actions

            case ROTATE_VOLUMECUBE:
                angleRotVolumeCube += 5.0f;

                if ((GLint(angleRotVolumeCube) % 360) == 0)
                    angleRotVolumeCube = 0.0f;

                if ((GLint(angleRotVolumeCube) % 90) == 0)
                    currentActions->removeSecondaryAction(ROTATE_VOLUMECUBE);

                break;

            case ROTATE_SKYBOX:
                skyboxAngle += 0.1f;

                if (skyboxAngle >= 360.0f)
                    skyboxAngle -= 360.0f;

                break;
            }
        }
    }

    // Disegno il menu

    if (!(isMoving && simplifyForPicking))
    {
        glPushName(BUTTON_VOLUME);
        glPushMatrix();
            glTranslatef(9.5f, 6.0f, 3.0f);
            glRotatef(angleRotVolumeCube, -1.0f, 0.0f, 0.0f);
            drawPrism(0.8f, 0.8f, 0.8f, volumeSkin, true);
        glPopMatrix();
        glPopName();

        if (!simplifyForPicking && (skybox != NULL))
        {
            glPushMatrix();
                glRotatef(skyboxAngle, 0.0f, 1.0f, 0.0f);
                skybox->draw();
            glPopMatrix();
        }

        glPushMatrix();

            glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);

            switch (currentSection)
            {
            case INTRO_SECTION:
                glTranslatef(-90.0f, -30.0f, 0.0f);
                cubeStudiosLabel->draw(simplifyForPicking);

                glTranslatef(30.0f, 0.0f, 0.0f);
                team34Label->draw(simplifyForPicking);

                glTranslatef(0.0f, 30.0f, 0.0f);
                qubetLabel->draw(simplifyForPicking);

                break;

            case MENU_SECTION:

                glPushMatrix();

                    mainMenuButtons->draw(simplifyForPicking);
                    glTranslatef(30.0f, 4.0f, 0.0f);

                    skinName->draw(simplifyForPicking);
                    QString comment = skinsList.value(currentSkin)->getComment();
                    dynamic_cast<QGLWidget*>(parent)->renderText(-comment.length()*0.1225f, -2.5f, 0.0f, comment);

                    glTranslatef(0.0f, -6.0f, 0.0f);

                    glPushName(SKIN_CUBE);
                    glPushMatrix();
                        glRotatef(angleRotCube, 0.0f, -1.0f, 0.0f);
                        drawPrism(3.0f, 3.0f, 3.0f, skinsList.value(currentSkin));
                    glPopMatrix();
                    glPopName();

                    glPushName(BUTTON_PREVIOUS_SKIN);
                    glTranslatef(-5.0f, 0.0f, 0.0f);
                    glBegin(GL_TRIANGLES);
                        glVertex3f(-1.0f,  0.0f,  0.0f);
                        glVertex3f( 1.0f,  1.0f,  0.0f);
                        glVertex3f( 1.0f, -1.0f,  0.0f);
                    glEnd();
                    glPopName();

                    glTranslatef(-3.0f, -4.0f, 0.0f);
                    backButton->draw(simplifyForPicking);
                    glPopName();

                    glPushName(BUTTON_NEXT_SKIN);
                    glTranslatef(13.0f, 4.0f, 0.0f);
                    glBegin(GL_TRIANGLES);
                        glVertex3f( 1.0f,  0.0f,  0.0f);
                        glVertex3f(-1.0f,  1.0f,  0.0f);
                        glVertex3f(-1.0f, -1.0f,  0.0f);
                    glEnd();
                    glPopName();

                    glTranslatef(3.0f, -4.0f, 0.0f);
                    if(gameType == STORY_MODE)
                        playButton->draw(simplifyForPicking);
                    else
                        levelsButton->draw(simplifyForPicking);

                glPopMatrix();

                glPushMatrix();
                    glTranslatef(15.0f, 31.0f, 0.0f);

                    levelName->draw(simplifyForPicking);

                    glPushName(BUTTON_PREVIOUS_LEVEL);
                    glTranslatef(-9.0f, 0.0f, 0.0f);
                    glBegin(GL_TRIANGLES);
                        glVertex3f(-1.0f,  0.0f,  0.0f);
                        glVertex3f( 1.0f,  1.0f,  0.0f);
                        glVertex3f( 1.0f, -1.0f,  0.0f);
                    glEnd();
                    glPopName();

                    glTranslatef(1.0f, -7.0f, 0.0f);
                    backButton->draw(simplifyForPicking);

                    glPushName(BUTTON_NEXT_LEVEL);
                    glTranslatef(17.0f, 7.0f, 0.0f);
                    glBegin(GL_TRIANGLES);
                        glVertex3f( 1.0f,  0.0f,  0.0f);
                        glVertex3f(-1.0f,  1.0f,  0.0f);
                        glVertex3f(-1.0f, -1.0f,  0.0f);
                    glEnd();
                    glPopName();

                    glTranslatef(-1.0f, -7.0f, 0.0f);
                    if (gameType == ARCADE_MODE)
                        playButton->draw(simplifyForPicking);
                    else if (gameType == EDITOR_MODE)
                        editButton->draw(simplifyForPicking);

                glPopMatrix();

                break;
            }

        glPopMatrix();
    }
}

GLvoid Menu::previousSkin()
{
    if (currentSkin == 1)
        currentSkin = skinsList.count();
    else
        currentSkin -= 1;

    skinName->~CubeString();
    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2.0f, alphabet, SKIN_NAME);
    emit playEffect(EFFECT_JUMPSMALL);
}

GLvoid Menu::nextSkin()
{
    if (skinsList.find(currentSkin + 1) == skinsList.end())
        currentSkin = 1;
    else
        currentSkin += 1;

    skinName->~CubeString();
    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2.0f, alphabet, SKIN_NAME);
    emit playEffect(EFFECT_JUMPSMALL);
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
    levelName = new CubeStringList(((currentLevel == 0) ? "new level" : levelsList.value(currentLevel)->getName()), 12.0f, 7.0f, alphabet, 2.0f, LEVEL_NAME);
    emit playEffect(EFFECT_JUMP);
}

GLvoid Menu::nextLevel()
{
    if (levelsList.find(currentLevel + 1) == levelsList.end())
        currentLevel = ((gameType == ARCADE_MODE) ? 1 : 0) ;
    else
        currentLevel += 1;

    levelName->~CubeStringList();
    levelName = new CubeStringList(((currentLevel == 0) ? "new level" : levelsList.value(currentLevel)->getName()), 12.0f, 7.0f, alphabet, 2.0f, LEVEL_NAME);
    emit playEffect(EFFECT_JUMP);
}

GLvoid Menu::buttonPlayStoryTriggered()
{
    if (currentView == MAIN_VIEW)
    {
        gameType = STORY_MODE;
        isMoving = true;
        emit playEffect(EFFECT_JUMP);
        currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
    }
}

GLvoid Menu::buttonPlayArcadeTriggered()
{
    if (currentView == MAIN_VIEW)
    {
        gameType = ARCADE_MODE;
        isMoving = true;
        emit playEffect(EFFECT_JUMP);
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
        emit playEffect(EFFECT_JUMP);
        currentActions->setPrimaryAction(GO_TO_LEVELS_VIEW);
    }
}

GLvoid Menu::buttonBackTriggered()
{
    if (currentView == SKINS_VIEW)
    {
        isMoving = true;
        emit playEffect(EFFECT_JUMP);
        currentActions->setPrimaryAction(GO_TO_MAIN_VIEW);
    }
    else if (currentView == LEVELS_VIEW)
    {
        emit playEffect(EFFECT_JUMP);

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
            emit playEffect(EFFECT_COIN);
            emit stopAmbientMusic();
            currentActions->setPrimaryAction(EXIT_FROM_SKINS);
        }
        else if  (gameType == ARCADE_MODE)
        {
            isMoving = true;
            emit playEffect(EFFECT_JUMP);
            currentActions->setPrimaryAction(GO_TO_LEVELS_VIEW);

            // Evito di mostrare l'elemento "new" se la modalita' e' ARCADE (e non EDITOR)
            if (currentLevel == 0)
                nextLevel();
        }
    }
    else if (currentView == LEVELS_VIEW)
    {
        isMoving = true;

        if (gameType == ARCADE_MODE)
            emit playEffect(EFFECT_COIN);
        else
            emit playEffect(EFFECT_STOMP);

        emit stopAmbientMusic();
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
        case BUTTON_PLAY_ARCADE:
        case BUTTON_LEVEL_EDITOR:
            if (!mainMenuButtons->isRotating(listNames.at(0), listNames.at(1)))
                mainMenuButtons->startLetterRotation(listNames.at(0), listNames.at(1), 6, 1);
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
    if (isMoving)
        return;

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
