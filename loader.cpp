#include "loader.h"

Loader::Loader(QMap<GLint,QImage*> &_skinsList, QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,QString> &_levelsList, QObject *parent) :
    skinsList(_skinsList),
    obstacleModelsList(_obstacleModelsList),
    levelsList(_levelsList)
{
}

Loader::~Loader()
{
}

void Loader::load()
{
    start();
}

void Loader::loadSkins()
{
    // TODO
    loadCustomSkins();

    emit skinsLoaded();
}

void Loader::loadCustomSkins()
{
    // future implementation
}

void Loader::loadObstacleModels()
{
    // TODO
    loadCustomObstacleModels();

    emit obstacleModelsLoaded();
}

void Loader::loadCustomObstacleModels()
{
    // future implementation
}

void Loader::loadLevels()
{
    // TODO
    loadCustomLevels();

    emit levelsLoaded();
}

void Loader::loadCustomLevels()
{
    // future implementation
}

void Loader::run()
{
    try
    {
        loadSkins();
        loadLevels();
        loadObstacleModels();
    }
    catch (...)
    {
        emit errorLoading();
    }

}

