#include "menu.h"

Menu::Menu(QMap<GLint,QImage*> &_skinsList, QMap<GLint,QString> &_levelsList, QObject *_parent) :
    parent(_parent),
    skinsList(_skinsList),
    levelsList(_levelsList),
    isMoving(true),
    currentStep(0),
    gameType(0),
    angleRotCube(0),
    spinCube(0),
    audioEnabled(true)
{
    cameraOffset = new Vector3f(0.0, 0.0, -10.0);

    //initialize the buttonsLettersAngle vector
    QVector<GLint> temp;
    temp << 0 << 0 << 0 << 0 << 0;
    buttonsLettersAngles << temp;
    temp << 0;
    buttonsLettersAngles << temp << temp;

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
            emit showLevelEditor();

        break;

    case 4:
        angleRotCube += 2;
        if (angleRotCube >= 360)
            angleRotCube = GLint(angleRotCube) % 360;
        break;

    case 5:
    case 6:
        spinCube++;
        angleRotCube += 2 + (spinCube <= 20 ? spinCube : 40 - spinCube);

        if (spinCube == 20)
        {
            if (currentStep == 5)
            {
                // Previous Skin
            }
            else
            {
                // Next Skin
            }
        }
        else if (spinCube == 40)
        {
            spinCube = 0;
            isMoving = false;
            currentStep = 4;
        }
        break;
    case 7:
        int j = 0;
        for(int i = 0; i < 3; i++)
        {
            switch(i)
            {
            case 0:
                j = 5;
                break;
            case 1:
            case 2:
                j = 6;
                break;
            }
            for(int t = 0; t < j; t++)
            {
                if( buttonsLettersAngles.at(i).at(t) == 360)
                    buttonsLettersAngles[i][t] = 0;
                else if( buttonsLettersAngles.at(i).at(t) != 0)
                    buttonsLettersAngles[i][t] += 6;
            }
        }
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
            drawCubesButton("story", buttonsLettersAngles.at(0), S_OF_BUTTON_PLAY_STORY);
        glPopMatrix();
        glPopName();

        glPushName(BUTTON_PLAY_ARCADE);
        drawCubesButton("arcade", buttonsLettersAngles.at(1), A_OF_BUTTON_PLAY_ARCADE);
        glPopName();

        glPushName(BUTTON_LEVEL_EDITOR);
        glPushMatrix();
            glTranslatef(0.0, -5.0, 0.0);
            drawCubesButton("editor", buttonsLettersAngles.at(2), E_OF_BUTTON_LEVEL_EDITOR);
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

void Menu::CheckLetterRotation(GLuint Name){
    if (Name < A_OF_BUTTON_PLAY_ARCADE)
    {
    GLint letterNumber = Name - S_OF_BUTTON_PLAY_STORY;
    if (buttonsLettersAngles.at(0).at(letterNumber) == 0)
        buttonsLettersAngles[0][letterNumber] += 6;
    currentStep = 7;
    }
    else if (Name < E_OF_BUTTON_LEVEL_EDITOR)
    {
        GLint letterNumber = Name - A_OF_BUTTON_PLAY_ARCADE;
        if (buttonsLettersAngles.at(1).at(letterNumber) == 0)
            buttonsLettersAngles[1][letterNumber] += 6;
        currentStep = 7;
    }
    else if (Name < E_OF_BUTTON_LEVEL_EDITOR + 6)
    {
        GLint letterNumber = Name - E_OF_BUTTON_LEVEL_EDITOR;
        if (buttonsLettersAngles.at(2).at(letterNumber) == 0)
            buttonsLettersAngles[2][letterNumber] += 6;
    }
}

void Menu::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{
    if (isMoving)
        return;
    if (!listNames.isEmpty())
    {
        if(listNames.at(1) >= S_OF_BUTTON_PLAY_STORY)
            CheckLetterRotation(listNames.at(1));
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
