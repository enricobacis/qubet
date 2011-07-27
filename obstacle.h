#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QColor>
#include "vector3f.h"

#include <GL/gl.h>

/**
 * @brief
 *
 */
class Obstacle : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param id
     * @param parent
     */
    explicit Obstacle(GLint id, QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~Obstacle();

    /**
     * @brief
     *
     */
    GLint getId();

    /**
     * @brief
     *
     * @param _position
     */
    void setPosition(Vector3f *_position);
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
    void setColor(QColor _color);
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
    void setModelId(GLint _modelId);
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
    void setType(GLint _type);
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

};

#endif // OBSTACLE_H
