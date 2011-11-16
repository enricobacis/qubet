#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "utilities.h"

/**
 * @brief This class rapresents an Obstacle.
 *
 * @version 1.0
 * @author \#34
 */
class Obstacle
{

public:

    /**
     * @brief Constructor of Obstacle.
     *
     * @param _modeld
     * @param _position
     */
    explicit Obstacle(GLint _modelId, Vector3f *_position);

    /**
     * @brief Safely destroy an Obstacle object.
     */
    ~Obstacle();

    /**
     * @brief draw function for Obstacle Object.
     *
     * @param simplifyForPicking
    */
    GLvoid draw(GLboolean simplifyForPicking);

    /**
     * @brief This method return the obstacleId.
     *
     * @returns the obstacleId.
     */
    GLint getId();


    /**
     * @brief set the obstacleId
     *
     * @param _id
     *
    */
    GLvoid setId(GLint _id);

    /**
     * @brief set the obstaclePosition
     *
     * @param _position
     */
    GLvoid setPosition(Vector3f *_position);

    /**
     * @brief returns the obstaclePosition
     *
     * @returns the obstaclePosition
     */
    Vector3f *getPosition();

    /**
     * @brief set the obstacleColor
     *
     * @param _color
     */
    GLvoid setColor(QColor _color);

    /**
     * @brief returns the obstacleColor
     *
     * @returns the obstacleColor.
     */
    QColor getColor();

    /**
     * @brief set the obstacleModelId
     *
     * @param _modelId
     */
    GLvoid setModelId(GLint _modelId);

    /**
     * @brief returns the obstacle modelId.
     *
     * @returns the obstacle modelId.
     */
    GLint getModelId();

    /**
     * @brief set the obstacle type.
     *
     * @param _type
     */
    GLvoid setType(GLint _type);

    /**
     * @brief returns the obstacle type value.
     *
     * @returns the obstacle type value.
     */
    GLint getType();

private:
    GLint id; /**< It is the obstacle id. */
    Vector3f *position; /**< It is the obstacle position. */
    QColor color; /**< It is the obstacle color. */
    GLint modelId; /**< It is the obstacle modelId. */
    GLint type; /**< It is the obstacle type value. */

};

#endif // OBSTACLE_H
