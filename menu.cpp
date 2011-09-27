#include "menu.h"

Menu::Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,QString> &_levelsList, Alphabet *_alphabet, QObject *_parent) :
    parent(_parent),
    currentSkin(1),
    skinsList(_skinsList),
    levelsList(_levelsList),
    alphabet(_alphabet),
    isMoving(true),
    currentStep(0),
    gameType(0),
    angleRotCube(0),
    spinCube(0),
    angleRotVolumeCube(0),
    audioEnabled(true),
    storyButton(NULL),
    arcadeButton(NULL),
    editorButton(NULL)
{
    cameraOffset = new Vector3f(0.0, 0.0, -10.0);

    storyButton = new CubeString("story", 3, BUTTON_PLAY_STORY, alphabet);
    arcadeButton = new CubeString("arcade", 3, BUTTON_PLAY_ARCADE, alphabet);
    editorButton = new CubeString("editor", 3, BUTTON_LEVEL_EDITOR, alphabet);

    skinName = new CubeString(skinsList.value(currentSkin)->getName(), 2, SKIN_NAME, alphabet);
}

Menu::~Menu()
{
    if (storyButton != NULL)
        storyButton->~CubeString();

    if (arcadeButton != NULL)
        arcadeButton->~CubeString();

    if (editorButton != NULL)
        editorButton->~CubeString();

    parent->disconnect(this);
}

GLvoid Menu::draw(GLboolean simplifyForPicking)
{
    if (!simplifyForPicking)
    {
        switch (currentStep)
        {
        case 0:
            cameraOffset->z += 0.5;
            if (cameraOffset->z == 0)
            {
                currentStep = 1;
                isMoving = false;
            }
            break;

        case 2:
            cameraOffset->x -= 1;
            if (cameraOffset->x == -30)
            {
                currentStep = 4;
                isMoving = false;
            }
            break;

        case 3:
            cameraOffset->x += 1;
            if (cameraOffset->x == -30)
                emit showLevelEditor();

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
                if (currentStep == 5)
                    previousSkin();
                else
                    nextSkin();
            }
            else if (spinCube == 60)
            {
                spinCube = 0;
                isMoving = false;
                currentStep = 4;
            }
            break;

        case 8:
            if (angleRotVolumeCube==90)
                angleRotVolumeCube = 0;
            else if (angleRotVolumeCube !=0)
                angleRotVolumeCube += 5;
            break;
        }
    }

    glPushName(BUTTON_VOLUME);
    glPushMatrix();
        glTranslatef(11.0, 7.0, 0.0);
        glRotatef(angleRotVolumeCube, -1, 0, 0);
        drawPrism(1.0, 1.0, 1.0);
    glPopMatrix();
    glPopName();

    glPushMatrix();
        glTranslatef(cameraOffset->x, cameraOffset->y, cameraOffset->z);

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
            dynamic_cast<QGLWidget*>(parent)->renderText(-comment.length()*0.1225, -2.0, 0.0, comment);

            glTranslatef(0.0, -8.0, 0.0);

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

        glPopMatrix();

    glPopMatrix();
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
            if(angleRotVolumeCube == 0 || angleRotVolumeCube == 90)
            {
                audioEnabled = !audioEnabled;
                emit enableAudio(audioEnabled);
                angleRotVolumeCube += 5;
                currentStep = 8;
            }
            break;

        case BUTTON_PLAY_STORY:
            gameType = STORY_MODE;
            isMoving = true;
            currentStep = 2;
            break;

        case BUTTON_PLAY_ARCADE:
            gameType = ARCADE_MODE;
            isMoving = true;
            currentStep = 2;
            break;

        case BUTTON_LEVEL_EDITOR:
            isMoving = true;
            currentStep = 3;
            break;

        case BUTTON_PREVIOUS_SKIN:
            isMoving = true;
            currentStep = 5;
            break;

        case BUTTON_NEXT_SKIN:
            isMoving = true;
            currentStep = 6;
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
    if (currentStep == 4)
    {
        if (event->key() == Qt::Key_Left)
        {
            isMoving = true;
            currentStep = 5;
        }
        else if (event->key() == Qt::Key_Right)
        {
            isMoving = true;
            currentStep = 6;
        }
    }
}
