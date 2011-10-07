#include "level.h"

Level::Level(QObject *_parent) :
    parent(_parent),
    isLoaded(false)
{
}

Level::Level(GLint _id, QString _filename, QObject *_parent) :
    parent(_parent),
    id(_id),
    filename(_filename),
    isLoaded(false)
{
}
Level::Level(GLint _id, QString _levelName, GLfloat _length, GLfloat _width)
{
    length = _length;
    width = _width;
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
    obstaclesList.insert(obstaclesList.count(), _obstacle);
}

void Level::deleteObstacle(GLint _id)
{
    obstaclesList.remove(_id);
}

void Level::moveObstacle(GLint _id, Vector3f *newPosition)
{
    obstaclesList[_id][1].setPosition(newPosition);
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

GLvoid Level::draw(GLboolean simplifyForPicking)
{
    drawPrism(width, 0.2f, length);

    QMap<GLint,Obstacle*>::const_iterator i = obstaclesList.constBegin();
     while (i != obstaclesList.constEnd())
     {
        i.value()->draw(simplifyForPicking);
        i++;
    }
}

GLint Level::getObstacleListCount()
{
    return obstaclesList.count();
}
