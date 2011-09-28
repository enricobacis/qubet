#include "menu.h"

Menu::Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,QString> &_levelsList, QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent) :
    parent(_parent),
    currentSkin(1),
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
    currentView(0),
    storyButton(NULL),
    arcadeButton(NULL),
    editorButton(NULL),
    backButton(NULL),
    playButton(NULL),
    levelsButton(NULL),
    volumeSkin(NULL)
{
    currentActions = new ActionList(0);
    cameraOffset = new Vector3f(0.0, 0.0, +10.0);

    storyButton = new CubeString("story", 3, BUTTON_PLAY_STORY, alphabet);
    arcadeButton = new CubeString("arcade", 3, BUTTON_PLAY_ARCADE, alphabet);
    editorButton = new CubeString("editor", 3, BUTTON_LEVEL_EDITOR, alphabet);
    backButton = new CubeString("back", 1, BUTTON_BACK, alphabet);
    playButton = new CubeString("play", 1, BUTTON_NEXT, alphabet);
    levelsButton = new CubeString("levels", 1, BUTTON_NEXT, alphabet);

    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2, SKIN_NAME, alphabet);

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

    if (volumeSkin != NULL)
        volumeSkin->~Skin();

    parent->disconnect(this);
}

GLvoid Menu::draw(GLboolean simplifyForPicking)
{
    // Calcolo nuovo Frame

    if (!simplifyForPicking)
    {
        QList<int> actions = currentActions->getAllActions();

        while (!actions.isEmpty())
        {
            GLint step = actions.takeFirst();
            switch (step)
            {
            case 0:
                cameraOffset->z -= 0.5;

                if (cameraOffset->z == 0)
                {
                    currentActions->setPrimaryAction(1);
                    currentView = MAIN_VIEW;
                    isMoving = false;
                }

                break;

            case GO_TO_SKINS_VIEW:
                if (cameraOffset->x < 30)
                    cameraOffset->x += 1;
                else
                    cameraOffset->x -= 1;

                if (cameraOffset->x == 30)
                {
                    currentActions->setPrimaryAction(4);
                    currentView = 4;
                    currentView = SKINS_VIEW;
                    isMoving = false;
                }

                break;

            case GO_TO_EDITOR_VIEW:

                if (cameraOffset->x > -30)
                    cameraOffset->x -= 1;
                else
                    cameraOffset->x += 1;

                if (cameraOffset->x == -30)
                {
                    //emit showLevelEditor();
                    currentActions->setPrimaryAction(1);
                    currentView = EDITOR_VIEW;
                    isMoving = false;
                }
                break;

            case 4:
                angleRotCube += 2;

                if (angleRotCube >= 360)
                    angleRotCube = GLint(angleRotCube) % 360;

                break;

            case 5:
            case 6:
                spinCube += 2;
                angleRotCube += 2 + (spinCube <= 30 ? spinCube : 60 - spinCube);

                if (spinCube == 30)
                {
                    if (step == 5)
                        previousSkin();
                    else
                        nextSkin();
                }
                else if (spinCube == 60)
                {
                    spinCube = 0;
                    isMoving = false;
                    currentActions->setPrimaryAction(4);
                }

                break;

            case 8:
                angleRotVolumeCube += 5;

                if ((GLint(angleRotVolumeCube) % 360) == 0)
                    angleRotVolumeCube = 0;

                if ((GLint(angleRotVolumeCube) % 90) == 0)
                    currentActions->removeSecondaryAction(8);

                break;

            case GO_TO_MAIN_VIEW:

                if (cameraOffset->x < 0)
                    cameraOffset->x += 1;
                else
                    cameraOffset->x -= 1;

                if (cameraOffset->x == 0)
                {
                    currentActions->setPrimaryAction(1);
                    currentView = MAIN_VIEW;
                    isMoving = false;
                }
                break;

            case GO_TO_LEVELS_VIEW:
                cameraOffset->x += 1;

                if (cameraOffset->x == 60)
                {
                    currentActions->setPrimaryAction(1);
                    currentView = LEVELS_VIEW;
                    isMoving = false;
                }
                break;
            }
        }
    }

    // Disegno il menu
    if (!(isMoving && simplifyForPicking))
    {
        glPushName(BUTTON_VOLUME);
        glPushMatrix();
            glTranslatef(11.0, 7.0, 0.0);
            glRotatef(angleRotVolumeCube, -1.0, 0.0, 0.0);
            drawPrism(1.0, 1.0, 1.0, volumeSkin, true);
        glPopMatrix();
        glPopName();

        glPushMatrix();
            glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);
            glPushMatrix();
                glTranslatef(0.0, 5.0, 0.0);
                storyButton->draw(simplifyForPicking);
            glPopMatrix();

            arcadeButton->draw(simplifyForPicking);

            glPushMatrix();
                glTranslatef(0.0, -5.0, 0.0);
                editorButton->draw(simplifyForPicking);
            glPopMatrix();

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
                glPushMatrix();
                    glTranslatef(-5.0, 0.0, 0.0);
                    glBegin(GL_TRIANGLES);
                        glVertex3f(-1.0,  0.0,  0.0);
                        glVertex3f( 1.0,  1.0,  0.0);
                        glVertex3f( 1.0, -1.0,  0.0);
                    glEnd();
                glPopMatrix();
                glPopName();

                glPushName(BUTTON_NEXT_SKIN);
                glPushMatrix();
                    glTranslatef(5.0, 0.0, 0.0);
                    glBegin(GL_TRIANGLES);
                        glVertex3f( 1.0,  0.0,  0.0);
                        glVertex3f(-1.0,  1.0,  0.0);
                        glVertex3f(-1.0, -1.0,  0.0);
                    glEnd();
                glPopMatrix();
                glPopName();

                glPushName(BUTTON_BACK);
                glPushMatrix();
                    glTranslatef(-8.0, -4.0, 0.0);
                    backButton->draw(simplifyForPicking);
                glPopMatrix();
                glPopName();

                glPushName(BUTTON_NEXT);
                glPushMatrix();
                    glTranslatef(+8.0, -4.0, 0.0);
                    if(gameType == STORY_MODE)
                        playButton->draw(simplifyForPicking);
                    else
                        levelsButton->draw(simplifyForPicking);
                glPopMatrix();
                glPopName();

            glPopMatrix();

            glPushMatrix();
                glTranslatef(60.0, 0.0, 0.0);
                glPushName(BUTTON_BACK);
                glPushMatrix();
                    glTranslatef(-8.0, -6.0, 0.0);
                    backButton->draw(simplifyForPicking);
                glPopMatrix();
                glPopName();
            glPopMatrix();

            glPushMatrix();
                glPushName(BUTTON_BACK);
                glTranslatef(-22.0, -6.0, 0.0);
                backButton->draw(simplifyForPicking);
            glPopMatrix();
            glPopName();

        glPopMatrix();
    }
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
                currentActions->appendSecondaryAction(8);
            }
            break;

        case BUTTON_PLAY_STORY:
            gameType = STORY_MODE;
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
            break;

        case BUTTON_PLAY_ARCADE:
            gameType = ARCADE_MODE;
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
            break;

        case BUTTON_LEVEL_EDITOR:
            isMoving = true;
            currentActions->setPrimaryAction(GO_TO_EDITOR_VIEW);
            break;

        case BUTTON_PREVIOUS_SKIN:
            isMoving = true;
            currentActions->setPrimaryAction(5);
            break;

        case BUTTON_NEXT_SKIN:
            isMoving = true;
            currentActions->setPrimaryAction(6);
            break;

        case BUTTON_BACK:
            isMoving = true;
            if (currentView == SKINS_VIEW || currentView == EDITOR_VIEW)
                currentActions->setPrimaryAction(GO_TO_MAIN_VIEW);
            else
                currentActions->setPrimaryAction(GO_TO_SKINS_VIEW);
            break;

        case BUTTON_NEXT:
            if (gameType == STORY_MODE)
            {
                //emit playStory(currentSkin);
            }
            else
            {
                isMoving = true;
                currentActions->setPrimaryAction(GO_TO_LEVELS_VIEW);
            }
            break;
        }
    }
}

void Menu::mouseReleased(QMouseEvent *event)
{
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
        }
    }
}

void Menu::keyPressed(QKeyEvent *event)
{
    if (currentActions->getAllActions().contains(4))
    {
        if (event->key() == Qt::Key_Left)
        {
            isMoving = true;
            currentActions->setPrimaryAction(5);
        }
        else if (event->key() == Qt::Key_Right)
        {
            isMoving = true;
            currentActions->setPrimaryAction(6);
        }
    }
}
