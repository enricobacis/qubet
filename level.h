#ifndef LEVEL_H
#define LEVEL_H

#include <QImage>
#include <QMap>
#include <QtOpenGL>

#include "vector3f.h"
#include "obstacle.h"


/**
 * @brief
 *
 */
class Level : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param _obstacleModelsList
     * @param parent
     */
    explicit Level(QMap<GLint,Vector3f*> &_obstacleModelsList, QObject *parent = 0);

    /**
     * @brief
     *
     * @param id
     * @param parent
     */
    explicit Level(GLint id, QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~Level();

    /**
     * @brief
     *
     */
    GLint getId();

    /**
     * @brief
     *
     */
    QString getName();

    /**
     * @brief
     *
     * @param _name
     */
    void setName(QString _name);

    /**
     * @brief
     *
     */
    bool getIsInStory();

    /**
     * @brief
     *
     */
    GLfloat getWidth();

    /**
     * @brief
     *
     */
    GLfloat getLength();

    /**
     * @brief
     *
     */
    GLfloat getGravity();

    /**
     * @brief
     *
     */
    QString getAmbientMusicFilename();

    /**
     * @brief
     *
     * @param _obstacle
     */
    void addObstacle(Obstacle *_obstacle);

    /**
     * @brief
     *
     * @param id
     */
    void deleteObstacle(GLint id);

    /**
     * @brief
     *
     * @param id
     * @param newPosition
     */
    void moveObstacle(GLint id, Vector3f *newPosition);

    /**
     * @brief
     *
     * @param filename
     */
    bool load(QString filename);

    /**
     * @brief
     *
     * @param filename
     */
    bool save(QString filename);

    /**
     * @brief
     *
     */
    void draw();

private:
    GLint id; /**< TODO */
    QString name; /**< TODO */
    bool isInStory; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    QMap<GLint,Obstacle*> obstaclesList; /**< TODO */
    GLint width; /**< TODO */
    GLint length; /**< TODO */
    GLfloat gravity; /**< TODO */
    QString ambientMusicFilename; /**< TODO */
    QImage *background; /**< TODO */
};

#endif // LEVEL_H
