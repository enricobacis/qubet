//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
     * @param _explosionShader is the shader for the explosion.
     */
    explicit Cube(Level *_level, Skin *_skin, QObject *_parent = 0, QGLShaderProgram *_explosionShader = NULL);

    /**
     * @brief Safely destroy a Cube object.
     */
    ~Cube();

    /**
     * @brief Start the motion of the Cube;
     */
    void startCube();

    /**
     * @brief Stop the motion of the Cube.
     */
    void stopCube();

    /**
     * @brief Returns the position of the Cube.
     *
     * @returns the position of the Cube.
     */
    Vector3f *getPosition();

    /**
     * @brief Returns the Z of the Cube.
     *
     * @return the Z of the Cube.
     */
    GLfloat getZ();

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
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    void draw(GLboolean simplifyForPicking = false);

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
    GLint jumpStep; /**< It is the parameter of the jump. */
    GLint movingStep;  /**< It is the current moving step for to left and right. */
    GLint explosionStep; /**< It is the current explosion step. */
    GLint xCell; /**< It is the x cell the Cube is on. */
    Vector3f* normalsMatrix[4][4][4]; /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion. */
    Vector3f* anglesMatrix[4][4][4]; /**< It is the 3-dimensional matrix that contain the nomrs vector of each sub-cube in case of explosion. */
    GLint startXCell; /**< It is the starting x cell. */
    bool canMove; /**< States if the cube can move or not. */
    QGLShaderProgram *explosionShader; /**< It is the explosion Shader. */

    /**
     * @brief Generate the normalsMatrix Matrix.
     */
    void createNormalsMatrix();

    /**
     * @brief this function is called in the draw function in case of explosion.
    */
    void drawExplosion();

    /**
     * @brief Make the Cube explode.
     */
    void explode();

    /**
     * @brief Actions to perform when the level is completed.
     */
    void completed();

    /**
     * @brief Reset the Level.
     */
    void resetCube();


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
     * @brief Signal emitted when the player "suicide" the Cube.
     */
    void suicide();

    /**
     * @brief Signal to inform that the explosion has finished.
     */
    void explosionFinished();

    /**
     * @brief Signal to inform to hide the level name.
     */
    void hideLevelName();

    /**
     * @brief Signal emitted to play an effect.
     *
     * @param effectName is the name of the effect to play.
     */
    void playEffect(QString effectName);

};

#endif // CUBE_H
