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

/**
 * @brief Draw a CubesButton using vertex and texture coordinates.
 *
 * @param label is the set of letter to assign at the button.
 * @param rotationAngles is the list that contain the letter's rotation angles.
 * @param name is the name (integer number) to assign to the first letter cube. Following Letters gets following names.
 */
GLvoid drawCubesButton(QString label, QVector<GLint> angles, GLint firstName);



#endif // UTILITIES_H
