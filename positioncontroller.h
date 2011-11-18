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
     * @brief Start checking for collisions;
     */
    void startChecking();


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
