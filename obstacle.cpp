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


#include "obstacle.h"
#include "defines.h"

Obstacle::Obstacle(GLint _modelId, Vector3f *_cell) :
    modelId(_modelId)
{
    setCell(_cell);
}

Obstacle::~Obstacle()
{ }

GLvoid Obstacle::draw(GLboolean simplifyForPicking)
{
    glPushMatrix();

        glTranslatef(position->x, position->y, position->z);
        if (simplifyForPicking)
        {
            drawObstacle(modelId);
        }
        else
        {
            setMaterialColor(color);
            drawObstacle(modelId);
            setMaterialColor(COLOR_DISABLED);
        }

    glPopMatrix();
}

GLint Obstacle::getId()
{
    return id;
}

GLvoid Obstacle::setId(GLint _id)
{
    id = _id;
}

GLvoid Obstacle::setCell(Vector3f *_cell)
{
    cell = new Vector3f(*_cell);
    position = obstacleCellToPosition(cell, modelId);
}

Vector3f *Obstacle::getCell()
{
    return cell;
}

Vector3f *Obstacle::getPosition()
{
    return position;
}

GLvoid Obstacle::setColor(QColor _color)
{
    color = _color;
}

QColor Obstacle::getColor()
{
    return color;
}

GLvoid Obstacle::setModelId(GLint _modelId)
{
    modelId = _modelId;
}

GLint Obstacle::getModelId()
{
    return modelId;
}

GLvoid Obstacle::setType(GLint _type)
{
    type = _type;
}

GLint Obstacle::getType()
{
    return type;
}
