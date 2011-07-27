#ifndef POSITIONCONTROLLER_H
#define POSITIONCONTROLLER_H

#include <QThread>
#include "cube.h"
#include "level.h"
#include "vector3f.h"

#include <GL/gl.h>

/**
 * @brief
 *
 */
class PositionController : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param _cube
     * @param _level
     * @param
     * @param _obstacleModelsList
     * @param parent
     */
    explicit PositionController(Cube *_cube, Level *_level, QMap<Vector3f*, GLint> *_obstacleModelsList, QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~PositionController();

private:
    Cube *cube; /**< TODO */
    Level *level; /**< TODO */
    QMap<Vector3f*, GLint> *obstacleModelsList; /**< TODO */
    QTimer checkPositionTimer; /**< TODO */

    /**
     * @brief
     *
     */
    void checkPosition();
    /**
     * @brief
     *
     */
    void run();

signals:
    /**
     * @brief
     *
     */
    void collision();
    /**
     * @brief
     *
     */
    void levelCompleted();

};

#endif // POSITIONCONTROLLER_H
