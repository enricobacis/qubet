#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QColor>
#include "vector3f.h"

#include <GL/gl.h>

class Obstacle : public QObject
{
    Q_OBJECT

public:
    explicit Obstacle(GLint id, QObject *parent = 0);
    ~Obstacle();

    GLint getId();

    void setPosition(Vector3f *_position);
    Vector3f *getPosition();

    void setColor(QColor _color);
    QColor getColor();

    void setModelId(GLint _modelId);
    GLint getModelId();

    void setType(GLint _type);
    GLint getType();

private:
    GLint id;
    Vector3f *position;
    QColor color;
    GLint modelId;
    GLint type;

};

#endif // OBSTACLE_H
