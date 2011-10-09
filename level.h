#ifndef LEVEL_H
#define LEVEL_H

#include "obstacle.h"
#include "skybox.h"

/**
 * @brief This class rapresents a Level of Qubet, with its obstacle.
 *        It is able to draw itself simply using the draw function.
 *        It can also load the xml description file and parse it.
 *
 * @version 1.0
 * @author \#34
 */
class Level : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Creates an empty Level. It is only used to test purposes.
     *
     * @param _parent is the parent of the Level.
     */
    explicit Level(QObject *_parent = 0);

    /**
     * @brief Creates a level from an id, a name, a length and a width.
     *        It is used to create a new Level from the LevelEditor.
     *
     * @param _id is the id of the Level.
     * @param _name is the name of the Level.
     * @param _length is the length of the Level.
     * @param _width is the width of the Level.
     * @param _parent is the parent of the Level.
    */
    explicit Level(QString _name, GLfloat _length, GLfloat _width, QObject *_parent = 0);

    /**
     * @brief Creates a Level from a filename.
     *        It is used in the Loader.
     *
     * @param _filename is the filename to load.
     * @param _parent is the parent of the Level.
     */
    explicit Level(QString _filename, QObject *_parent = 0);

    /**
     * @brief Safely destroies a Level instance.
     */
    ~Level();

    /**
     * @brief Returns the id of the Level.
     *
     * @return the id of the Level.
     */
    GLint getId();

    /**
     * @brief Returns the filename of the Level.
     *
     * @return the filename of the Level.
     */
    QString getFilename();

    /**
     * @brief Set the Level filename.
     *
     * @param _filename is the filename to set.
     */
    void setFilename(QString _filename);

    /**
     * @brief Returns the name of the Level.
     *
     * @return the name of the Level.
     */
    QString getName();

    /**
     * @brief Set the name of the Level.
     *
     * @param _name is the name to set.
     */
    void setName(QString _name);

    /**
     * @brief Returns the a variable that states if the Level is in the story.
     *
     * @return true if the Level is in the story, false elsewhere.
     */
    bool getIsInStory();

    /**
     * @brief Returns the width of the Level.
     *
     * @return the width of the Level.
     */
    GLfloat getWidth();

    /**
     * @brief Returns the length of the Level.
     *
     * @return the length of the Level.
     */
    GLfloat getLength();

    /**
     * @brief Returns the gravity of the Level.
     *
     * @return the gravity of the Level.
     */
    GLfloat getGravity();

    /**
     * @brief Returns the ambient Music Filename.
     *
     * @return the ambientMusicFilename.
     */
    QString getAmbientMusicFilename();

    /**
     * @brief Adds an obstacle to the Level.
     *
     * @param _obstacle is the obstacle to add.
     */
    void addObstacle(Obstacle *_obstacle);

    /**
     * @brief Deletes an obstacle.
     *
     * @param _id is the obstacle id.
     */
    void deleteObstacle(GLint _id);

    /**
     * @brief Moves an obstacle to a new position.
     *
     * @param _id is the id of the obstacle to move.
     * @param newPosition is the new position.
     */
    void moveObstacle(GLint _id, Vector3f *newPosition);

    /**
     * @brief Loads the Level from xml form using the filename as input.
     */
    bool load();

    /**
     * @brief Saves the Level in a xml form using the filename as output.
     */
    bool save();

    /**
     * @brief Draws the Level and its obstacles.
     *
     * @param simplifyForPicking is used to state if you want to draw it simplified.
     */
    GLvoid draw(GLboolean simplifyForPicking);

    /**
     * @brief Returns the number of obstacles in the level.
     *
     * @return the number of obstacles in the level.
    */
    GLint getObstacleListCount();

    /**
     * @brief Returns the number of obstacles in the level.
     *
     * @return the number of obstacles in the level.
    */
    GLvoid clearObstaclesList();


private:

    QObject *parent; /**< It is the parent of Level.  */
    GLint id; /**< It is the Level id. */
    QString filename; /**< It is the Level xml description filename. */
    QString name; /**< It is the Level name. */
    bool isLoaded; /**< Is is the variable that states if the Level is fully loaded. */
    bool isInStory; /**< It is the variable that states if the Level is in the story. */
    QMultiMap<GLint,Obstacle*> obstaclesList; /**< It is the Level multiMap of obstacles. */
    GLint length; /**< It is the Level length. */
    GLint width; /**< It is the Level width. */
    GLfloat gravity; /**< It is the Level gravity. */
    QString ambientMusicFilename; /**< It is the Level ambient music filename. */
};

#endif // LEVEL_H
