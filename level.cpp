#include "level.h"

Level::Level(QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *_parent) :
    parent(_parent),
    isLoaded(false),
    obstacleModelsList(_obstacleModelsList)
{
}

Level::Level(GLint _id, QString _filename, QObject *_parent) :
    parent(_parent),
    id(_id),
    filename(_filename),
    isLoaded(false)
{
}

Level::~Level()
{

}

GLint Level::getId()
{
    return id;
}

QString Level::getFilename()
{
    return filename;
}

void Level::setFilename(QString _filename)
{
    filename = _filename;
}

QString Level::getName()
{
    return name;
}

void Level::setName(QString _name)
{
    name = _name;
}

bool Level::getIsInStory()
{
    return isInStory;
}

GLfloat Level::getWidth()
{
    return width;
}

GLfloat Level::getLength()
{
    return length;
}

GLfloat Level::getGravity()
{
    return gravity;
}

QString Level::getAmbientMusicFilename()
{
    return ambientMusicFilename;
}

void Level::addObstacle(Obstacle *_obstacle)
{
    // TODO
}

void Level::deleteObstacle(GLint _id)
{
    // TODO
}

void Level::moveObstacle(GLint _id, Vector3f *newPosition)
{
    // TODO
}

bool Level::load()
{
    if (isLoaded)
        return true;

    // TODO
    return true;
}

bool Level::save()
{
    // TODO
}

void Level::draw()
{
    // TODO
}
