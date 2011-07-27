#ifndef CUBE_H
#define CUBE_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>
#include <QTimer>

#include <GL/gl.h>

#include "vector3f.h"
#include "level.h"

/**
 * @brief
 *
 */
class Cube : public QThread
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
    explicit Cube(Level *_level, QImage *_skin, QObject *parent = 0);
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
    Vector3f *position; /**< TODO */
    GLint state; /**< TODO */
    GLint moving; /**< TODO */
    GLfloat speed; /**< TODO */
    GLfloat gravity; /**< TODO */
    GLfloat scaleFactor; /**< TODO */
    GLfloat jumpStartTime; /**< TODO */
    QTimer updatePositionTimer; /**< TODO */

    /**
     * @brief
     *
     */
    void run();

private slots:
    /**
     * @brief
     *
     */
    void collided();
    /**
     * @brief
     *
     */
    void levelCompleted();
    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *e);
    /**
     * @brief
     *
     */
    void pauseGame();
    /**
     * @brief
     *
     */
    void continueGame();

};

#endif // CUBE_H
