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
     * @param _modelId is the modelId of the Obstacle.
     * @param _position is the position of the Obstacle.
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
     * @brief Set the obstacleId.
     *
     * @param _id is the id to set.
    */
    GLvoid setId(GLint _id);

    /**
     * @brief Set the obstacle position.
     *
     * @param _position is the position to set.
     */
    GLvoid setPosition(Vector3f *_position);

    /**
     * @brief Returns the obstacle position.
     *
     * @returns the obstacle position.
     */
    Vector3f *getPosition();

    /**
     * @brief Set the obstacle color.
     *
     * @param _color is the color to set.
     */
    GLvoid setColor(QColor _color);

    /**
     * @brief Returns the obstacle color.
     *
     * @returns the obstacle color.
     */
    QColor getColor();

    /**
     * @brief Set the obstacle modelId.
     *
     * @param _modelId is the modelId to set.
     */
    GLvoid setModelId(GLint _modelId);

    /**
     * @brief Returns the obstacle modelId.
     *
     * @returns the obstacle modelId.
     */
    GLint getModelId();

    /**
     * @brief Set the obstacle type.
     *
     * @param _type is the type to set.
     */
    GLvoid setType(GLint _type);

    /**
     * @brief Returns the obstacle type.
     *
     * @returns the obstacle type.
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
