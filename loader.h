#ifndef LOADER_H
#define LOADER_H

#include <QThread>
#include <QImage>

#include <GL/gl.h>

#include "vector3f.h"

class Loader : public QThread
{
    Q_OBJECT

public:
    explicit Loader(QObject *parent = 0);
    ~Loader();

    void setSkins(QMap<QImage*, GLint> &_skinsList);
    void setLevels(QMap<QString, GLint> &_levelsList);
    void setObstacleModels(QMap<Vector3f*, GLint> &_obstacleModelsList);
    void load();

private:
    QMap<QImage*, GLint> skinsList;
    QMap<QString, GLint> levelsList;
    QMap<Vector3f*, GLint> obstacleModelsList;
    void loadCustomSkins();
    void loadCustomLevels();
    void loadCustomObstacles();
    void run();

signals:
    void skinsLoaded();
    void levelsLoaded();
    void obstacleModelsLoaded();

};

#endif // LOADER_H
