#include "game.h"
#include "defines.h"
#include "game_defines.h"
#include "effects_defines.h"

Game::Game(QMap<GLint,GLuint> &_iconsList, QMap<QString,Skybox*> &_skyboxesList, Alphabet *_alphabet, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent, bool _audioEnabled) :
    parent(_parent),
    iconsList(_iconsList),
    skyboxesList(_skyboxesList),
    alphabet(_alphabet),
    skin(_skin),
    levelsList(_levelsList),
    audioEnabled(_audioEnabled),
    gameType(STORY_MODE)
{
    initGame();
}

Game::Game(QMap<GLint,GLuint> &_iconsList, QMap<QString,Skybox*> &_skyboxesList, Alphabet *_alphabet, Skin *_skin, Level *_level, QObject *_parent, bool _audioEnabled) :
    parent(_parent),
    iconsList(_iconsList),
    skyboxesList(_skyboxesList),
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
}

void Game::startGame()
{
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

    qDebug() << level->getSkyboxName();

    skybox = skyboxesList.value(level->getSkyboxName());
    emit playAmbientMusic("resources/music/" + level->getAmbientMusicFilename());
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

    //    glTranslatef(-cameraOffset->x, -cameraOffset->y, -cameraOffset->z);
    //    glRotatef(cameraAngle, 0.0f, 0.0f, 1.0f);

    //    glPushMatrix();

    //    glPopMatrix();
}

void Game::initGame()
{
    currentActions = new ActionList(DO_NOTHING);
    currentActions->appendSecondaryAction(ROTATE_SKYBOX);

    skyboxAngle = 0.0f;
    angleRotVolumeCube = (audioEnabled ? 0.0f : 90.0f);

    GLuint volume_on = iconsList.value(VOLUME_ON);
    GLuint volume_off = iconsList.value(VOLUME_OFF);
    volumeSkin = new Skin(0, 0, volume_off, volume_off, volume_on, volume_on);
}

void Game::playLevel(GLint levelId)
{

}

void Game::nextLevel(GLint currentLevelId)
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

}

void Game::itemClicked(QMouseEvent *event, QList<GLuint> listNames)
{
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
{ }

void Game::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
{

}

void Game::wheelScrolled(QWheelEvent *event)
{

}

void Game::keyPressed(QKeyEvent *event)
{

}

void Game::collided()
{

}

void Game::levelCompleted()
{
    playEffect(EFFECT_STAGECLEAR);
}
