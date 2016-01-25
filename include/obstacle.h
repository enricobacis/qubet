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
     * @param _cell is the cell of the Obstacle.
     */
    explicit Obstacle(GLint _modelId, Vector3f *_cell);

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
     * @brief Set the cell of the Obstacle.
     *
     * @param _cell is the cel to set.
     */
    GLvoid setCell(Vector3f *_cell);

    /**
     * @brief Returns the cell of the Obstacle.
     *
     * @returns the cell of the Obstacle.
     */
    Vector3f *getCell();

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
    Vector3f *cell; /**< It is the obstacle cell position. */
    QColor color; /**< It is the obstacle color. */
    GLint modelId; /**< It is the obstacle modelId. */
    GLint type; /**< It is the obstacle type value. */

};

#endif // OBSTACLE_H
