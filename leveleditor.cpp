#include "leveleditor.h"
#include "defines.h"
#include "leveleditor_defines.h"
#include "effects_defines.h"

LevelEditor::LevelEditor(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *_parent, Level *_level, bool _audioEnabled, Skybox *_skybox):
    parent(_parent),
    iconsList(_iconsList),
    skybox(_skybox),
    skyboxAngle(0.0f),
    audioEnabled(_audioEnabled),
    isMoving(false),
    level(_level),
    currentView(SET_NAME_VIEW),
    currentLength(LEVEL_LENGTH_DEFAULT),
    currentWidth(LEVEL_WIDTH_DEFAULT),
    currentGravity(LEVEL_GRAVITY_DEFAULT),
    alphabet(_alphabet),
    volumeSkin(NULL),
    visible(true),
    visibleTime(0),
    currentName(""),
    disableVector(QVector<GLfloat>(4)),
    enableVector(QVector<GLfloat>(4)),
    movingObject(-1),
    redEmission(QVector<GLfloat>(4)),
    greenEmission(QVector<GLfloat>(4)),
    positionValid(false),
    xCell(0),
    yCell(0),
    zCell(0),
    lastMouseX(0),
    lastMouseY(0)
{
    currentActions = new ActionList(INITIAL_MOVEMENT);
    currentActions->appendSecondaryAction(ROTATE_SKYBOX);

    cameraOffset = new Vector3f(-30.0f, -30.0f, 0.0f);
    levelOffset  = new Vector3f(0.0f, -3.0f, 0.0f);

    if (level != NULL)
    {
        // Carica il livello
        level->load();
        currentGravity = level->getGravity();
        currentLength = level->getLength();
        currentWidth = level->getWidth();

        cameraOffset->x = 30.0f;
        currentView = SET_GRAVITY_VIEW;
    }

    angleRotVolumeCube = (audioEnabled ? 0.0f : 90.0f);

    disableVector.fill(0.0f, 3);
    disableVector.append(1.0f);

    enableVector.fill(1.0f, 4);

    redEmission[0] = 1.0f;
    redEmission[1] = 0.0f;
    redEmission[2] = 0.0f;
    redEmission[3] = 1.0f;

    greenEmission[0] = 0.0f;
    greenEmission[1] = 1.0f;
    greenEmission[2] = 0.0f;
    greenEmission[3] = 1.0f;

    lengthLabel = new CubeString(QString::number(currentLength / 3), 3.0f, alphabet, LENGTH_LABEL);
    widthLabel = new CubeString(QString::number(currentWidth / 3), 3.0f, alphabet, WIDTH_LABEL);
    gravityLabel = new CubeString(QString::number(currentGravity), 3.0f, alphabet, GRAVITY_LABEL);

    lengthString = new CubeString("length", 1.5f, alphabet, LENGTH_STRING);
    widthString = new CubeString("width", 1.5f, alphabet, WIDTH_STRING);
    gravityString = new CubeString("gravity", 1.5f, alphabet, GRAVITY_STRING);

    back = new CubeString("back", 1.0f, alphabet, BUTTON_BACK);
    menu = new CubeString("menu", 1.0f, alphabet, BUTTON_BACK);
    create = new CubeString("create", 1.0f, alphabet, BUTTON_NEXT);
    next = new CubeString("next", 1.0f, alphabet, BUTTON_NEXT);
    save = new CubeString("save", 0.8f, alphabet, BUTTON_SAVE);
    cancel = new CubeString("cancel", 0.8f, alphabet, BUTTON_CANCEL);
    clear = new CubeString("clear", 0.8f, alphabet, BUTTON_CLEAR);

    labelSetLevelName = new CubeString("set level name", 1.3f, alphabet, LABEL_SET_LEVEL_NAME);

    formSetLevelName = new CubeStringList("", 14.0f, 6.0f, alphabet, 2.0f, FORM_SET_LEVEL_NAME);
    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);

    toolbarObstacleCentres.append(new Vector3f(80.0f,  6.0f, 0.0f));
    toolbarObstacleCentres.append(new Vector3f(80.0f,  3.2f, 0.0f));
    toolbarObstacleCentres.append(new Vector3f(80.0f,  0.4f, 0.0f));
    toolbarObstacleCentres.append(new Vector3f(80.0f, -2.4f, 0.0f));
}

LevelEditor::~LevelEditor()
{
    if (lengthLabel != NULL)
        lengthLabel->~CubeString();

    if (widthLabel != NULL)
        widthLabel->~CubeString();

    if (lengthString != NULL)
        lengthString->~CubeString();

    if (widthString != NULL)
        widthString->~CubeString();

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

    this->disconnect(parent);
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

            case GO_TO_SET_NAME_VIEW:
                if(currentView == SET_PARAM_VIEW)
                {
                    cameraOffset->x -= 0.5f;
                    cameraAngle -= 6.0f;
                    if(cameraOffset->x == -30.0f)
                    {
                        currentView = SET_NAME_VIEW;
                        currentActions->setPrimaryAction(DO_NOTHING);
                        isMoving = false;
                        cameraAngle = 0.0f;
                    }
                }

                break;

            case GO_TO_SET_PARAM_VIEW:
                if (currentView == SET_NAME_VIEW)
                {
                    cameraOffset->x += 0.5f;
                    cameraAngle += 6.0f;

                    if (cameraOffset->x == 0.0f)
                    {
                        currentView = SET_PARAM_VIEW;
                        currentActions->setPrimaryAction(DO_NOTHING);
                        isMoving = false;
                        cameraAngle = 0.0f;
                    }
                }
                else if (currentView == SET_GRAVITY_VIEW)
                {
                    cameraOffset->x -= 0.5f;
                    cameraAngle -= 6.0f;

                    if (cameraOffset->x == 0.0f)
                    {
                        currentView = SET_PARAM_VIEW;
                        currentActions->setPrimaryAction(DO_NOTHING);
                        isMoving = false;
                        cameraAngle = 0.0f;
                    }
                }

                break;

            case GO_TO_SET_GRAVITY_VIEW:
                cameraOffset->x += 0.5f;
                cameraAngle += 6.0f;

                if (cameraOffset->x == 30.0f)
                {
                    currentView = SET_GRAVITY_VIEW;
                    currentActions->setPrimaryAction(DO_NOTHING);
                    isMoving = false;
                    cameraAngle = 0.0f;
                }

                break;

             case GO_TO_EDITING_LEVEL_VIEW:
                cameraOffset->x += 2.0f;

                if (cameraOffset->x == 60.0f)
                {
                    currentView = EDITING_LEVEL_VIEW;
                    emit setMouseMovementTracking(MOUSE_MOVED_DOWN);
                }
                else if (cameraOffset->x == 90.0f)
                {
                    currentActions->setPrimaryAction(DO_NOTHING);
                    isMoving = false;
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

    // Disegno l' editor

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

        glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);
        glRotatef(cameraAngle, 0.0f, 0.0f, 1.0f);

        glPushMatrix();

        if(currentView == EDITING_LEVEL_VIEW)
        {
            glPushMatrix();

                glTranslatef(90.0f, 0.0f, 0.0f);

                glPushMatrix();
                    glTranslatef(7.0f, 4.0f, 3.0f);
                    save->draw(simplifyForPicking);
                    glTranslatef(0.0f, -1.5f, 0.0f);
                    cancel->draw(simplifyForPicking);
                    glTranslatef(0.0f, -1.5f, 0.0f);
                    clear->draw(simplifyForPicking);
                glPopMatrix();

                glPushMatrix();

                    glTranslatef(levelOffset->x, levelOffset->y, levelOffset->z);
                    glScalef(0.4f, 0.4f, 0.4f);
                    level->draw(simplifyForPicking);

                glPopMatrix();

                glScalef(0.4f, 0.4f, 0.4f);
                glTranslatef(-25.0f, 15.0f, 0.0f);

                glPushMatrix();
                if (movingObject == 0)
                {
                    glTranslatef(currentDelta.x, currentDelta.y, currentDelta.z);
                    setColorEmissive(positionValid ? COLOR_GREEN : COLOR_RED);
                }
                else
                {
                    setColorEmissive(COLOR_DISABLED);
                }

                glPushName(OBSTACLE_0);
                drawObstacle(0);
                glPopName();
                glPopMatrix();

                glTranslatef(0.0f, -7.0f, 0.0f);

                glPushMatrix();
                if (movingObject == 1)
                {
                    glTranslatef(currentDelta.x, currentDelta.y, currentDelta.z);
                    setColorEmissive(positionValid ? COLOR_GREEN : COLOR_RED);
                }
                else
                {
                    setColorEmissive(COLOR_DISABLED);
                }

                glPushName(OBSTACLE_1);
                drawObstacle(1);
                glPopName();
                glPopMatrix();

                if (currentWidth >= 6)
                {
                    glTranslatef(0.0f, -7.0f, 0.0f);

                    glPushMatrix();
                    if (movingObject == 2)
                    {
                        glTranslatef(currentDelta.x, currentDelta.y, currentDelta.z);
                        setColorEmissive(positionValid ? COLOR_GREEN : COLOR_RED);
                    }
                    else
                    {
                        setColorEmissive(COLOR_DISABLED);
                    }

                    glPushName(OBSTACLE_2);
                    drawObstacle(2);
                    glPopName();
                    glPopMatrix();

                    glTranslatef(0.0f, -7.0f, 0.0f);

                    glPushMatrix();
                    if (movingObject == 3)
                    {
                        glTranslatef(currentDelta.x, currentDelta.y, currentDelta.z);
                        setColorEmissive(positionValid ? COLOR_GREEN : COLOR_RED);
                    }
                    else
                    {
                        setColorEmissive(COLOR_DISABLED);
                    }

                    glPushName(OBSTACLE_3);
                    drawObstacle(3);
                    glPopName();
                    glPopMatrix();
                }

            glPopMatrix();
            setColorEmissive(COLOR_DISABLED);
        }
        else
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

            glPushMatrix();

                glTranslatef(9.0f, -7.0f, 0.0f);
                next->draw(simplifyForPicking);

                glTranslatef(-18.5f, 0.0f, 0.0f);
                back->draw(simplifyForPicking);

                glTranslatef(3.5f, 11.5f, 0.0f);
                lengthString->draw(simplifyForPicking);

                glTranslatef(12.0f, 0.0f, 0.0f);
                widthString->draw(simplifyForPicking);

                glTranslatef(-12.0f, -2.5f, 1.5f);
                glPushName(BUTTON_LENGTHEN);
                glBegin(GL_TRIANGLES);
                    glVertex3f( 0.0f,  1.0f,  0.0f);
                    glVertex3f( 1.0f, -1.0f,  0.0f);
                    glVertex3f(-1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

                glTranslatef(0.0f, -3.5f, -1.5f);
                lengthLabel->draw(simplifyForPicking);

                glTranslatef(7.0f, 0.0f, 1.5f);
                glPushName(BUTTON_REDUCE);
                glBegin(GL_TRIANGLES);
                    glVertex3f(-1.0f,  0.0f,  0.0f);
                    glVertex3f( 1.0f,  1.0f,  0.0f);
                    glVertex3f( 1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

                glTranslatef(4.5f, 0.0f, -1.5f);
                widthLabel->draw(simplifyForPicking);

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

            glPopMatrix();

            // Set Gravity

            glPushMatrix();

                glTranslatef(30.0f, 4.0f, 0.0f);
                gravityString->draw(simplifyForPicking);

                glTranslatef(0.0f, -4.0f, 0.0f);
                gravityLabel->draw(simplifyForPicking);

                glTranslatef(+6.0f, 0.0f, 0.0f);
                glPushName(BUTTON_GRAVITY_PLUS);
                glBegin(GL_TRIANGLES);
                    glVertex3f( 1.0f,  0.0f,  0.0f);
                    glVertex3f(-1.0f,  1.0f,  0.0f);
                    glVertex3f(-1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

                glTranslatef(-12.0f, 0.0f, 0.0f);
                glPushName(BUTTON_GRAVITY_MINUS);
                glBegin(GL_TRIANGLES);
                    glVertex3f(-1.0f,  0.0f,  0.0f);
                    glVertex3f( 1.0f,  1.0f,  0.0f);
                    glVertex3f( 1.0f, -1.0f,  0.0f);
                glEnd();
                glPopName();

                glTranslatef(-2.0f, -7.0f, 0.0f);

                if (level == NULL)
                    back->draw(simplifyForPicking);

                glTranslatef(15.0f, -0.0f, 0.0f);
                create->draw(simplifyForPicking);

            glPopMatrix();

        }
        glPopMatrix();
    }
}

GLvoid LevelEditor::lengthen()
{
    if (currentLength + 3 <= MAX_LEVEL_LENGTH)
    {
        emit playEffect(EFFECT_COIN);
        lengthLabel->~CubeString();
        currentLength += 3;
        lengthLabel = new CubeString(QString::number(currentLength / 3), 3, alphabet, LENGTH_LABEL);
   }
}

GLvoid LevelEditor::shorten()
{
    if (currentLength - 3 >= MIN_LEVEL_LENGTH)
    {
        emit playEffect(EFFECT_COIN);
        lengthLabel->~CubeString();
        currentLength -= 3;
        lengthLabel = new CubeString(QString::number(currentLength / 3), 3, alphabet, LENGTH_LABEL);
    }
}

GLvoid LevelEditor::enlarge()
{
    if (currentWidth + 3 <= MAX_LEVEL_WIDTH)
    {
        emit playEffect(EFFECT_COIN);
        widthLabel->~CubeString();
        currentWidth += 3;
        widthLabel = new CubeString(QString::number(currentWidth / 3), 3, alphabet, WIDTH_LABEL);
    }
}

GLvoid LevelEditor::reduce()
{
    if (currentWidth - 3 >= MIN_LEVEL_WIDTH)
    {
        emit playEffect(EFFECT_COIN);
        widthLabel->~CubeString();
        currentWidth -= 3;
        widthLabel = new CubeString(QString::number(currentWidth / 3), 3, alphabet, WIDTH_LABEL);
    }
}

GLvoid LevelEditor::gravityMinus()
{
    if (currentGravity > MIN_GRAVITY)
    {
        emit playEffect(EFFECT_COIN);
        gravityLabel->~CubeString();
        currentGravity--;
        gravityLabel = new CubeString(QString::number(currentGravity), 3, alphabet, GRAVITY_LABEL);
    }
}

GLvoid LevelEditor::gravityPlus()
{
    if (currentGravity < MAX_GRAVITY)
    {
        emit playEffect(EFFECT_COIN);
        gravityLabel->~CubeString();
        currentGravity++;
        gravityLabel = new CubeString(QString::number(currentGravity), 3, alphabet, GRAVITY_LABEL);
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
    else if (currentView == SET_GRAVITY_VIEW)
    {
        if (level == NULL)
        {
            isMoving = true;
            emit playEffect(EFFECT_JUMPSMALL);
            currentActions->setPrimaryAction(GO_TO_SET_PARAM_VIEW);
        }
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

            currentName = currentName.toLower();

            isMoving = true;
            emit playEffect(EFFECT_JUMPSMALL);
            currentActions->setPrimaryAction(GO_TO_SET_PARAM_VIEW);
        }
    }
    else if (currentView == SET_PARAM_VIEW)
    {
        isMoving = true;
        emit playEffect(EFFECT_JUMPSMALL);
        currentActions->setPrimaryAction(GO_TO_SET_GRAVITY_VIEW);
    }
    else if (currentView == SET_GRAVITY_VIEW)
    {
        emit playEffect(EFFECT_JUMPSMALL);
        isMoving = true;

        if (level == NULL)
            level = new Level(currentName, currentLength, currentWidth, this);

        level->setGravity(currentGravity);

        levelOffset->z -= ((currentLength * 0.4f) / 2.0f) - 10.0f;
        currentActions->setPrimaryAction(GO_TO_EDITING_LEVEL_VIEW);
    }
    else
    {
        saveLevel();
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

GLvoid LevelEditor::setColorEmissive(int color)
{
    switch (color)
    {
    case COLOR_DISABLED:
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  enableVector.data());
        glMaterialfv(GL_FRONT, GL_SPECULAR, enableVector.data());
        glMaterialfv(GL_FRONT, GL_EMISSION, disableVector.data());
        break;

    case COLOR_RED:
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  redEmission.data());
        glMaterialfv(GL_FRONT, GL_SPECULAR, redEmission.data());
        glMaterialfv(GL_FRONT, GL_EMISSION, redEmission.data());
        break;

    case COLOR_GREEN:
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  greenEmission.data());
        glMaterialfv(GL_FRONT, GL_SPECULAR, greenEmission.data());
        glMaterialfv(GL_FRONT, GL_EMISSION, greenEmission.data());
        break;
    }
}

GLvoid LevelEditor::checkMousePosition(GLint x, GLint y)
{
    if (movingObject != -1)
    {
        Vector3f* P0 = new Vector3f(x, y, 0);
        Vector3f* P1 = new Vector3f(x, y, 1);

        Vector3f* M0 = getModelViewPos(P0, false);
        Vector3f* M1 = getModelViewPos(P1, false);

        // Calcolo del punto sul piano
        GLfloat t = (levelOffset->y + (LEVEL_HEIGHT/2.0f) - M0->y)/(M1->y - M0->y);
        Vector3f *newPos = getPointFromParametricLine(M0, M1, t);

        // Se non e' sul piano uso l'altra parametrizzazione
        if (  (newPos->x < (90.0f - (currentWidth * 0.4f)/2.0f))
           || (newPos->x > (90.0f + (currentWidth * 0.4f)/2.0f))
           || (newPos->z >  20.0f)
           || (newPos->z > levelOffset->z + (currentLength * 0.4f)/2.0f)
           || (newPos->z < levelOffset->z - (currentLength * 0.4f)/2.0f))
        {
            t = (lastCentre.z + deltaFromCentre.z - M0->z)/(M1->z - M0->z);
            newPos = getPointFromParametricLine(M0, M1, t);
            currentDelta = *newPos - lastCentre - deltaFromCentre;
            currentDelta = currentDelta * 2.5f;
            positionValid = false;
        }
        else
        {
            xCell = floor((((newPos->x - 90.f) / 0.4f) + currentWidth / 2.0f) / 3.0f);
            zCell = floor((-(newPos->z - levelOffset->z) / 0.4f + currentLength / 2.0f) / 3.0f);

            int x_cellMax = floor(currentWidth / 3.0f) - ((movingObject == 0) || (movingObject == 1) ? 1 : 2);
            xCell = qMin(xCell, x_cellMax);

            Vector3f *bounding = getObstacleBoundingBox(movingObject);

            Vector3f *newCentre = new Vector3f();
            newCentre->x = ((bounding->x / 2.0f) + (xCell * 3.0f) - (currentWidth / 2.0f)) * 0.4f + 90.0f;
            newCentre->y = ((bounding->y / 2.0f) + (LEVEL_HEIGHT / 2.0f)) * 0.4f + levelOffset->y;
            newCentre->z = -((bounding->z / 2.0f) + (zCell * 3.0f) - (currentLength / 2.0f)) * 0.4f + levelOffset->z;

            currentDelta = *newCentre - lastCentre;
            currentDelta = currentDelta * 2.5f;

            positionValid = true;
        }
    }
}

GLvoid LevelEditor::moveIn()
{
    if (levelOffset->z <= ((currentLength * 0.4f) / 2.0f) + 10.0f)
        levelOffset->z += 1.0f;
}

GLvoid LevelEditor::moveOut()
{
    if (levelOffset->z > -((currentLength * 0.4f) / 2.0f) + 10.0f)
        levelOffset->z -= 1.0f;
}

GLvoid LevelEditor::saveLevel()
{
    bool newlyCreated = false;
    level->save(&newlyCreated);

    if (newlyCreated)
        emit addLevelToLevelsList(level);
}

void LevelEditor::itemClicked(QMouseEvent *event, QList<GLuint> listNames)
{
    if (isMoving)
        return;

    Vector3f *pos = NULL;

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

        case BUTTON_LENGTHEN:
            lengthen();
            break;

        case BUTTON_REDUCE:
            reduce();
            break;

        case BUTTON_ENLARGE:
            enlarge();
            break;

        case BUTTON_GRAVITY_MINUS:
            gravityMinus();
            break;

        case BUTTON_GRAVITY_PLUS:
            gravityPlus();
            break;

        case BUTTON_BACK:
            buttonBackTriggered();
            break;

        case BUTTON_NEXT:
            buttonNextTriggered();
            break;

        case OBSTACLE_0:
            lastCentre = toolbarObstacleCentres.at(0);
            pos = getModelViewPos(new Vector3f(event->x(), event->y(), 0.0f), true);
            currentDelta = Vector3f();
            deltaFromCentre = *pos - lastCentre;
            movingObject = 0;
            break;

        case OBSTACLE_1:
            lastCentre = toolbarObstacleCentres.at(1);
            pos = getModelViewPos(new Vector3f(event->x(), event->y(), 0.0f), true);
            currentDelta = Vector3f();
            deltaFromCentre = *pos - lastCentre;
            movingObject = 1;
            break;

        case OBSTACLE_2:
            lastCentre = toolbarObstacleCentres.at(2);
            pos = getModelViewPos(new Vector3f(event->x(), event->y(), 0.0f), true);
            currentDelta = Vector3f();
            deltaFromCentre = *pos - lastCentre;
            movingObject = 2;
            break;

        case OBSTACLE_3:
            lastCentre = toolbarObstacleCentres.at(3);
            pos = getModelViewPos(new Vector3f(event->x(), event->y(), 0.0f), true);
            currentDelta = Vector3f();
            deltaFromCentre = *pos - lastCentre;
            movingObject = 3;
            break;

        case BUTTON_SAVE:
            saveLevel();
            break;

        case BUTTON_CANCEL:
            level->clearTempObstaclesList();
            break;

        case BUTTON_CLEAR:
            level->clearObstaclesList();
            break;
        }
    }
}

void LevelEditor::mouseReleased(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(currentView == EDITING_LEVEL_VIEW)
    {
        if ((movingObject != -1) && (positionValid == true))
            level->addObstacle(new Obstacle(movingObject, new Vector3f(GLfloat(xCell), GLfloat(yCell), GLfloat(zCell))));

        positionValid = false;
        currentDelta = new Vector3f();
        lastMouseX = 0;
        lastMouseY = 0;
        movingObject = -1;
    }
}

void LevelEditor::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{
    if (isMoving)
        return;

    if (currentView == EDITING_LEVEL_VIEW)
    {
        lastMouseX = event->x();
        lastMouseY = event->y();

        checkMousePosition(event->x(), event->y());
    }

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case LENGTH_LABEL:
            if (!lengthLabel->isRotating(listNames.at(1)))
                lengthLabel->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case LENGTH_STRING:
            if (!lengthString->isRotating(listNames.at(1)))
            {
                if ((listNames.at(1) % 2) == 0)
                    lengthString->startLetterRotation(listNames.at(1), 6, 2);
                else
                    lengthString->startLetterRotation(listNames.at(1), 12, 4);
            }
            break;

        case WIDTH_LABEL:
            if (!widthLabel->isRotating(listNames.at(1)))
                widthLabel->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case WIDTH_STRING:
            if (!widthString->isRotating(listNames.at(1)))
            {
                if ((listNames.at(1) % 2) == 0)
                    widthString->startLetterRotation(listNames.at(1), 6, 2);
                else
                    widthString->startLetterRotation(listNames.at(1), 12, 4);
            }
            break;

        case LABEL_SET_LEVEL_NAME:
            if (!labelSetLevelName->isRotating(listNames.at(1)))
                labelSetLevelName->startLetterRotation(listNames.at(1), 6, 1);
            break;

        }
    }
}

void LevelEditor::wheelScrolled(QWheelEvent *event)
{
    if (currentView == EDITING_LEVEL_VIEW)
    {
        if (event->delta() < 0)
            moveIn();
        else
            moveOut();

        checkMousePosition(lastMouseX, lastMouseY);
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
            lengthen();
        }
        else if (currentView == EDITING_LEVEL_VIEW)
        {
            moveIn();
            checkMousePosition(lastMouseX, lastMouseY);
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
            moveOut();
            checkMousePosition(lastMouseX, lastMouseY);
        }
    }
    else if (key == Qt::Key_Left)
    {
        if (currentView == SET_PARAM_VIEW)
            reduce();
        else if (currentView == SET_GRAVITY_VIEW)
            gravityMinus();
    }
    else if (key == Qt::Key_Right)
    {
        if (currentView == SET_PARAM_VIEW)
            enlarge();
        else if (currentView == SET_GRAVITY_VIEW)
            gravityPlus();
    }
    else if ((key >= Qt::Key_A && key <= Qt::Key_Z) || (key >= Qt::Key_0 && key <= Qt::Key_9) || key == Qt::Key_Space)
    {
        letterTyped(key);
    }
}
