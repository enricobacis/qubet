#include "game.h"
#include "defines.h"
#include "game_defines.h"
#include "effects_defines.h"

Game::Game(Skin *_skin, QMap<GLint,Level*> &_levelsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent) :
    parent(_parent),
    skin(_skin),
    levelsList(_levelsList),
    obstacleModelsList(_obstacleModelsList),
    gameType(STORY_MODE)
{
}

Game::Game(Skin *_skin, Level *_level, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent) :
    parent(_parent),
    skin(_skin),
    level(_level),
    obstacleModelsList(_obstacleModelsList),
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

void Game::itemClicked(QList<GLuint> listNames)
{

}

void Game::mouseReleased(QMouseEvent *event)
{

}

void Game::mouseMoved(QMouseEvent *event, QList<GLuint> listNames)
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

}
