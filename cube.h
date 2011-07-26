#ifndef CUBE_H
#define CUBE_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>
#include <QTimer>

#include <GL/gl.h>

#include "vector3f.h"
#include "level.h"

class Cube : public QThread
{
    Q_OBJECT

public:
    explicit Cube(Level *_level, QImage *_skin, QObject *parent = 0);
    ~Cube();

    Vector3f getPosition();
    void setPosition(Vector3f _position);
    void jump();
    void draw();
    void updatePosition();
    void start();

private:
    Level *level;
    QImage *skin;
    Vector3f position;
    GLint state;
    GLint moving;
    GLfloat jumpStartTime;
    QTimer updatePositionTimer;

    void run();

private slots:
    void collided();
    void levelCompleted();
    void keyPressed(QKeyEvent *e);
    void pauseGame();
    void continueGame();
};

#endif // CUBE_H
