#ifndef POSITIONCONTROLLER_H
#define POSITIONCONTROLLER_H

#include <QThread>
#include "cube.h"
#include "level.h"
#include "vector3f.h"

#include <GL/gl.h>

class PositionController : public QThread
{
    Q_OBJECT

public:
    explicit PositionController(Cube *_cube, Level *_level, QMap<Vector3f*, GLint> *_obstacleModelsList, QObject *parent = 0);
    ~PositionController();

private:
    Cube *cube;
    Level *level;
    QMap<Vector3f*, GLint> *obstacleModelsList;
    QTimer checkPositionTimer;

    void checkPosition();
    void run();

signals:
    void collision();
    void levelCompleted();

};

#endif // POSITIONCONTROLLER_H
