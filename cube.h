#ifndef CUBE_H
#define CUBE_H

#include "level.h"
#include "skin.h"

/**
 * @brief This class rapresents the player's Cube.
 *
 * @version 1.0
 * @author \#34
 */
class Cube : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create a Cube.
     *
     * @param _level is the Level in which the Cube lives.
     * @param _skin is the skin of the Cube.
     * @param _parent is the parent of the Cube.
     */
    explicit Cube(Level *_level, Skin *_skin, QObject *_parent = 0);

    /**
     * @brief Safely destroy a Cube object.
     */
    ~Cube();

    /**
     * @brief Returns the position of the Cube.
     *
     * @returns the position of the Cube.
     */
    Vector3f *getPosition();

    /**
     * @brief Set the position of the Cube.
     *
     * @param _position is the position to set.
     */
    void setPosition(Vector3f *_position);

    /**
     * @brief Make the Cube jump.
     */
    void jump();

    /**
     * @brief Returns true if the Cube is moving, else false.
     *
     * @returns true if the Cube is moving, else false.
     */
    bool isMoving();

    /**
     * @brief Make the Cube move to the Left.
     */
    void moveLeft();

    /**
     * @brief Make the Cube move to the right.
     */
    void moveRight();

    /**
     * @brief Draw the Cube.
     */
    void draw();

    /**
     * @brief Update the position of the Cube.
     */
    void updatePosition();


private:
    Skin *skin; /**< It is the Skin of the Cube. */
    QObject *parent; /**< It is the Parent of the Cube. */
    Vector3f *position; /**< It is the Cube's current position. */
    unsigned char state; /**< It is the state of the cube. */
    GLfloat speed; /**< It is the current speed of the Cube. */
    GLfloat gravity; /**< It is the gravity variable. */
    GLint levelCellsLength; /**< It is the number of cells of the Level's length. */
    GLint levelCellsWidth; /**< It is the number of cells of the Level's width. */
    GLfloat scaleFactor; /**< It is the scale factor. */
    GLfloat jumpStartTime; /**< It is the time the Cube has started the jump. */
    GLuint jumpParameter; /**< It is the parametric variable to put in the jump parametric functions. */
    GLfloat jumpVelocity;  /**< It is the velocity of the jump. */
    GLuint movingParameter;  /**< It is the parametric variable to put in the moving parametric functions */
    GLuint t; /**< TODO */
    Vector3f* normalsMatrix[4][4][4]; /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion. */

    /**
     * @brief Generate the normalsMatrix Matrix.
     */
    void createNormalsMatrix();

    /**
     * @brief Make the Cube explode.
     */
    void explode();


private slots:

    /**
     * @brief It is the slot invoked when the Cube collides with an Obstacle.
     */
    void collided();

    /**
     * @brief Slot invoked when the user presses a key on the keyboard.
     *
     * @param event is the QKeyEvent*.
     */
    void keyPressed(QKeyEvent *event);


signals:

    /**
     * @brief Signal emitted when the level is completed.
     */
    void levelCompleted();

    /**
     * @brief Signal emitted to play an effect.
     *
     * @param effectName is the name of the effect to play.
     */
    void playEffect(QString effectName);

};

#endif // CUBE_H
