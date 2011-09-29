#include "game.h"

Game::Game(Skin *_skin, QMap<GLint,Level*> &_levelsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent) :
    parent(_parent),
    levelsList(_levelsList),
    obstacleModelsList(_obstacleModelsList),
    skin(_skin),
    gameType(STORY_MODE)
{
}

Game::Game(Skin *_skin, Level *_level, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent) :
    parent(_parent),
    level(_level),
    obstacleModelsList(_obstacleModelsList),
    skin(_skin),
    gameType(ARCADE_MODE)
{
}

Game::~Game()
{
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
