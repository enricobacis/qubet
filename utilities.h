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
 * @param repeat is to repeat the texture. [default = false]
 */
GLvoid drawRectangle(GLfloat x, GLfloat y, GLuint texture = 0, bool repeat = false);

/**
 * @brief Draw a XYZ Prism using vertex and texture coordinates, using a skin.
 *
 * @param x is the length of the x side.
 * @param y is the length of the y side.
 * @param z is the length of the z side.
 * @param skin is the Skin* of textures [default NULL].
 * @param it is used for the Letter cubes [default false].
 * @param repeat is to repeat the texture. [default = false]
 */
GLvoid drawPrism(GLfloat x, GLfloat y, GLfloat z, Skin *skin = NULL, bool invertBackTexture = false, bool repeat = false);

/**
 * @brief Set the repetition of the texture.
 *
 * @param repeat true to repeat, false to clamp
 */
GLvoid setTextureRepeat(bool repeat);

/**
 * @brief draw in (0,0,0) an obstacle with id id.
 *
 * @param id is the obstacle id.
*/
GLvoid drawObstacle(GLuint id);

/**
 * @brief returns the modelView coordinates from Projection coordinates.
 *
 * @param vect is the vector of Projection coordinates.
 * @param computeZDepth is set to true if you want to compute the foreground object z, else false.
 *
 * @returns the ModelView coordinates from projection coordinates.
 */
Vector3f *getModelViewPos(Vector3f *vect, bool computeZDepth = false);

/**
 * @brief returns the Projection coordinates from modelView coordinates.
 *
 * @param vect is the vector of ModelView coordinates.
 *
 * @returns the Projection coordinates from ModelView coordinates.
 */
Vector3f *getProjectionPos(Vector3f *vect);

/**
 * @brief Returns the specified by t coordinates of a parametric line.
 *
 * @param p0 is the first point of a line.
 * @param p1 is the second point of a line.
 * @param t is the parametric variable.
 *
 * @returns the specified by t coordinates of a parametric line.
 */
Vector3f *getPointFromParametricLine(Vector3f *p0, Vector3f *p1, GLfloat t);

/**
 * @brief returns the Obstacle boundingBox lenghts.
 *
 * @param id is the id of the Obstacle.
 *
 * @returns the Obstacle boundingBox lenghts.
*/
Vector3f *getObstacleBoundingBox(GLuint id);

/**
 * @brief This function set the colorEmissive value.
 *
 * @param color is the color to set.
 */
GLvoid setMaterialColor(int color);

/**
 * @brief This function set the colorEmissive value.
 *
 * @param color is the color to set.
 */
GLvoid setMaterialColor(QColor color);

/**
 * @brief Convert the cell coordinates occupied by the obstacle to absolute position.
 *
 * @param cell is the Vector3f of cells coordinates.
 * @param obstacleModelId is the modelID of the obstacle.
 *
 * @returns the absolute position of the obstacle.
 */
Vector3f *obstacleCellToPosition(Vector3f *cell, GLuint obstacleModelId);

/**
 * @brief Convert the absolute position of an obstacle to the cell coordinates.
 *
 * @param position is the absolute position of the obstacle.
 * @param obstacleModelId is the modelID of the obstacle.
 *
 * @returns the cell coordinates of the obstacle.
 */
Vector3f *obstaclePositionToCell(Vector3f *position, GLuint obstacleModelId);

#endif // UTILITIES_H
