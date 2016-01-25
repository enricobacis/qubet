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


#ifndef POSITIONCONTROLLER_H
#define POSITIONCONTROLLER_H

#include "cube.h"

/**
 * @brief PositionController Class check if the cube has a collision with obstacles.
 *
 * @version 1.0
 * @author \#34
 */
class PositionController : public QThread
{
    Q_OBJECT

public:

    /**
     * @brief Create a PositionController Objects.
     *
     * @param _cube is the cube Object pointer.
     * @param _level is the level Object pointer.
     * @param _parent is the parent Object pointer.
     */
    explicit PositionController(Cube *_cube, Level *_level, QObject *_parent = 0);

    /**
     * @brief Destroy a PositionController Object.
     */
    ~PositionController();

    /**
     * @brief Start checking for collision.
     */
    void startChecking();

    /**
     * @brief Stop checking for collisions.
     */
    void stopChecking();


private:

    QObject *parent; /**< It is the parent of the PositionController. */
    Cube *cube; /**< It is the pointer to the Cube Object. */
    Level *level; /**< Is the pointer to the Level Object. */
    GLint levelLength; /**< It is the length of the Level. */
    GLint levelWidth; /**< It is the width of the Level. */
    QTimer *checkPositionTimer; /**< QTimer controlling the checkCollision() calls. */
    QVector<QVector<QVector<bool> > > obstacleCells; /**< It is the 3d matrix rappresent obstacle cells */

    /**
     * @brief Returns the cell coordinates from absolute position.
     *
     * @param position is the vector of absolute coordinates.
     *
     * @returns the cell coordinates from absolute position.
     */
    Vector3f *positionToCell(Vector3f *position);

    /**
     * @brief Create the 3D Matrix of ObstacleCells.
     */
    GLvoid createObstacleCells();

    /**
     * @brief Reimplementation of the run() function of the QThread class.
     */
    void run();

    /**
     * @brief Check if a float is an integer.
     *
     * @param f is the float.
     * @return true if is an integer.
     */
    bool isInteger(float f);

private slots:

    /**
     * @brief Check if the cube has a collision with an obstacle.
     */
    void checkCollision();

signals:

    /**
     * @brief Signal emitted when the cube has a collision with an obstacle.
     */
    void collision();

};

#endif // POSITIONCONTROLLER_H
