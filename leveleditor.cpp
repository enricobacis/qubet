#include "leveleditor.h"
#include "defines.h"
#include "leveleditor_defines.h"
#include "effects_defines.h"

LevelEditor::LevelEditor(QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,Level*> &_levelsList,QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent):
    parent(_parent),
    levelsList(_levelsList),
    obstacleModelsList(_obstacleModelsList),
    iconsList(_iconsList),
    isMoving(false),
    currentView(0),
    currentLenght(0),
    currentWidth(0),
    alphabet(_alphabet),
    volumeSkin(NULL),
    angleRotVolumeCube(0.0f),
    visible(true),
    visibleTime(0),
    currentName("")
{
    currentActions = new ActionList(DO_NOTHING);
    cameraOffset = new Vector3f(0.0f, -30.0f, 0.0f);

    currentLenght = 50;
    currentWidth = 3;
    cameraOffset = new Vector3f(-30.0f, 0.0f, 0.0f);

    lenghtDisplay = new CubeString(QString::number(currentLenght), 3.0f, alphabet, LENGHT_DISPLAY);
    widthDisplay = new CubeString(QString::number(currentWidth), 3.0f, alphabet, WIDTH_DISPLAY);

    labelLenght = new CubeString("lenght", 1.5f, alphabet, LABEL_LENGHT);
    labelWidth = new CubeString("width", 1.5f, alphabet, LABEL_WIDTH);

    back = new CubeString("back", 1.0f, alphabet, BUTTON_BACK);
    menu = new CubeString("menu", 1.0f, alphabet, BUTTON_BACK);
    create = new CubeString("create", 1.0f, alphabet, BUTTON_NEXT);
    next = new CubeString("next", 1.0f, alphabet, BUTTON_NEXT);
    labelSetLevelName = new CubeString("set level name", 1.3f, alphabet, LABEL_SET_LEVEL_NAME);

    formSetLevelName = new CubeStringList("", 14.0f, 6.0f, alphabet, 2.0f, FORM_SET_LEVEL_NAME);
    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);

    currentView = SET_NAME_VIEW;

    audioEnabledEntry = audioEnabled;
}

LevelEditor::~LevelEditor()
{
    this->disconnect(parent);
    parent->disconnect(this);

    if (lenghtDisplay != NULL)
        lenghtDisplay->~CubeString();

    if (widthDisplay != NULL)
        widthDisplay->~CubeString();

    if (labelLenght != NULL)
        labelLenght->~CubeString();

    if (labelWidth != NULL)
        labelWidth->~CubeString();

    if (labelSetLevelName != NULL)
        labelSetLevelName->~CubeString();

    if (formSetLevelName != NULL)
        formSetLevelName->~CubeStringList();

    if (next != NULL)
        next->~CubeString();

    if (back != NULL)
        back->~CubeString();

    if (menu != NULL)
        menu->~CubeString();
}

void LevelEditor::quitEditor()
{
}

void LevelEditor::draw(GLboolean simplifyForPicking)
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
            case INITIAL_MOVEMENT:
                if (cameraOffset->y < 0.0f)
                {
                    cameraOffset->y += 2.0f;
                }
                else
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    isMoving = false;
                }

                break;

            case ROTATE_VOLUMECUBE:
                angleRotVolumeCube += 5.0f;

                if ((GLint(angleRotVolumeCube) % 360) == 0)
                    angleRotVolumeCube = 0.0f;

                if ((GLint(angleRotVolumeCube) % 90) == 0)
                    currentActions->removeSecondaryAction(ROTATE_VOLUMECUBE);

                break;

            case GO_TO_SET_NAME_VIEW:
                if(currentView == SET_PARAM_VIEW)
                {
                    cameraOffset->x --;
                    cameraAngle -= 12;
                    if(cameraOffset->x == -30)
                    {
                        currentView = SET_NAME_VIEW;
                        currentActions->setPrimaryAction(DO_NOTHING);
                        isMoving = false;
                        cameraAngle = 0;
                    }
                }
                break;

            case GO_TO_SET_PARAM_VIEW:
                if (currentView == SET_NAME_VIEW)
                {
                    cameraOffset->x ++;
                    cameraAngle+=12;
                    if (cameraOffset->x == 0)
                    {
                        currentView = SET_PARAM_VIEW;
                        currentActions->setPrimaryAction(DO_NOTHING);
                        isMoving = false;
                        cameraAngle = 0;
                    }
                }
                break;
             case GO_TO_EDITING_LEVEL_VIEW:
                cameraOffset->z ++;
                cameraAngle += 12;
                sceneAngleX ++;
                if (cameraOffset->z == 30)
                {
                    currentView = EDITING_LEVEL_VIEW;
                    currentActions->setPrimaryAction(DO_NOTHING);
                    isMoving = false;
                    cameraAngle = 0;
                }
                break;
            }
        }
    }

    // Disegno l' editor

    if (!(isMoving && simplifyForPicking))
    {
        glPushName(BUTTON_VOLUME);
        glPushMatrix();
            glTranslatef(9.5f, 6.0f, 3.0f);
            if(!audioEnabledEntry)
            {

                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            }
            glRotatef(angleRotVolumeCube, -1.0f, 0.0f, 0.0f);
            drawPrism(0.8f, 0.8f, 0.8f, volumeSkin, true);
        glPopMatrix();
        glPopName();

        glPushMatrix();

        if(currentView == EDITING_LEVEL_VIEW)
         {
             glPushName(TOOLBAR);
             glPushMatrix();
                 glTranslatef(-9.5f, 0.0f, 4.0f);
                 //drawRectangle(19.0f, 3.0f, 0.0f);
                 glTranslatef(1.0f, 5.5f, -1.0f);
                 glScalef(0.4f, 0.4f, 0.4f);
                 glPushName(OBSTACLE_0);
                    drawObstacle(0);
                 glPopName();
                 glPushName(OBSTACLE_1);
                 glTranslatef(0.0f, -7.0f, 0.0f);
                 drawObstacle(1);
                 glPopName();
                 glPushName(OBSTACLE_2);
                 glTranslatef(0.0f, -7.0f, 0.0f);
                 drawObstacle(2);
                 glPopName();
                 glPushName(OBSTACLE_3);
                 glTranslatef(0.0f, -7.0f, 0.0f);
                 drawObstacle(3);
                 glPopName();
             glPopMatrix();
             glPopName();
         }

            glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);
            glRotatef(cameraAngle, 0.0f, 0.0f, 1.0f);
            glRotatef(sceneAngleX, 1.0f, 0.0f, 0.0f);
            glRotatef(sceneAngleY, 0.0f, 1.0f, 0.0f);

            if(currentView == SET_NAME_VIEW || currentView == SET_PARAM_VIEW)
            {
                // Set Name View

                glPushMatrix();

                glTranslatef(-30.0f, 6.0f, 0.0f);
                    labelSetLevelName->draw(simplifyForPicking);

                glTranslatef(8.5f, -13.0f, 0.0f);
                    next->draw(simplifyForPicking);

                    glTranslatef(-17.0f, 0.0f, 0.0f);
                    menu->draw(simplifyForPicking);

                glTranslatef(8.5f, 6.5f, 0.0f);

                if (!simplifyForPicking)
                {
                    if (formSetLevelName->getLabel(0) == "" && visible)
                    {
                        visibleTime++;
                        drawPrism(2.0f, 2.0f, 2.0f);
                        if(visibleTime == 20)
                            visible = false;
                    }
                    else if (formSetLevelName->getLabel(0) == "" && !visible)
                    {
                        visibleTime++;
                        if(visibleTime == 33)
                        {
                            visibleTime = 0;
                            visible = true;
                        }
                    }
                    else
                    {
                        formSetLevelName->draw(simplifyForPicking);
                    }
                }

                glPopMatrix();

                // Set Parameters View

                glTranslatef(8.5f, -7.0f, 0.0f);
                create->draw(simplifyForPicking);

                glTranslatef(-18.0f, 0.0f, 0.0f);
                back->draw(simplifyForPicking);

            glTranslatef(3.5f, 11.5f, 0.0f);
                labelLenght->draw(simplifyForPicking);

                glTranslatef(12.0f, 0.0f, 0.0f);
                labelWidth->draw(simplifyForPicking);

            glTranslatef(-12.0f, -2.5f, 1.5f);
                glPushName(BUTTON_LENGHTEN);
                glBegin(GL_TRIANGLES);
                glVertex3f( 0.0f,  1.0f,  0.0f);
                glVertex3f( 1.0f, -1.0f,  0.0f);
                glVertex3f(-1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

            glTranslatef(0.0f, -3.5f, -1.5f);
                lenghtDisplay->draw(simplifyForPicking);

                glTranslatef(7.0f, 0.0f, 1.5f);
            glPushName(BUTTON_REDUCE);
                glBegin(GL_TRIANGLES);
                glVertex3f(-1.0f,  0.0f,  0.0f);
                glVertex3f( 1.0f,  1.0f,  0.0f);
                glVertex3f( 1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

            glTranslatef(4.5f, 0.0f, -1.5f);
                widthDisplay->draw(simplifyForPicking);

                glTranslatef(4.5f, 0.0f, 1.5f);
            glPushName(BUTTON_ENLARGE);
                glBegin(GL_TRIANGLES);
                glVertex3f( 1.0f,  0.0f,  0.0f);
                glVertex3f(-1.0f,  1.0f,  0.0f);
                glVertex3f(-1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

            glTranslatef(-16.0f, -3.5f, 0.0f);
                glPushName(BUTTON_SHORTEN);
                glBegin(GL_TRIANGLES);
                glVertex3f(-1.0f,  1.0f,  0.0f);
                glVertex3f( 1.0f,  1.0f,  0.0f);
                glVertex3f( 0.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

            }
            else if(currentView == EDITING_LEVEL_VIEW)
            {
                level->draw(simplifyForPicking);
                //tool bar draw
            }
            glPopMatrix();

    }
}

GLvoid LevelEditor::lenghten()
{
    if (currentLenght < MAX_LEVEL_LENGHT)
    {
        emit playEffect(EFFECT_COIN);
        lenghtDisplay->~CubeString();
        currentLenght++;
        lenghtDisplay = new CubeString(QString::number(currentLenght), 3, alphabet, LENGHT_DISPLAY);
   }
}

GLvoid LevelEditor::shorten()
{
    if (currentLenght > MIN_LEVEL_LENGHT)
    {
        emit playEffect(EFFECT_COIN);
        lenghtDisplay->~CubeString();
        currentLenght--;
        lenghtDisplay = new CubeString(QString::number(currentLenght), 3, alphabet, LENGHT_DISPLAY);
    }
}

GLvoid LevelEditor::enlarge()
{
    if (currentWidth < MAX_LEVEL_WIDTH)
    {
        emit playEffect(EFFECT_COIN);
        widthDisplay->~CubeString();
        currentWidth++;
        widthDisplay = new CubeString(QString::number(currentWidth), 3, alphabet, WIDTH_DISPLAY);
    }
}

GLvoid LevelEditor::reduce()
{
    if (currentWidth > MIN_LEVEL_WIDTH)
    {
        emit playEffect(EFFECT_COIN);
        widthDisplay->~CubeString();
        currentWidth--;
        widthDisplay = new CubeString(QString::number(currentWidth), 3, alphabet, WIDTH_DISPLAY);
    }
}

GLvoid LevelEditor::buttonBackTriggered()
{
    if (currentView == SET_PARAM_VIEW)
    {
        isMoving = true;
        emit playEffect(EFFECT_JUMPSMALL);
        currentActions->setPrimaryAction(GO_TO_SET_NAME_VIEW);
    }
}

GLvoid LevelEditor::buttonNextTriggered()
{
    if(currentView == SET_NAME_VIEW)
    {
        if(currentName != "")
        {
            if (currentName.endsWith(' '))
                currentName.chop(1);

            isMoving = true;
            emit playEffect(EFFECT_JUMPSMALL);
            currentActions->setPrimaryAction(GO_TO_SET_PARAM_VIEW);
        }
    }
    else if (currentView == SET_PARAM_VIEW)
    {
        emit playEffect(EFFECT_JUMPSMALL);
        isMoving = true;
        level = new Level(0, currentName, currentLenght, currentWidth);
        currentActions->setPrimaryAction(GO_TO_EDITING_LEVEL_VIEW);
    }
}

GLvoid LevelEditor::letterTyped(int key)
{
    if (currentView == SET_NAME_VIEW)
    {
        bool isSpace = false;

        if (key != Qt::Key_Space)
        {
            currentName += key;
        }
        else
        {
            if (currentName.endsWith(' '))
                return;

            isSpace = true;
            currentName.append(" ");
        }

        emit playEffect(EFFECT_COIN);

        if (!isSpace)
        {
            formSetLevelName->~CubeStringList();
            formSetLevelName = new CubeStringList(currentName, 14.0f, 6.0f, alphabet, 2.0f, FORM_SET_LEVEL_NAME);

            GLuint stringName = formSetLevelName->getLabelCount() - 1;
            GLuint letterName = formSetLevelName->getLabel(stringName).size() - 1;

            if (!formSetLevelName->isRotating(stringName, letterName))
                formSetLevelName->startLetterRotation(stringName, letterName, 30, 4);
        }
    }
}

void LevelEditor::itemClicked(QList<GLuint> listNames)
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

         case BUTTON_SHORTEN:
             shorten();
             break;

         case BUTTON_LENGHTEN:
             lenghten();
             break;

         case BUTTON_REDUCE:
             reduce();
             break;

         case BUTTON_ENLARGE:
             enlarge();
             break;

         case BUTTON_BACK:
             buttonBackTriggered();
             break;

         case BUTTON_NEXT:
             buttonNextTriggered();
             break;
         }
     }
}

void LevelEditor::mouseReleased(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void LevelEditor::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{
    Q_UNUSED(event);

    if (isMoving)
        return;

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case LENGHT_DISPLAY:
            if (!lenghtDisplay->isRotating(listNames.at(1)))
                lenghtDisplay->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case LABEL_LENGHT:
            if (!labelLenght->isRotating(listNames.at(1)))
            {
                if ((listNames.at(1) % 2) == 0)
                    labelLenght->startLetterRotation(listNames.at(1), 6, 2);
                else
                    labelLenght->startLetterRotation(listNames.at(1), 12, 4);
            }
            break;

        case WIDTH_DISPLAY:
            if (!widthDisplay->isRotating(listNames.at(1)))
                widthDisplay->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case LABEL_WIDTH:
            if (!labelWidth->isRotating(listNames.at(1)))
            {
                if ((listNames.at(1) % 2) == 0)
                    labelWidth->startLetterRotation(listNames.at(1), 6, 2);
                else
                    labelWidth->startLetterRotation(listNames.at(1), 12, 4);
            }
            break;

        case LABEL_SET_LEVEL_NAME:
            if (!labelSetLevelName->isRotating(listNames.at(1)))
                labelSetLevelName->startLetterRotation(listNames.at(1), 6, 1);
            break;

        }
    }
}

void LevelEditor::keyPressed(QKeyEvent *event)
{
    if (isMoving)
        return;

    int key = event->key();

    if ((key == Qt::Key_Escape) || (key == Qt::Key_Backspace))
    {
        if (key == Qt::Key_Backspace && currentView == SET_NAME_VIEW)
        {
            emit playEffect(EFFECT_JUMP);
            currentName = currentName.left(currentName.length() - 1);

            formSetLevelName->~CubeStringList();
            formSetLevelName = new CubeStringList(currentName, 14.0f, 6.0f, alphabet, 2.0f, FORM_SET_LEVEL_NAME);
        }
        else
        {
            buttonBackTriggered();
        }
    }
    else if ((key == Qt::Key_Enter) || (key == Qt::Key_Return))
    {
        buttonNextTriggered();
    }
    else if (key == Qt::Key_Up)
    {
        if (currentView == SET_PARAM_VIEW)
        {
            lenghten();
        }
        else if (currentView == EDITING_LEVEL_VIEW)
        {
            cameraOffset->z -=2;
        }
    }
    else if (key == Qt::Key_Down)
    {
        if (currentView == SET_PARAM_VIEW)
        {
            shorten();
        }
        else if (currentView == EDITING_LEVEL_VIEW)
        {
            cameraOffset->z +=2;
        }
    }
    else if (key == Qt::Key_Left)
    {
        if (currentView == SET_PARAM_VIEW)
        {
            reduce();
        }
        else if (currentView == EDITING_LEVEL_VIEW)
        {
            sceneAngleY +=2;
        }
    }
    else if (key == Qt::Key_Right)
    {
        if (currentView == SET_PARAM_VIEW)
        {
            enlarge();
        }
        else if (currentView == EDITING_LEVEL_VIEW)
        {
            sceneAngleY -=2;
        }
    }
    else if ((key >= Qt::Key_A && key <= Qt::Key_Z) || (key >= Qt::Key_0 && key <= Qt::Key_9) || key == Qt::Key_Space)
    {
        letterTyped(key);
    }
}
