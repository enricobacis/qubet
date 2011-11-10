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


private:
    Level *level; /**< TODO */
    Skin *skin; /**< TODO */
    QObject *parent; /**< TODO */
    Vector3f *position; /**< TODO */
    GLint state; /**< TODO */
    GLuint sideLength;  /**< TODO */
    GLfloat speed; /**< TODO */
    GLfloat gravity; /**< It is the gravity variable */
    GLfloat scaleFactor; /**< TODO */
    GLfloat jumpStartTime; /**< TODO */
    GLuint t;  /**< It is the parametric variable to put in the parametric functions */
    QVector<QVector<QVector<Vector3f*>>> normsMatrices;  /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion */



private slots:

    /**
     * @brief
     *
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
