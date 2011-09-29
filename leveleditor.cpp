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
    alphabet(_alphabet),
    volumeSkin(NULL),
    angleRotVolumeCube(0),
    lenghtDisplay(NULL),
    widthDisplay(NULL)
{

    currentActions = new ActionList(INITIAL_ACTION);

    currentLenght = 10;
    currentWidth = 3;
    cameraOffset = new Vector3f(0.0, 0.0, 10.0);

    lenghtDisplay = new CubeString(QString(currentLenght), 3, LENGHT_DISPLAY, alphabet);
    widthDisplay = new CubeString(QString(currentWidth), 3, WIDTH_DISPLAY, alphabet);

    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);


}

LevelEditor::~LevelEditor()
{
    if (lenghtDisplay != NULL)
        lenghtDisplay->~CubeString();

    if (widthDisplay != NULL)
        widthDisplay->~CubeString();

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

                currentActions->setPrimaryAction(NOTHING);
                currentView = SET_PARAM_VIEW;
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

            glPushName(BUTTON_SHORTEN);
            glTranslatef(-9.0, 5.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  0.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 1.0, -1.0,  0.0);
            glEnd();
            glPopName();

            glTranslatef(9.0, 0.0, 0.0);
            lenghtDisplay->draw(simplifyForPicking);

            glPushName(BUTTON_LENGHTEN);
            glTranslatef(9.0, 0.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  0.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 1.0, -1.0,  0.0);
            glEnd();
            glPopName();

            glPushName(BUTTON_REDUCE);
            glTranslatef(-18.0, -10.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  0.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 1.0, -1.0,  0.0);
            glEnd();
            glPopName();

            glTranslatef(9.0, 0.0, 0.0);
            widthDisplay->draw(simplifyForPicking);

            glPushName(BUTTON_LENGHTEN);
            glTranslatef(9.0, 0.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex3f(-1.0,  0.0,  0.0);
                glVertex3f( 1.0,  1.0,  0.0);
                glVertex3f( 1.0, -1.0,  0.0);
            glEnd();
            glPopName();

        glPopMatrix();
    }
}

GLvoid LevelEditor::playAudio()
{
    emit playAmbientMusic(":/music/resources/music/menu.mp3");
}

GLvoid LevelEditor::lenghten()
{
    if (currentLenght != MAX_LEVEL_LENGHT)
        lenghtDisplay = new CubeString(QString(++currentLenght), 3, LENGHT_DISPLAY, alphabet);
}

GLvoid LevelEditor::shorten()
{
    if (currentLenght != MIN_LEVEL_LENGHT)
        lenghtDisplay = new CubeString(QString(--currentLenght), 3, LENGHT_DISPLAY, alphabet);
}

GLvoid LevelEditor::enlarge()
{
    if (currentLenght != MAX_LEVEL_WIDTH)
        widthDisplay = new CubeString(QString(++currentWidth), 3, LENGHT_DISPLAY, alphabet);

}

GLvoid LevelEditor::reduce()
{
    if (currentLenght != MIN_LEVEL_WIDTH)
        lenghtDisplay = new CubeString(QString(--currentWidth), 3, LENGHT_DISPLAY, alphabet);

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

        case WIDTH_DISPLAY:
            if (!widthDisplay->isRotating(listNames.at(1)))
                widthDisplay->startLetterRotation(listNames.at(1), 6, 1);
            break;
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

