#include "positioncontroller.h"

PositionController::PositionController(Cube *_cube, Level *_level, QObject *_parent) :
    parent(_parent),
    cube(_cube),
    level(_level)
{
    checkPositionTimer = new QTimer(this);

    createObstacleCells();
}

PositionController::~PositionController()
{
    this->disconnect(parent);
    parent->disconnect(this);
}

GLvoid PositionController::checkCollision()
{

}

void PositionController::run()
{

}

void PositionController::createObstacleCells()
{
//    bool cells[(int)(level->getWidth() / 3)][10][(int)(level->getLength() / 3)];
}
