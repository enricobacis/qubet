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


#include "positioncontroller.h"
#include "defines.h"

PositionController::PositionController(Cube *_cube, Level *_level, QObject *_parent) :
    parent(_parent),
    cube(_cube),
    level(_level)
{
    connect(this, SIGNAL(collision()), parent, SLOT(collided()));

    levelLength = level->getLength();
    levelWidth = level->getWidth();

    createObstacleCells();

    checkPositionTimer = new QTimer(this);
    connect(checkPositionTimer, SIGNAL(timeout()), this, SLOT(checkCollision()));
    checkPositionTimer->setSingleShot(true);
    checkPositionTimer->start(30);
}

PositionController::~PositionController()
{
    this->disconnect(parent);
    parent->disconnect(this);

    if (checkPositionTimer != NULL)
        stopChecking();
}

void PositionController::startChecking()
{
    checkPositionTimer->start(30);
}

void PositionController::stopChecking()
{
    checkPositionTimer->stop();
}

void PositionController::checkCollision()
{
    Vector3f* position = cube->getPosition();
    *position += new Vector3f(0.01f, 0.01f, 0.01f - 12.0f);

    QList<int> xCells;
    QList<int> yCells;
    QList<int> zCells;

    Vector3f *cell = positionToCell(position);

    if (cell->z >= 0)
    {
        xCells.append((int)(cell->x));
        if (!(isInteger(position->x) && ((((int)(position->x)) % 3) == 0)))
            xCells.append((int)(cell->x + 1));

        yCells.append((int)(cell->y));
        if (!(isInteger(position->y) && ((((int)(position->y)) % 3) == 0)))
            yCells.append((int)(cell->y + 1));

        zCells.append((int)(cell->z));
        if (!(isInteger(position->z) && ((((int)(position->z)) % 3) == 0)))
            zCells.append((int)(cell->z + 1));

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

    checkPositionTimer->start(30);
}

Vector3f *PositionController::positionToCell(Vector3f *position)
{
    Vector3f *cells = new Vector3f();

    cells->x = (int)(position->x / 3);
    cells->y = (int)(position->y / 3);
    cells->z = (int)(position->z / 3);

    return cells;
}

void PositionController::run()
{ }

bool PositionController::isInteger(float f)
{
    int i = f;
    return (f - static_cast<float>(i) < 0.02);
}

void PositionController::createObstacleCells()
{
    int xMax = (int)(level->getWidth()  / 3) + 5;
    int yMax = 5;
    int zMax = (int)(level->getLength() / 3) + 5;

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
