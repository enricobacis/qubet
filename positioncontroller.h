#ifndef POSITIONCONTROLLER_H
#define POSITIONCONTROLLER_H

#include <QThread>
#include <QMap>

#include "cube.h"
#include "level.h"
#include "vector3f.h"

#include <GL/gl.h>

/**
 * @brief The PositionController class checks if the Cube collides with obstacles.
 *
 */
class PositionController : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the PositionController objects.
     *
     * @param _cube Pointer to the Cube object.
     * @param _level Pointer to the Level object.
     * @param _obstacleModelsList The obstacleModelsList loaded from the Loader.
     * @param parent Pointer to the parent of the object.
     */
    explicit PositionController(Cube *_cube, Level *_level, QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *parent = 0);

    /**
     * @brief Destructor for the PositionController objects.
     *
     */
    ~PositionController();

private:
    Cube *cube; /**< TODO */
    Level *level; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    QTimer checkPositionTimer; /**< TODO */

    /**
     * @brief Checks if the cube has collided with obstacles.
     *
     */
    void checkPosition();

    /**
     * @brief Re-implementation of the run() QThread function.
     *
     *
     */
    void run();

signals:
    /**
     * @brief Signal emitted when the cube collides with an obstacle.
     *
     */
    void collision();

};

#endif // POSITIONCONTROLLER_H
