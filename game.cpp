#include "game.h"
#include "defines.h"
#include "game_defines.h"
#include "effects_defines.h"

Game::Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent, bool _audioEnabled) :
    parent(_parent),
    iconsList(_iconsList),
    alphabet(_alphabet),
    skin(_skin),
    levelsList(_levelsList),
    audioEnabled(_audioEnabled),
    gameType(STORY_MODE)
{
    initGame();
}

Game::Game(QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, Skin *_skin, Level *_level, QObject *_parent, bool _audioEnabled) :
    parent(_parent),
    iconsList(_iconsList),
    alphabet(_alphabet),
    skin(_skin),
    level(_level),
    audioEnabled(_audioEnabled),
    gameType(ARCADE_MODE)
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
            case INTRODUCTION:
                introduction();
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

    glPushName(BUTTON_VOLUME);
    glPushMatrix();

        glTranslatef(9.5f, 6.0f, 3.0f);
        glRotatef(angleRotVolumeCube, -1.0f, 0.0f, 0.0f);
        drawPrism(0.8f, 0.8f, 0.8f, volumeSkin, true);

    glPopMatrix();
    glPopName();

    glPushMatrix();
        glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);
        glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
        glPushMatrix();
            glTranslatef(-(level->getWidth() / 2.0f) + 1.5f, levelOffset->y + 1.5f, -1.5f);
            cube->draw();
        glPopMatrix();

        glTranslatef(levelOffset->x, levelOffset->y, levelOffset->z + cube->getPosition()->z);
        level->draw(simplifyForPicking);


    glPopMatrix();
    //inizio a scrivere l' intro
    glPushMatrix();
    //intro->draw(simplifyForPicking);
    glPopMatrix();
    //finito l intro

}

void Game::initGame()
{
    connect(this, SIGNAL(setMouseMovementTracking(int)), parent, SLOT(setMouseMovementTracking(int)));
    connect(this, SIGNAL(setSkybox(QString)), parent, SLOT(setSkybox(QString)));

    currentActions = new ActionList(INTRODUCTION);

    introStep = 0;

    angleRotVolumeCube = (audioEnabled ? 0.0f : 90.0f);

    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);

    intro = new CubeString("", 3.0f, alphabet);

    emit setMouseMovementTracking(MOUSE_MOVED_NONE);

    switch (gameType)
    {
    case STORY_MODE:
        if (!levelsList.isEmpty())
        {
            currentLevel = levelsList.begin().key();
            level = static_cast<Level*>(levelsList.begin().value());
        }
        break;

    case ARCADE_MODE:
        break;
    }
}

void Game::introduction(){
    switch(introStep)
    {
    case 10:
        intro = new CubeString("3", 3.0f, alphabet );
        intro->startStringRotation(5, 1);
        break;
    case 50:
        intro = new CubeString("2", 3.0f, alphabet );
        intro->startStringRotation(9, 2);
        break;
    case 90:
        intro = new CubeString("1", 3.0f, alphabet );
        intro->startStringRotation(18, 4);
        break;
    case 130:
        intro = new CubeString("go", 3.0f, alphabet );
        intro->startStringRotation(27, 6);
        break;
    case 180:
        currentActions->setPrimaryAction(DO_NOTHING);
        break;
    default:
        break;
    }
    introStep++;
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 0.0f);
    intro->draw();
    glPopMatrix();
}

void Game::playLevel()
{
    level->load();

    emit setSkybox(level->getSkyboxName());
    emit playAmbientMusic("resources/music/" + level->getAmbientMusicFilename());

    cube = new Cube(level, skin, this);
    positionController = new PositionController(cube, level, this);

    positionController->startChecking();

    cameraOffset = new Vector3f(0.0,   0.0f, 4.0f);
    levelOffset  = new Vector3f(0.0f, -4.0f, -(level->getLength() / 2.0f));
}

void Game::nextLevel()
{

}

void Game::pauseGame()
{

}

void Game::continueGame()
{

}

void Game::quitGame()
{
    emit gameClosedSignal();
    return;
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
                emit enableAudio(audioEnabled);
                currentActions->appendSecondaryAction(ROTATE_VOLUMECUBE);
            }
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
    Q_UNUSED(listNames);
}

void Game::wheelScrolled(QWheelEvent *event)
{
    Q_UNUSED(event);
}

void Game::keyPressed(QKeyEvent *event)
{
    emit keyPressedSignal(event);
}

void Game::collided()
{
    emit collision();
}

void Game::explosionFinished()
{
    positionController->startChecking();
}

void Game::levelCompleted()
{
    positionController->~PositionController();
    cube->~Cube();

    if (gameType == ARCADE_MODE)
    {
        playEffect(EFFECT_STAGECLEAR);
        quitGame();
    }
    else
    {
        nextLevel();
    }
}
