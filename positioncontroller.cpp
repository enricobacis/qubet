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
    *position = *position - Vector3f(1.5f, 1.5f, 1.5f);

    QList<int> xCells;
    QList<int> yCells;
    QList<int> zCells;

    Vector3f *cell = positionToCell(position);

    xCells.append(cell->x);
    if (((int) position->x != position->x) || (((int) position->x % 3) == 0))
        xCells.append(cell->x + 1);

    yCells.append(cell->y);
    if (((int) position->y != position->y) || (((int) position->y % 3) == 0))
        yCells.append(cell->y + 1);

    zCells.append(cell->z);
    if (((int) position->z != position->z) || (((int) position->z % 3) == 0))
        zCells.append(cell->z + 1);

    for (int x = 0; x < xCells.count(); x++)
    {
        for (int y = 0; y < yCells.count(); y++)
        {
            for (int z = 0; z < zCells.count(); z++)
            {
                if (obstacleCells[xCells.at(x)][yCells.at(y)][zCells.at(z)])
                {
                    emit collision();
                    return;
                }
            }
        }
    }
}

Vector3f *PositionController::positionToCell(Vector3f *position)
{
    Vector3f *cells = new Vector3f();

    cells->x = (int)((position->x + (levelWidth / 2.0f)) / 3);
    cells->y = (int)( position->y / 3);
    cells->z = (int)((position->z + (levelLength / 2.0f)) / 3);

    return cells;
}

void PositionController::run()
{ }

void PositionController::createObstacleCells()
{
    int xMax = (int)(level->getWidth() / 3);
    int yMax = 10;
    int zMax = (int)(level->getLength() / 3);

    obstacleCells.resize(xMax);

    for (int x = 0; x < xMax; x++)
    {
        obstacleCells[x].resize(yMax);

        for (int y = 0; y < yMax; y++)
        {
            obstacleCells[x][y].resize(zMax);

            for (int z = 0; z < zMax; z++)
            {
                obstacleCells[x][y][z] = false;
            }
        }
    }

    QMap<GLint,Obstacle*> obstacles = level->getObstaclesList();

    for (QMap<GLint,Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); i++)
    {
        Obstacle *obstacle = dynamic_cast<Obstacle*>(i.value());
        Vector3f *cell = obstacle->getCell();

        obstacleCells[cell->x][cell->y][cell->z] = true;

        switch (obstacle->getModelId())
        {
        case OBSTACLE_I:
            obstacleCells[cell->x]    [cell->y + 1][cell->z]     = true;
            break;

        case OBSTACLE_L:
            obstacleCells[cell->x + 1][cell->y]    [cell->z]     = true;
            obstacleCells[cell->x + 1][cell->y + 1][cell->z]     = true;
            break;

        case OBSTACLE_CUBE_BIG:
            obstacleCells[cell->x]    [cell->y + 1][cell->z]     = true;

            obstacleCells[cell->x + 1][cell->y]    [cell->z]     = true;
            obstacleCells[cell->x + 1][cell->y + 1][cell->z]     = true;

            obstacleCells[cell->x]    [cell->y]    [cell->z + 1] = true;
            obstacleCells[cell->x]    [cell->y + 1][cell->z + 1] = true;

            obstacleCells[cell->x + 1][cell->y]    [cell->z + 1] = true;
            obstacleCells[cell->x + 1][cell->y + 1][cell->z + 1] = true;
            break;
        }
    }
}
