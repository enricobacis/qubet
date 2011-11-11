#include "level.h"
#include "defines.h"

#include <QDomElement>

Level::Level(QString _filename, QObject *_parent) :
    parent(_parent),
    filename(_filename),
    currentObstacleId(0)
{
    name = "not yet loaded";
}

Level::Level(QString _name, GLfloat _length, GLfloat _width, QObject *_parent) :
    parent(_parent),
    name(_name),
    isInStory(false),
    length(_length),
    width(_width),
    currentObstacleId(0)
{
    filename = name + ".xml";
    filename.replace(" ", "_");
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

void Level::setIsInStory(bool _isInStory)
{
    isInStory = _isInStory;
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

GLvoid Level::setGravity(GLfloat _gravity)
{
    gravity = _gravity;
}

QString Level::getAmbientMusicFilename()
{
    return ambientMusicFilename;
}

QString Level::getSkyboxName()
{
    return skyboxName;
}

void Level::addObstacle(Obstacle *_obstacle)
{
    Vector3f *cells = _obstacle->getPosition();
    Vector3f *position = obstacleCellToPosition(cells, _obstacle->getModelId());

    _obstacle->setPosition(position);
    _obstacle->setId(++currentObstacleId);
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
    QDomDocument document(filename);
    QFile file("resources/levels/xml/" + filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }

    file.close();

    QDomElement levelElement = document.documentElement();
    name = levelElement.attribute("name", "no name");
    width = levelElement.attribute("width", QString::number(LEVEL_WIDTH_DEFAULT)).toInt();
    length = levelElement.attribute("length", QString::number(LEVEL_LENGTH_DEFAULT)).toInt();
    gravity = levelElement.attribute("gravity", QString::number(LEVEL_GRAVITY_DEFAULT)).toInt();
    ambientMusicFilename = levelElement.attribute("music", "game_" + QString::number((qrand() % 2) + 1) + ".mp3");
    skyboxName = levelElement.attribute("skybox", "nebula");

    QDomElement obstacleElement = levelElement.firstChildElement("obstacle");

    while(!obstacleElement.isNull())
    {
        GLint modelId = obstacleElement.attribute("model", "1").toInt();

        GLint zCell = obstacleElement.attribute("z", "0").toInt();
        Vector3f *cells = new Vector3f(obstacleElement.attribute("x", "0").toInt(),
                                       obstacleElement.attribute("y", "0").toInt(),
                                       zCell);

        Vector3f *position = obstacleCellToPosition(cells, modelId);
        Obstacle *obstacle = new Obstacle(modelId, position);

        GLint obstacleId = obstacleElement.attribute("id", "1").toInt();
        obstacle->setId(obstacleId);

        if (obstacleId > currentObstacleId)
            currentObstacleId = obstacleId;

        obstacle->setType(1);

        obstaclesList.insert(zCell, obstacle);
        obstacleElement = obstacleElement.nextSiblingElement("obstacle");
    }

    return true;
}

bool Level::save(bool *newlyCreated)
{
    for (QMultiMap<GLint,Obstacle*>::iterator i = tempObstaclesList.begin(); i != tempObstaclesList.end(); i++)
        obstaclesList.insert(i.key(),i.value());
    tempObstaclesList.clear();

    QDomDocument document;

    QDomElement levelElement = document.createElement("level");
    levelElement.setAttribute("name", name);
    levelElement.setAttribute("width", width);
    levelElement.setAttribute("length", length);
    levelElement.setAttribute("gravity", gravity);
    document.appendChild(levelElement);

    Obstacle *obstacle = NULL;
    Vector3f *cells = NULL;

    for (QMultiMap<GLint,Obstacle*>::iterator i = obstaclesList.begin(); i != obstaclesList.end(); i++)
    {
        obstacle = dynamic_cast<Obstacle*>(i.value());
        QDomElement obstacleElement = document.createElement("obstacle");
        cells = obstaclePositionToCell(obstacle->getPosition(), obstacle->getModelId());
        obstacleElement.setAttribute("id", obstacle->getId());
        obstacleElement.setAttribute("model", obstacle->getModelId());
        obstacleElement.setAttribute("x", cells->x);
        obstacleElement.setAttribute("y", cells->y);
        obstacleElement.setAttribute("z", cells->z);
        levelElement.appendChild(obstacleElement);
    }

    QFile file("resources/levels/xml/" + filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        document.save(stream, 4);
        file.close();
    }
    else
    {
        return false;
    }

    if (!isInStory)
    {
        QDomDocument levels("levels");
        QFile levelsFile("resources/levels/levels.xml");
        if (!levelsFile.open(QIODevice::ReadOnly))
            return false;

        if (!levels.setContent(&levelsFile))
        {
            levelsFile.close();
            return false;
        }

        levelsFile.close();

        QDomElement rootElement = levels.documentElement();
        QDomElement levelElement = rootElement.firstChildElement("level");

        bool found = false;
        while (!levelElement.isNull())
        {
            if (levelElement.attribute("name") == name)
            {
                found = true;
                break;
            }

            levelElement = levelElement.nextSiblingElement("level");
        }

        if (newlyCreated != NULL)
            *newlyCreated = !found;

        if (!found)
        {
            levelElement = levels.createElement("level");
            levelElement.setAttribute("filename", filename);
            levelElement.setAttribute("name", name);
            rootElement.appendChild(levelElement);

            QFile levelsFileWrite("resources/levels/levels.xml");
            if (levelsFileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                QTextStream stream(&levelsFileWrite);
                levels.save(stream, 4);
                levelsFileWrite.close();
            }
            else
            {
                return false;
            }
        }
    }

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
    clearTempObstaclesList();
}

GLvoid Level::clearTempObstaclesList()
{
    tempObstaclesList.clear();
}

Vector3f *Level::obstacleCellToPosition(Vector3f *cells, GLuint obstacleModelId)
{
    Vector3f *bounding = getObstacleBoundingBox(obstacleModelId);
    Vector3f *position = new Vector3f();

    position->x =  (bounding->x / 2.0f) + (cells->x * 3.0f) - (width / 2.0f);
    position->y =  (bounding->y / 2.0f) + (cells->y * 3.0f) + (LEVEL_HEIGHT / 2.0f);
    position->z = -(bounding->z / 2.0f) - (cells->z * 3.0f) + (length / 2.0f);

    return position;
}

Vector3f *Level::obstaclePositionToCell(Vector3f *position, GLuint obstacleModelId)
{
    Vector3f *bounding = getObstacleBoundingBox(obstacleModelId);
    Vector3f *cells = new Vector3f();

    cells->x = (int)(( position->x -(bounding->x / 2.0f) + (width / 2.0f)) / 3);
    cells->y = (int)(( position->y -(bounding->y / 2.0f) - (LEVEL_HEIGHT / 2.0f)) / 3);
    cells->z = (int)((-position->z -(bounding->z / 2.0f) + (length / 2.0f)) / 3);

    return cells;
}
