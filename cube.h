#ifndef CUBE_H
#define CUBE_H

#include <QImage>
#include <QKeyEvent>
#include <QTimer>
#include <QGLWidget>

#include <GL/gl.h>

#include "vector3f.h"
#include "level.h"

/**
 * @brief
 *
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
    explicit Cube(Level *_level, QImage *_skin, QObject *_parent = 0);

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
    QImage *skin; /**< TODO */
    QObject *parent; /**< TODO */
    Vector3f *position; /**< TODO */
    GLint state; /**< TODO */
    GLint moving; /**< TODO */
    GLfloat speed; /**< TODO */
    GLfloat gravity; /**< TODO */
    GLfloat scaleFactor; /**< TODO */
    GLfloat jumpStartTime; /**< TODO */

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
