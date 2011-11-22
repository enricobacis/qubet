//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "game.h"
#include "defines.h"
#include "game_defines.h"
#include "effects_defines.h"

Game::Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent, bool _audioEnabled, QGLShaderProgram *_explosionShader) :
    parent(_parent),
    iconsList(_iconsList),
    alphabet(_alphabet),
    skin(_skin),
    levelsList(_levelsList),
    audioEnabled(_audioEnabled),
    gameType(STORY_MODE),
    explosionShader(_explosionShader)
{
    initGame();
}

Game::Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, Level *_level, QObject *_parent, bool _audioEnabled, QGLShaderProgram *_explosionShader) :
    parent(_parent),
    iconsList(_iconsList),
    alphabet(_alphabet),
    skin(_skin),
    level(_level),
    audioEnabled(_audioEnabled),
    gameType(ARCADE_MODE),
    explosionShader(_explosionShader)
{
    initGame();
}

Game::~Game()
{
    this->disconnect(parent);
    parent->disconnect(this);

    if (positionController != NULL)
        positionController->~PositionController();

    if (cube != NULL)
        cube->~Cube();
}

void Game::startGame()
{
    playLevel();
}

void Game::draw(GLboolean simplifyForPicking)
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

            // Primary Actions

            case COUNTDOWN:
                countdown();
                break;

            case MOVE_TO_LEVEL:
                if (cameraOffset->x < 0.0f)
                    cameraOffset->x += 2.0f;
                else
                    currentActions->setPrimaryAction(COUNTDOWN);
                break;

            case MOVE_TO_NEXT_LEVEL:
                if (cameraOffset->x < 60.0f)
                {
                    cameraOffset->x += 2.0f;
                }
                else
                {
                    level = next;
                    currentLevel = levelsList.key(next);
                    currentActions->setPrimaryAction(MOVE_TO_LEVEL);
                    playLevel();
                }
                break;

            case GO_TO_RESULTS_SCREEN:
                if (cameraOffset->x < 60.0f)
                    cameraOffset->x += 2.0f;
                else
                    if (waitCounter++ > 150)
                        currentActions->setPrimaryAction(EXIT_TO_MENU);
                break;

            case EXIT_TO_MENU:
                if (cameraOffset->x < (isQuitting ? 60.0f : 120.0f))
                {
                    cameraOffset->x += 2.0f;
                }
                else
                {
                    emit gameClosedSignal();
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
            }
        }
    }

    if (!isQuitting)
    {
        glPushMatrix();

            glTranslatef(0.0, -6.0f, 0.0f);
            levelName->draw(simplifyForPicking);

            glTranslatef(0.0f,  12.0f, 0.0f);
            stateLabel->draw(simplifyForPicking);

            if (!showingResult)
            {
                glTranslatef(-9.0f, 0.0f, 0.0f);
                deathCounter->draw(simplifyForPicking);

                dynamic_cast<QGLWidget*>(parent)->renderText(-1.0f, -1.5f, 0.0f, "deaths");
            }

            if (isPaused)
            {
                glPushMatrix();
                    glTranslatef(16.0f, -4.0f, 0.0f);
                    quitLabel->draw(simplifyForPicking);
                glPopMatrix();
            }

        glPopMatrix();
    }

    glPushName(BUTTON_VOLUME);
    glPushMatrix();

        glTranslatef(9.5f, 6.0f, 3.0f);
        glRotatef(angleRotVolumeCube, -1.0f, 0.0f, 0.0f);
        drawPrism(0.8f, 0.8f, 0.8f, volumeSkin, true);

    glPopMatrix();
    glPopName();

    if (!simplifyForPicking)
    {
        glPushMatrix();

            glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);

            if ((currentActions->getPrimaryAction() == GO_TO_RESULTS_SCREEN) ||
                    ((currentActions->getPrimaryAction() == EXIT_TO_MENU) && !isQuitting))
            {
                glPushMatrix();
                    glTranslated(60.0f, 5.0f, 0.0f);
                    resultsCubeString->draw(simplifyForPicking);
                    glTranslated(0.0f, -5.0f, 15.0f);
                    deathCounter->draw(simplifyForPicking);
                    glTranslated(0.0f, -5.0f, -15.0f);
                    adjectiveCubeString->draw(simplifyForPicking);
                glPopMatrix();
            }

            glRotatef(15.0f, 1.0f, 0.0f, 0.0f);

            glPushMatrix();
                glTranslatef(-(level->getWidth() / 2.0f) + 1.5f, levelOffset->y + 1.5f, -1.5f);
                cube->draw(simplifyForPicking);
            glPopMatrix();

            glTranslatef(levelOffset->x, levelOffset->y, levelOffset->z + cube->getZ());
            level->draw(simplifyForPicking);

            glTranslatef(0.0f, 0.0f, -levelOffset->z - 6.0f);
            drawPrism(level->getWidth(), LEVEL_HEIGHT, 12.0f, gridSkin);

            glTranslatef(0.0f, 0.0f, -level->getLength() - 12.0f);
            drawPrism(level->getWidth(), LEVEL_HEIGHT, 12.0f, gridSkin);

        glPopMatrix();
    }
}

void Game::initGame()
{
    connect(this, SIGNAL(setMouseMovementTracking(int)), parent, SLOT(setMouseMovementTracking(int)));
    connect(this, SIGNAL(setSkybox(QString)), parent, SLOT(setSkybox(QString)));

    currentActions = new ActionList(MOVE_TO_LEVEL);
    deaths = 0;
    waitCounter = 0;
    isPaused = false;
    isQuitting = false;
    isExploding = false;
    showingResult = false;

    cube = NULL;
    positionController = NULL;

    angleRotVolumeCube = (audioEnabled ? 0.0f : 90.0f);

    GLuint volume_on  = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin   = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);
    gridSkin     = new Skin(iconsList.value(GRID));

    stateLabel   = new CubeString("", 2.0f, alphabet, STATE_LABEL);
    quitLabel    = new CubeString("quit", 1.5f, alphabet, QUIT_LABEL);
    deathCounter = new CubeString("0", 1.5f, alphabet);
    levelName    = new CubeString("", 10.0f, 2.0f, alphabet, STATE_LABEL);
    resultsCubeString = new CubeString("Deaths", 1.5f, alphabet);
    adjectiveCubeString = NULL;

    emit setMouseMovementTracking(MOUSE_MOVED_NONE);

    if (gameType == STORY_MODE)
    {
        if (!levelsList.isEmpty())
        {
            currentLevel = levelsList.begin().key();
            level = static_cast<Level*>(levelsList.begin().value());
        }
    }
}

void Game::countdown()
{
    switch (introStep)
    {
    case 10:
        stateLabel->~CubeString();
        stateLabel = new CubeString("3", 2.0f, alphabet, STATE_LABEL);
        stateLabel->startStringRotation(5, 1);
        playEffect(EFFECT_BOP);
        break;

    case 50:
        stateLabel->~CubeString();
        stateLabel = new CubeString("2", 2.0f, alphabet, STATE_LABEL);
        stateLabel->startStringRotation(9, 2);
        playEffect(EFFECT_BOP);
        break;

    case 90:
        stateLabel->~CubeString();
        stateLabel = new CubeString("1", 2.0f, alphabet, STATE_LABEL);
        stateLabel->startStringRotation(18, 4);
        playEffect(EFFECT_BOP);
        break;

    case 130:
        stateLabel->~CubeString();
        stateLabel = new CubeString("go", 2.0f, alphabet, STATE_LABEL);
        stateLabel->startStringRotation(27, 6);
        playEffect(EFFECT_BEEP);

        emit hideLevelName();
        cube->startCube();
        break;

    case 180:
        stateLabel->~CubeString();
        stateLabel = new CubeString("", 2.0f, alphabet, STATE_LABEL);
        currentActions->setPrimaryAction(DO_NOTHING);
        break;
    }

    introStep++;
}

void Game::playLevel()
{
    level->load();
    levelName = new CubeString(level->getName(), 15.0f, 2.0f, alphabet, STATE_LABEL);

    emit setSkybox(level->getSkyboxName());
    emit playAmbientMusic("resources/music/" + level->getAmbientMusicFilename());

    if (cube != NULL)
        cube->~Cube();

    cube = new Cube(level, skin, this, explosionShader);

    if (positionController != NULL)
        positionController->~PositionController();

    positionController = new PositionController(cube, level, this);
    positionController->startChecking();

    introStep = 0;

    cameraOffset = new Vector3f(-60.0, 0.0f, 4.0f);
    levelOffset  = new Vector3f(0.0f, -4.0f, -(level->getLength() / 2.0f) - 12.0f);
}

void Game::nextLevel()
{
    QMap<GLint,Level*>::iterator i = levelsList.find(currentLevel);
    i++;
    next = static_cast<Level*>(i.value());

    if (i != levelsList.end())
    {
        next = static_cast<Level*>(i.value());
        if (next->getIsInStory())
        {
            currentActions->setPrimaryAction(MOVE_TO_NEXT_LEVEL);
            playEffect(EFFECT_HEREWEGO);
            return;
        }
    }

    createResultStrings();
    emit stopAmbientMusic();
    playEffect(EFFECT_STAGECLEAR);
}

void Game::pauseGame()
{
    isPaused = true;

    cube->stopCube();
    positionController->stopChecking();

    if (audioEnabled)
        emit enableAudio(false);

    emit setMouseMovementTracking(MOUSE_MOVED_FULL);

    stateLabel->~CubeString();
    stateLabel = new CubeString("paused", 1.5f, alphabet, STATE_LABEL);
}

void Game::continueGame()
{
    isPaused = false;

    cube->startCube();

    if (!isExploding)
        positionController->startChecking();

    if (audioEnabled)
        emit enableAudio(true);

    emit setMouseMovementTracking(MOUSE_MOVED_NONE);

    stateLabel->~CubeString();
    stateLabel = new CubeString("", 2.0f, alphabet, STATE_LABEL);
}

void Game::quitGame()
{
    isQuitting = true;
    currentActions->setPrimaryAction(EXIT_TO_MENU);

    emit stopAmbientMusic();

    if (audioEnabled)
        emit enableAudio(true);
}

void Game::itemClicked(QMouseEvent *event, QList<GLuint> listNames)
{
    Q_UNUSED(event);

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case BUTTON_VOLUME:
            if ((GLint(angleRotVolumeCube) % 90) == 0)
            {
                audioEnabled = !audioEnabled;

                if (!isPaused)
                    emit enableAudio(audioEnabled);

                currentActions->appendSecondaryAction(ROTATE_VOLUMECUBE);
            }
            break;

        case QUIT_LABEL:
            quitGame();
            break;
        }
    }
}

void Game::mouseReleased(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void Game::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{
    Q_UNUSED(event);

    if (!isPaused)
        return;

    if (!listNames.isEmpty())
    {
        switch (listNames.at(0))
        {
        case STATE_LABEL:
            if (!stateLabel->isRotating(listNames.at(1)))
                stateLabel->startLetterRotation(listNames.at(1), 6, 1);
            break;

        case QUIT_LABEL:
            if (!quitLabel->isRotating(listNames.at(1)))
                quitLabel->startLetterRotation(listNames.at(1), 6, 1);
            break;
        }
    }
}

void Game::wheelScrolled(QWheelEvent *event)
{
    Q_UNUSED(event);
}

void Game::keyPressed(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
    case Qt::Key_P:
        if (currentActions->getPrimaryAction() != COUNTDOWN)
        {
            if (isPaused)
                continueGame();
            else
                pauseGame();

            event->accept();
        }
        break;

    default:
        emit keyPressedSignal(event);
    }
}

void Game::collided()
{
    emit collision();
    exploded();
}

void Game::exploded()
{
    isExploding = true;
    deaths++;
    deathCounter->~CubeString();
    deathCounter = new CubeString(QString::number(deaths), 1.5f, alphabet);
    deathCounter->startStringRotation(10, 1);
}

void Game::explosionFinished()
{
    isExploding = false;
    positionController->startChecking();
}

void Game::levelCompleted()
{
    positionController->~PositionController();
    positionController = NULL;

    if (gameType == ARCADE_MODE)
    {
        emit stopAmbientMusic();
        playEffect(EFFECT_STAGECLEAR);
        createResultStrings();
    }
    else
    {
        nextLevel();
    }
}

void Game::hideLevelName()
{
    levelName = new CubeString("", 10.0f, 2.0f, alphabet, STATE_LABEL);
}

void Game::createResultStrings()
{
    showingResult = true;
    currentActions->setPrimaryAction(GO_TO_RESULTS_SCREEN);

    QString adjective;
    if (deaths == 0) adjective = "veteran";
    else if(deaths < 10) adjective = "master";
    else if(deaths < 30) adjective = "pro";
    else if(deaths < 50) adjective = "respectable";
    else if(deaths < 70) adjective = "good";
    else if(deaths < 110) adjective = "noob";
    else if(deaths < 150) adjective = "goat";
    else if(deaths < 200) adjective = "change game";
    else if(deaths < 250) adjective = "worst ever";
    else adjective = "no way";

    adjectiveCubeString = new CubeString(adjective, 18.0f, 3.0f , alphabet);

    adjectiveCubeString->setCurrentAngle(0.0f, -40.0f);
    adjectiveCubeString->startStringRotation(10, 8);
}
