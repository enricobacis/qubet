#include "obstacle.h"

Obstacle::Obstacle(GLint _modelId, Vector3f *_position) :
    modelId(_modelId)
{
    position = new Vector3f(*_position);
}

Obstacle::~Obstacle()
{ }

GLvoid Obstacle::draw(GLboolean simplifyForPicking)
{
    Q_UNUSED(simplifyForPicking);

    glPushMatrix();
        glTranslatef(position->x, position->y, position->z);
        drawObstacle(modelId);
    glPopMatrix();
}

GLint Obstacle::getId()
{
    return id;
}

GLvoid Obstacle::setPosition(Vector3f *_position)
{
    position = new Vector3f(*_position);
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
