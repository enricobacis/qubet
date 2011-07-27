#ifndef LOADER_H
#define LOADER_H

#include <QThread>
#include <QImage>

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
     * @param parent
     */
    explicit Loader(QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~Loader();

    /**
     * @brief
     *
     * @param
     * @param _skinsList
     */
    void setSkins(QMap<QImage*, GLint> &_skinsList);
    /**
     * @brief
     *
     * @param QMap<QString
     * @param _levelsList
     */
    void setLevels(QMap<QString, GLint> &_levelsList);
    /**
     * @brief
     *
     * @param
     * @param _obstacleModelsList
     */
    void setObstacleModels(QMap<Vector3f*, GLint> &_obstacleModelsList);
    /**
     * @brief
     *
     */
    void load();

private:
    QMap<QImage*, GLint> skinsList; /**< TODO */
    QMap<QString, GLint> levelsList; /**< TODO */
    QMap<Vector3f*, GLint> obstacleModelsList; /**< TODO */
    /**
     * @brief
     *
     */
    void loadCustomSkins();
    /**
     * @brief
     *
     */
    void loadCustomLevels();
    /**
     * @brief
     *
     */
    void loadCustomObstacles();
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

};

#endif // LOADER_H
