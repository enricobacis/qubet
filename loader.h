#ifndef LOADER_H
#define LOADER_H

#include <QThread>
#include <QImage>
#include <QMap>

#include <GL/gl.h>

#include "vector3f.h"

/**
 * @brief Loader class used to load skins, levels and obstacles in Qubet.
 */
class Loader : public QThread
{
    Q_OBJECT

public:

    /**
     * @brief Create a Loader Object to load skins, levels and obstacles in Qubet.
     *
     * @param _skinsList is the reference to Qubet's skinsList.
     * @param _obstacleModelsList is the reference to Qubet's obstacleModelsList.
     * @param _levelsList is the reference to Qubet's levelsList.
     * @param parent is the pointer to Qubet.
     */
    explicit Loader(QMap<GLint,QImage*> &_skinsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,QString> &_levelsList, QObject *parent = 0);

    /**
     * @brief Destroy a Loader object (for what it worths)
     */
    ~Loader();

    /**
     * @brief This is a duplicated of the Qthread's start() method.
     */
    void load();

private:
    QMap<GLint,QImage*> skinsList; /**< skinsList provided by Qubet object */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< obstacleModelsList provided by Qubet object */
    QMap<GLint,QString> levelsList; /**< levelsList provided by Qubet object */


    /**
     * @brief Load the skins from the resource file.
     */
    void loadSkins();

    /**
     * @brief Load custom skins from folder.
     */
    void loadCustomSkins();

    /**
     * @brief Load the obstacleModels from the resource file.
     */
    void loadObstacleModels();

    /**
     * @brief Load custom obstacleModels from folder.
     */
    void loadCustomObstacleModels();

    /**
     * @brief Load the levels from the resource file.
     */
    void loadLevels();

    /**
     * @brief Load custom levels from folder.
     */
    void loadCustomLevels();

    /**
     * @brief Re-implementation of the Qthread's run method. It calls the loading methods.
     */
    void run();

signals:
    /**
     * @brief Signal emitted when the loading process for the skins has ended.
     */
    void skinsLoaded();

    /**
     * @brief Signal emitted when the loading process for the levels has ended.
     */
    void levelsLoaded();

    /**
     * @brief Signal emitted when the loading process for the obstaclesModels has ended.
     */
    void obstacleModelsLoaded();

    /**
     * @brief Signal emitted when something in the loading process goes wrong.
     */
    void errorLoading();

};

#endif // LOADER_H
