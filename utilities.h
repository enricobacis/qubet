#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtOpenGL>

/**
 * @brief Draw a XY Square using vertex and texture coordinates.
 *
 * @param x is the length of the x side.
 * @param y is the length of the y side.
 */
GLvoid drawRectangle(GLfloat x, GLfloat y);

/**
 * @brief Draw a XYZ Prism using vertex and texture coordinates.
 *
 * @param x is the length of the x side.
 * @param y is the length of the y side.
 * @param z is the length of the z side.
 */
GLvoid drawPrism(GLfloat x, GLfloat y, GLfloat z);

#endif // UTILITIES_H
