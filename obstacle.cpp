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
