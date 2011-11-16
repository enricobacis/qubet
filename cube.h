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

    GLint getSideLength();

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

    void moveLeft();

    void moveRight();

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


private:
    Skin *skin; /**< It is the Skin of the Cube. */
    QObject *parent; /**< It is the Parent of the Cube. */
    Vector3f *position; /**< It is the Cube's current position. */
    unsigned char state; /**< It is the state of the cube. */
    GLuint sideLength;  /**< It is the side of the Cube. */
    GLfloat speed; /**< It is the current speed of the Cube. */
    GLfloat gravity; /**< It is the gravity variable. */
    GLint levelCellsLength;
    GLint levelCellsWidth;
    GLfloat scaleFactor; /**< It is the scale factor. */
    GLfloat jumpStartTime; /**< It is the time the Cube has started the jump. */
    GLuint t;  /**< It is the parametric variable to put in the parametric functions. */
    Vector3f* normalsMatrix[4][4][4];  /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion. */

    void createNormalsMatrix();

    void explode();


private slots:

    /**
     * @brief It is the slot invoked when the Cube collides with an Obstacle.
     */
    void collided();

    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *event);


signals:

    /**
     * @brief
     *
     */
    void levelCompleted();

    /**
     * @brief Signal emitted to play an effect.
     *
     * @param effectName is the name of the effect to play.
     */
    void playEffect(QString effectName);

};

#endif // CUBE_H
