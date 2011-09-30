#ifndef CUBESTRING_H
#define CUBESTRING_H

//#include <QtOpenGL>

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
    explicit CubeString(QString _label, GLfloat _cubeDimension, GLuint _name, Alphabet *_alphabet);

    /**
     * @brief
     *
     * @param _label
     * @param _maxWidth
     * @param _maxHeight
     * @param _name
     * @param _alphabet
     */
    explicit CubeString(QString _label, GLfloat _maxWidth, GLfloat _maxHeight, GLuint _name, Alphabet *_alphabet);

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
     */
    GLuint getName();

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
    GLvoid startStringRotation(GLint _angleStep, GLint _turns);

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
     * @return [GLfloat] the angle the next letter after this string should have using the :nextLetterDelta.
     */
    GLfloat setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta = 0);


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

    /**
     * @brief
     *
     */
    GLvoid init();

};

#endif // CUBESTRING_H
