#include "positioncontroller.h"
#include "defines.h"

PositionController::PositionController(Cube *_cube, Level *_level, QObject *_parent) :
    parent(_parent),
    cube(_cube),
    level(_level)
{
    levelLength = level->getLength();
    levelWidth = level->getWidth();

    createObstacleCells();

    checkPositionTimer = new QTimer(this);
    connect(checkPositionTimer, SIGNAL(timeout()), this, SLOT(checkCollision()));
    checkPositionTimer->start(30);
}

PositionController::~PositionController()
{
    this->disconnect(parent);
    parent->disconnect(this);

    if (checkPositionTimer != NULL)
        checkPositionTimer->stop();
}

GLvoid PositionController::checkCollision()
{
    Vector3f* position = cube->getPosition();
    GLfloat cubeSide = (GLfloat) cube->getSideLength();
    *position = *position - Vector3f(cubeSide / 2.0f, cubeSide / 2.0f, cubeSide / 2.0f);
    Vector3f *vertex;

    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            for (int z = 0; z < 2; z++)
            {
                if (obstacleCells[][][])
                vertex = Vector3f(position->)
            }
        }
    }
}

Vector3f *PositionController::positionToCell(Vector3f *position)
{
    Vector3f *cells = new Vector3f();

    cells->x = (int)((position->x + (width / 2.0f)) / 3);
    cells->y = (int)( position->y / 3);
    cells->z = (int)((position->z + (length / 2.0f)) / 3);

    return cells;
}

void PositionController::run()
{ }

void PositionController::createObstacleCells()
{
    int xMax = ;
    int yMax = ;
    int zMax = ;

    for (int x = 0; x < xMax; x++)
    {
        for (int y = 0; y < yMax; y++)
        {

        }
    }

    obstacleCells[(int)(level->getWidth() / 3)][10][(int)(level->getLength() / 3)];
}
