#ifndef UTILITIES_H
#define UTILITIES_H

#include "alphabet.h"
#include "vector3f.h"

/**
 * @brief Draw a XY Square using vertex and texture coordinates.
 *
 * @param x is the length of the x side.
 * @param y is the length of the y side.
 * @param texture is the GLuint textureID.
 */
GLvoid drawRectangle(GLfloat x, GLfloat y, GLuint texture = 0);

/**
 * @brief Draw a XYZ Prism using vertex and texture coordinates, using a skin.
 *
 * @param x is the length of the x side.
 * @param y is the length of the y side.
 * @param z is the length of the z side.
 * @param skin is the Skin* of textures [default NULL].
 * @param it is used for the Letter cubes [default false].
 */
GLvoid drawPrism(GLfloat x, GLfloat y, GLfloat z, Skin *skin = NULL, GLboolean invertBackTexture = false);


/**
 * @brief draw in (0,0,0) an obstacle with id id.
 *
 * @param id is the obstacle id.
*/
GLvoid drawObstacle(GLuint id);

/**
 * @brief Returns the position of the point in the ModelView system from the
 *        window coordinates.
 *
 * @param x is the x coordinate of the window.
 * @param y is the y coordinate of the window.
 * @param z is the z for which you want to compute the point.
 *
 * @return the vector that rapresents the point in the ModelView System.
 */
Vector3f *getOGLPosition(GLfloat x, GLfloat y, GLfloat z);

/**
 * @brief Returns the position of the point in the ModelView system from the
 *        window coordinates. It uses the z of the foreground object.
 *
 * @param x is the x coordinate of the window.
 * @param y is the y coordinate of the window.
 *
 * @return the vector that rapresents the point in the ModelView System.
 */
Vector3f *getOGLPosition(GLfloat x, GLfloat y);

#endif // UTILITIES_H
