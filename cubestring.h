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
     * @param _angleStep
     * @param _turns
     */
    GLvoid startLettersRotation(GLint _angleStep, GLint _turns);

    /**
     * @brief
     *
     * @param _letterName
     */
    GLboolean isRotating(GLuint _letterName);

    /**
     * @brief Set the current angle for letters in the CubeString.
     *
     * @param _nextLetterDelta is the delta you want to apply from letter to letter angle. [default 0]
     *
     * @return [GLint] the angle the next letter after this string should have using the :nextLetterDelta.
     */
    GLint setCurrentAngle(GLint _firstLetterAngle, GLint _nextLetterDelta = 0);


private:

    QString label; /**< TODO */
    GLfloat cubeDimension; /**< TODO */
    GLint length; /**< TODO */
    GLuint name; /**< TODO */
    Alphabet *alphabet; /**< TODO */

    QList<GLint> angleSteps; /**< TODO */
    QList<GLint> currentAngles;  /**< TODO */
    QList<GLint> finalAngles; /**< TODO */
    QList<GLuint> letterDisplayLists; /**< TODO */

    /**
     * @brief
     *
     * @param _letter
     */
    GLuint createLetterDisplayList(QChar _letter);

    /**
     * @brief
     *
     * @param _skin
     */
    GLuint createLetterDisplayList(Skin *_skin);

};

#endif // CUBESTRING_H
