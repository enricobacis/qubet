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
     * @brief Constructor of PositionController Objects.
     *
     * @param _cube It is the cube Object pointer.
     * @param _level It is the level Object pointer.
     * @param _parent It is the parent Object pointer.
     */
    explicit PositionController(Cube *_cube, Level *_level, QObject *_parent = 0);

    /**
     * @brief Destroyer of PositionController Object.
     *
     */
    ~PositionController();

private:
    Cube *cube; /**< It is the pointer to the Cube Object. */
    Level *level; /**< Is the pointer to the Level Object. */
    QTimer checkPositionTimer; /**< QTimer controlling the checkCollision() calls. */

    /**
     * @brief Check if the cube has a collision with an obstacle.
     *
     */
    GLvoid checkCollision();

    /**
     * @brief Reimplementation of the run() function of the QThread class.
     *
     *
     */
    void run();

signals:
    /**
     * @brief Signal emitted when the cube has a collision with an obstacle.
     *
     */
    void collision();

};

#endif // POSITIONCONTROLLER_H
