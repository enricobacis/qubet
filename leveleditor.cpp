#include "leveleditor.h"
#include "leveleditor_defines.h"

LevelEditor::LevelEditor(QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,Level*> &_levelsList,QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent):
    parent(_parent),
    levelsList(_levelsList),
    obstacleModelsList(_obstacleModelsList),
    iconsList(_iconsList),
    audioEnabled(true),
    isMoving(false),
    currentView(0),
    currentLenght(0),
    currentWidth(0),
    alphabet(_alphabet),
    volumeSkin(NULL),
    angleRotVolumeCube(0)
{
    currentActions = new ActionList(DO_NOTHING);

    currentLenght = 50;
    currentWidth = 3;
    cameraOffset = new Vector3f(0.0, 0.0, 0.0);

    lenghtDisplay = new CubeString(QString::number(currentLenght), 3, LENGHT_DISPLAY, alphabet);
    widthDisplay = new CubeString(QString::number(currentWidth), 3, WIDTH_DISPLAY, alphabet);

    lenghtLabel = new CubeString("lenght", 1.5, LENGHT_LABEL, alphabet);
    widthLabel = new CubeString("width", 1.5, WIDTH_LABEL, alphabet);

    create = new CubeString("create", 1, CREATE_BUTTON, alphabet);



    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);


    currentView = SET_PARAM_VIEW;
}

LevelEditor::~LevelEditor()
{
    if (lenghtDisplay != NULL)
        lenghtDisplay->~CubeString();

    if (widthDisplay != NULL)
        widthDisplay->~CubeString();

    if (lenghtLabel != NULL)
        lenghtLabel->~CubeString();

    if (widthLabel != NULL)
        widthLabel->~CubeString();

    parent->disconnect(this);
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
            case INITIAL_ACTION:
                currentActions->setPrimaryAction(0);
                isMoving = false;
                break;

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
    // Disegno l' editor
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

            //SET NAME VIEW DRAWING
            glPushMatrix();
            glPopMatrix();

            //SET PARAM VIEW DRAWING
            glTranslatef(8.5, -7.0, 0.0);
            create->draw(simplifyForPicking);
            glTranslatef(-8.5, 7.0, 0.0);

            glTranslatef(-6.0, 4.5, 0.0);
            lenghtLabel->draw(simplifyForPicking);

            glTranslatef(12.0, 0.0, 0.0);
            widthLabel->draw(simplifyForPicking);
            glTranslatef(-5.0, -4.5, 0.0); //return to (0.0, 0.0, 0.0)

            glPushName(BUTTON_LENGHTEN);
            glTranslatef(-7.0, 2, 1.5);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.0, 1.0,  0.0);
                glVertex3f(1.0, -1.0,  0.0);
                glVertex3f(-1.0, -1.0,  0.0);
            glEnd();
            glTranslatef(0.0, 0.0, -1.5);
            glPopName();

            glTranslatef(0.0, -3.5, 0.0);
            lenghtDisplay->draw(simplifyForPicking);

            glPushName(BUTTON_REDUCE);
            glTranslatef(7, 0.0, 1.5);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  0.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 1.0, -1.0,  0.0);
            glEnd();
            glTranslatef(0.0, 0.0, -1.5);
            glPopName();

            glTranslatef(4.5, 0.0, 0.0);
            widthDisplay->draw(simplifyForPicking);

            glPushName(BUTTON_ENLARGE);
            glTranslatef(4.5, 0.0, 1.5);
            glBegin(GL_TRIANGLES);
                glVertex3f( 1.0,  0.0,  0.0);
                glVertex3f(-1.0,  1.0,  0.0);
                glVertex3f(-1.0, -1.0,  0.0);
            glEnd();
            glTranslatef(0.0, 0.0, -1.5);
            glPopName();

            glTranslatef(-16, 0.0, 0.0);//return to (-6.0,0.0,0.0)

            glPushName(BUTTON_SHORTEN);
            glTranslatef(0.0, -3.5, 1.5);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  1.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 0.0, -1.0,  0.0);
            glEnd();
            glTranslatef(0.0, 0.0, -1.5);
            glPopName();
        glPopMatrix();
        //end of set param view
    }
}

GLvoid LevelEditor::playAudio()
{
    emit playAmbientMusic(":/music/resources/music/menu.mp3");
}

GLvoid LevelEditor::lenghten()
{
    if (currentLenght < MAX_LEVEL_LENGHT)
    {
        lenghtDisplay->~CubeString();
        currentLenght++;
        lenghtDisplay = new CubeString(QString::number(currentLenght), 3, LENGHT_DISPLAY, alphabet);
   }
}

GLvoid LevelEditor::shorten()
{
    if (currentLenght > MIN_LEVEL_LENGHT)
    {
        lenghtDisplay->~CubeString();
        currentLenght--;
        lenghtDisplay = new CubeString(QString::number(currentLenght), 3, LENGHT_DISPLAY, alphabet);
    }
}

GLvoid LevelEditor::enlarge()
{
    if (currentWidth < MAX_LEVEL_WIDTH)
    {
        widthDisplay->~CubeString();
        currentWidth++;
        widthDisplay = new CubeString(QString::number(currentWidth), 3, WIDTH_DISPLAY, alphabet);
    }
}

GLvoid LevelEditor::reduce()
{
    if (currentWidth > MIN_LEVEL_WIDTH)
    {
        widthDisplay->~CubeString();
        currentWidth--;
        widthDisplay = new CubeString(QString::number(currentWidth), 3, WIDTH_DISPLAY, alphabet);
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

         case CREATE_BUTTON:
             //newLevel(currentLenght,currentWidth);
             //editLevel(newLevel);
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

        case LENGHT_LABEL:
            if (!lenghtLabel->isRotating(listNames.at(1)))
            {
                if (listNames.at(1) % 2 == 0)
                    lenghtLabel->startLetterRotation(listNames.at(1),6,2);
                else
                    lenghtLabel->startLetterRotation(listNames.at(1),12,4);
            }
            break;

        case WIDTH_DISPLAY:
            if (!widthDisplay->isRotating(listNames.at(1)))
                widthDisplay->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case WIDTH_LABEL:
            if (!widthLabel->isRotating(listNames.at(1)))
            {
                if (listNames.at(1) % 2 == 0)
                    widthLabel->startLetterRotation(listNames.at(1),6,2);
                else
                    widthLabel->startLetterRotation(listNames.at(1),12,4);
            }
        }
    }
}

void LevelEditor::keyPressed(QKeyEvent *event)
{
    int key = event->key();

    if ((key == Qt::Key_Enter) || (key == Qt::Key_Return))
    {
    }
    else if (key == Qt::Key_Up)
    {
        if (currentView == SET_PARAM_VIEW)
            lenghten();
    }
    else if (key == Qt::Key_Down)
    {
        if (currentView == SET_PARAM_VIEW)
            shorten();
    }
    else if (key == Qt::Key_Left)
    {
        if (currentView == SET_PARAM_VIEW)
            reduce();
    }
    else if (key == Qt::Key_Right)
    {
        if (currentView == SET_PARAM_VIEW)
            enlarge();
    }
}

