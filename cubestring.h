#ifndef CUBESTRING_H
#define CUBESTRING_H

#include <QtOpenGL>

#include "utilities.h"

/**
 * @brief
 *
 */
class CubeString
{

public:

    /**
     * @brief
     *
     * @param _label
     * @param _cubeDimension
     * @param _firstname
     * @param _alphabet
     */
    explicit CubeString(QString _label, GLfloat _cubeDimension, GLuint _firstname, Alphabet *_alphabet);

    /**
     * @brief
     *
     */
    ~CubeString();

    /**
     * @brief
     *
     * @param simplifyForPicking
     */
    GLvoid draw(GLboolean simplifyForPicking);

    /**
     * @brief
     *
     */
    QString getLabel();

    /**
     * @brief
     *
     * @param _letterName
     * @param _angleStep
     * @param _turns
     */
    GLvoid startLetterRotation(GLuint _letterName, GLint _angleStep, GLint _turns);

    /**
     * @brief
     *
     * @param _letterName
     */
    GLboolean isRotating(GLuint _letterName);


private:

    QString label; /**< TODO */
    GLfloat cubeDimension; /**< TODO */
    GLint length; /**< TODO */
    GLuint name; /**< TODO */
    Alphabet *alphabet; /**< TODO */

    QList<Skin*> skins; /**< TODO */
    QList<GLint> angleSteps; /**< TODO */
    QList<GLint> currentAngles;  /**< TODO */
    QList<GLint> finalAngles; /**< TODO */

};

#endif // CUBESTRING_H
