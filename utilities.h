#ifndef UTILITIES_H
#define UTILITIES_H

#include "alphabet.h"

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


#endif // UTILITIES_H
