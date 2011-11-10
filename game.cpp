#include "game.h"
#include "defines.h"
#include "game_defines.h"
#include "effects_defines.h"

Game::Game(QMap<QString,Skybox*> _skyboxesList, Skin *_skin, QMap<GLint,Level*> &_levelsList, QObject *_parent, bool _audioEnabled, Skybox *_skybox) :
    parent(_parent),
    skyboxesList(_skyboxesList),
    skin(_skin),
    levelsList(_levelsList),
    audioEnabled(_audioEnabled),
    skybox(_skybox),
    gameType(STORY_MODE)
{
}

Game::Game(QMap<QString,Skybox*> _skyboxesList, Skin *_skin, Level *_level, QObject *_parent, bool _audioEnabled, Skybox *_skybox) :
    parent(_parent),
    skyboxesList(_skyboxesList),
    skin(_skin),
    level(_level),
    audioEnabled(_audioEnabled),
    skybox(_skybox),
    gameType(ARCADE_MODE)
{
}

Game::~Game()
{
    this->disconnect(parent);
    parent->disconnect(this);
}

void Game::startGame()
{

}

void Game::draw(GLboolean simplifyForPicking)
{

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

}

void Game::mouseReleased(QMouseEvent *event)
{

}

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
