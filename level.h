#ifndef LEVEL_H
#define LEVEL_H

#include <QThread>
#include <QImage>

#include <GL/gl.h>

#include "vector3f.h"
#include "obstacle.h"

class Level : public QThread
{
    Q_OBJECT

public:
    explicit Level(QMap<Vector3f, GLint> *_obstacleModelsList, QObject *parent = 0);
    explicit Level(GLint id, QObject *parent = 0);
    ~Level();

    GLint getId();
    QString getName();
    void setName(QString _name);
    bool getIsInStory();
    GLfloat getWidth();
    GLfloat getLength();
    GLfloat getGravity();
    QString getAmbientMusicFilename();

    void addObstacle(Obstacle *_obstacle);
    void deleteObstacle(GLint id);
    void moveObstacle(GLint id, Vector3f *newPosition);

    bool load(QString filename);
    bool save(QString filename);
    void draw();

private:
    GLint id;
    QString name;
    bool isInStory;
    QMap<Vector3f*, GLint> *obstacleModelsList;
    QMap<Obstacle*, GLfloat> *obstaclesList;
    GLint width;
    GLint length;
    GLfloat gravity;
    QString ambientMusicFilename;
    QImage *background;
};

#endif // LEVEL_H
