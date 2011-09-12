#include "level.h"

Level::Level(QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *parent)
{

}

Level::Level(GLint id, QObject *parent)
{

}

Level::~Level()
{

}

GLint Level::getId()
{

}

QString Level::getName()
{

}

void Level::setName(QString _name)
{

}

bool Level::getIsInStory()
{

}

GLfloat Level::getWidth()
{

}

GLfloat Level::getLength()
{

}

GLfloat Level::getGravity()
{

}

QString Level::getAmbientMusicFilename()
{

}

void Level::addObstacle(Obstacle *_obstacle)
{

}

void Level::deleteObstacle(GLint id)
{

}

void Level::moveObstacle(GLint id, Vector3f *newPosition)
{

}

bool Level::load(QString filename)
{

}

bool Level::save(QString filename)
{

}

void Level::draw()
{

}
