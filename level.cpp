#include "level.h"
#include "defines.h"

Level::Level(QObject *_parent) :
    parent(_parent),
    isLoaded(false)
{
}

Level::Level(QString _filename, QObject *_parent) :
    parent(_parent),
    filename(_filename),
    isLoaded(false)
{
}

Level::Level(QString _name, GLfloat _length, GLfloat _width, QObject *_parent) :
    parent(_parent),
    name(_name),
    length(_length),
    width(_width)
{
    // TODO: generate an id.
}

Level::~Level()
{
    for (QMultiMap<GLint,Obstacle*>::iterator i = obstaclesList.begin(); i != obstaclesList.end(); i++)
    {
        if (i.value() != NULL)
            dynamic_cast<Obstacle*>(i.value())->~Obstacle();
    }

    obstaclesList.~QMultiMap();
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
    Vector3f *cells = _obstacle->getPosition();

    Vector3f *bounding = getObstacleBoundingBox(_obstacle->getModelId());

    Vector3f *position = new Vector3f();
    position->x =  (bounding->x / 2.0f) + (cells->x * 3.0f) - (width / 2.0f);
    position->y =  (bounding->y / 2.0f) + (cells->y * 3.0f) + (LEVEL_HEIGHT / 2.0f);
    position->z = -(bounding->z / 2.0f) - (cells->z * 3.0f) + (length / 2.0f);

    _obstacle->setPosition(position);
    tempObstaclesList.insert(cells->z, _obstacle);
}

void Level::deleteObstacle(GLint _id)
{
    Obstacle *obstacle;
    for (QMultiMap<GLint,Obstacle*>::iterator i = obstaclesList.begin(); i != obstaclesList.end(); i++)
    {
        obstacle = dynamic_cast<Obstacle*>(i.value());
        if (obstacle->getId() == _id)
        {
            obstacle->~Obstacle();
            obstaclesList.erase(i);
            break;
        }
    }
}

void Level::moveObstacle(GLint _id, Vector3f *newPosition)
{
    Obstacle *obstacle;
    for (QMultiMap<GLint,Obstacle*>::iterator i = obstaclesList.begin(); i != obstaclesList.end(); i++)
    {
        obstacle = dynamic_cast<Obstacle*>(i.value());
        if (obstacle->getId() == _id)
        {
            obstacle->setPosition(newPosition);
            break;
        }
    }
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
    for (QMultiMap<GLint,Obstacle*>::iterator i = tempObstaclesList.begin(); i != tempObstaclesList.end(); i++)
        obstaclesList.insert(i.key(),i.value());
    tempObstaclesList.clear();
    return true;
}

GLvoid Level::draw(GLboolean simplifyForPicking)
{
    glPushName(LEVEL);
    drawPrism(width, LEVEL_HEIGHT, length);
    glPopName();

    glPushName(OBSTACLES);
    for (QMultiMap<GLint,Obstacle*>::iterator i = obstaclesList.begin(); i != obstaclesList.end(); i++)
        dynamic_cast<Obstacle*>(i.value())->draw(simplifyForPicking);
    for (QMultiMap<GLint,Obstacle*>::iterator i = tempObstaclesList.begin(); i != tempObstaclesList.end(); i++)
        dynamic_cast<Obstacle*>(i.value())->draw(simplifyForPicking);
    glPopName();
}

GLint Level::getObstacleListCount()
{
    return obstaclesList.count();
}

GLvoid Level::clearObstaclesList()
{
    obstaclesList.clear();
}

GLvoid Level::clearTempObstaclesList()
{
    tempObstaclesList.clear();
}
