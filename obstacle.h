#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QColor>
#include "vector3f.h"

#include <GL/gl.h>

/**
 * @brief This class rapresents an Obstacle.
 *
 * @version 1.0
 * @author \#34
 */
class Obstacle : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create an Obstacle object.
     *
     * @param id is the id given to the Obstacle object.
     * @param parent is the parent whom has generated the Obstacle object.
     */
    explicit Obstacle(GLint id, QObject *parent = 0);

    /**
     * @brief Safely destroy an Obstacle object.
     */
    ~Obstacle();

    /**
     * @brief This method
     *
     */
    GLint getId();

    /**
     * @brief
     *
     * @param _position
     */
    GLvoid setPosition(Vector3f *_position);

    /**
     * @brief
     *
     */
    Vector3f *getPosition();

    /**
     * @brief
     *
     * @param _color
     */
    GLvoid setColor(QColor _color);

    /**
     * @brief
     *
     */
    QColor getColor();

    /**
     * @brief
     *
     * @param _modelId
     */
    GLvoid setModelId(GLint _modelId);

    /**
     * @brief
     *
     */
    GLint getModelId();

    /**
     * @brief
     *
     * @param _type
     */
    GLvoid setType(GLint _type);

    /**
     * @brief
     *
     */
    GLint getType();

private:
    GLint id; /**< TODO */
    Vector3f *position; /**< TODO */
    QColor color; /**< TODO */
    GLint modelId; /**< TODO */
    GLint type; /**< TODO */
    GLboolean solid; /**< TODO */

};

#endif // OBSTACLE_H
