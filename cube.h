#ifndef CUBE_H
#define CUBE_H

//#include <QtOpenGL>
//#include <QTimer>
//#include <QKeyEvent>

#include "level.h"
#include "skin.h"
#include "vector3f.h"

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
