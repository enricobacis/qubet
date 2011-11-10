#ifndef CUBE_H
#define CUBE_H

#include "level.h"
#include "skin.h"

/**
 * @brief
 *
 * @version 1.0
 * @author \#34
 */
class Cube : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief
     *
     * @param _level
     * @param _skin
     * @param parent
     */
    explicit Cube(Level *_level, Skin *_skin, QObject *_parent = 0);

    /**
     * @brief
     *
     */
    ~Cube();

    /**
     * @brief
     *
     */
    Vector3f *getPosition();

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
    void jump();

    /**
     * @brief
     *
     */
    void draw();

    /**
     * @brief
     *
     */
    void updatePosition();

    void createNormsMatrix();


private:
    Level *level; /**< It is the Level the Cube is in (to take parameters). */
    Skin *skin; /**< It is the Skin of the Cube. */
    QObject *parent; /**< It is the PArent of the Cube. */
    Vector3f *position; /**< It is the Cube's current position. */
    GLint state; /**< It is the state of the cube. */
    GLuint sideLength;  /**< It is the side of the Cube. */
    GLfloat speed; /**< It is the current speed of the Cube. */
    GLfloat gravity; /**< It is the gravity variable. */
    GLfloat scaleFactor; /**< It is the scale factor. */
    GLfloat jumpStartTime; /**< It is the time the Cube has started the jump. */
    GLuint t;  /**< It is the parametric variable to put in the parametric functions. */
    QVector<QVector<QVector<Vector3f*> > > normsMatrix;  /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion. */



private slots:

    /**
     * @brief It is the slot called when the Cube collides with an Obstacle.
     */
    void collided();

    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *e);


signals:

    /**
     * @brief
     *
     */
    void levelCompleted();

};

#endif // CUBE_H
