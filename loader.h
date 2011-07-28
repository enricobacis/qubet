#ifndef LOADER_H
#define LOADER_H

#include <QThread>
#include <QImage>
#include <QMap>

#include <GL/gl.h>

#include "vector3f.h"

/**
 * @brief
 *
 */
class Loader : public QThread
{
    Q_OBJECT

public:

    /**
     * @brief
     *
     * @param _skinsList
     * @param _obstacleModelsList
     * @param _levelsList
     * @param parent
     */
    explicit Loader(QMap<GLint,QImage*> &_skinsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,QString> &_levelsList, QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~Loader();

    /**
     * @brief
     *
     */
    void load();

private:
    QMap<GLint,QImage*> skinsList; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    QMap<GLint,QString> levelsList; /**< TODO */


    /**
     * @brief
     *
     */
    void loadSkins();

    /**
     * @brief
     *
     */
    void loadCustomSkins();

    /**
     * @brief
     *
     */
    void loadObstacleModels();

    /**
     * @brief
     *
     */
    void loadCustomObstacleModels();

    /**
     * @brief
     *
     */
    void loadLevels();

    /**
     * @brief
     *
     */
    void loadCustomLevels();

    /**
     * @brief
     *
     */
    void run();

signals:
    /**
     * @brief
     *
     */
    void skinsLoaded();

    /**
     * @brief
     *
     */
    void levelsLoaded();

    /**
     * @brief
     *
     */
    void obstacleModelsLoaded();

    /**
     * @brief
     *
     */
    void errorLoading();

};

#endif // LOADER_H
