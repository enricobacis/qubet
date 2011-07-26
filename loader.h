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

    void loadSkins(QMap<QImage, GLint> *skinsList);
    void loadLevels(QMap<QString, GLint> *levelsList);
    void loadObstacleModels(QMap<Vector3f, GLint> *obstacleModelsList);

private:
    void loadCustomSkins();
    void loadCustomLevels();
    void loadCustomObstacles();

signals:
    void skinsLoaded();
    void levelsLoaded();
    void obstacleModelsLoaded();

};

#endif // LOADER_H
