#include "menu.h"

Menu::Menu(QMap<GLint,QImage*> &_skinsList, QMap<GLint,QString> &_levelsList, QObject *_parent) :
    parent(_parent),
    skinsList(_skinsList),
    levelsList(_levelsList),
    isMoving(true),
    currentStep(0),
    gameType(0),
    angleRotCube(0),
    audioEnabled(true)
{
    cameraOffset = new Vector3f(0.0, 0.0, -10.0);
}

Menu::~Menu()
{
    parent->disconnect(this);
}

GLvoid Menu::draw(GLboolean simplifyForPicking)
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
        {
            emit showLevelEditor();
        }
        break;

    case 4:
        angleRotCube += 2;
        break;
    }

    glPushName(BUTTON_VOLUME);
    glPushMatrix();
        glTranslatef(11.0, 7.0, 0.0);
        drawRectangle(1.0, 1.0);
    glPopMatrix();
    glPopName();

    glPushMatrix();
        glTranslatef(cameraOffset->x, cameraOffset->y, cameraOffset->z);

        glPushName(BUTTON_PLAY_STORY);
        glPushMatrix();
            glTranslatef(0.0, 5.0, 0.0);
            drawRectangle(8.0, 3.0);
        glPopMatrix();
        glPopName();

        glPushName(BUTTON_PLAY_ARCADE);
        drawRectangle(8.0, 3.0);
        glPopName();

        glPushName(BUTTON_LEVEL_EDITOR);
        glPushMatrix();
            glTranslatef(0.0, -5.0, 0.0);
            drawRectangle(8.0, 3.0);
        glPopMatrix();
        glPopName();

        glPushMatrix();
            glTranslatef(30.0, -4.0, 0.0);

            glPushName(SKIN_CUBE);
            glPushMatrix();
                glRotatef(angleRotCube, 0.0, -1.0, 0.0);
                drawPrism(3.0, 3.0, 3.0);
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

void Menu::itemClicked(QList<GLuint> listNames)
{
    if (isMoving)
        return;

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case BUTTON_VOLUME:
            audioEnabled = !audioEnabled;
            emit enableAudio(audioEnabled);
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
            break;

        case BUTTON_NEXT_SKIN:
            break;
        }
    }
}

void Menu::mouseReleased(QMouseEvent *event)
{

}

void Menu::mouseMoved(QMouseEvent *event)
{

}

void Menu::keyPressed(QKeyEvent *event)
{

}
