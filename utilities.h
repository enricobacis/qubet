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
 * @brief
 *
 * @param vect
 * @param computeZDepth
 */
Vector3f* getModelViewPos(Vector3f *vect, bool computeZDepth = false);

/**
 * @brief
 *
 * @param vect
 */
Vector3f* getProjectionPos(Vector3f *vect);

/**
 * @brief
 *
 * @param p0
 * @param p1
 * @param t
 */
Vector3f* getPointFromParametricLine(Vector3f* p0, Vector3f* p1, GLfloat t);

#endif // UTILITIES_H
