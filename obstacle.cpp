#include "obstacle.h"

Obstacle::Obstacle(GLint _id, Vector3f *_position):
    id(_id),
    position(_position)
{

}

Obstacle::~Obstacle()
{

}

GLvoid Obstacle::draw(GLboolean simplifyForPicking)
{
    glTranslatef(position->x, position->y, position->z);
    drawObstacle(id);
    glTranslatef(-position->x, -position->y, -position->z);
}

GLint Obstacle::getId()
{
    return id;
}

GLvoid Obstacle::setPosition(Vector3f *_position)
{
    position->x = _position->x;
    position->y = _position->y;
    position->z = _position->z;
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
