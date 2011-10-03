#ifndef CUBESTRINGLIST_H
#define CUBESTRINGLIST_H

#include "cubestring.h"

/**
 * @brief
 *
 * @version 1.0
 * @author \#34
 */
class CubeStringList
{

public:

    /**
     * @brief
     *
     * @param _labels
     * @param _cubeDimension
     * @param _alphabet
     */
    explicit CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet);

    /**
     * @brief
     *
     * @param _labels
     * @param _maxWidth
     * @param _maxHeight
     * @param _alphabet
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     */
    explicit CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f);

    /**
     * @brief
     *
     * @param _labels
     * @param _cubeDimension
     * @param _alphabet
     * @param _name
     */
    explicit CubeStringList(QString _labels, GLfloat _cubeDimension, Alphabet *_alphabet, GLuint _name = 0);

    /**
     * @brief
     *
     * @param _labels
     * @param _maxWidth
     * @param _maxHeight
     * @param _alphabet
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     * @param _name
     */
    explicit CubeStringList(QString _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f, GLuint _name = 0);

    /**
     * @brief
     *
     */
    ~CubeStringList();

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
    GLint getLabelCount();

    /**
     * @brief
     *
     * @param _stringName
     */
    QString getLabel(GLuint _stringName);

    /**
     * @brief
     *
     * @param _stringName
     * @param _letterName
     * @param _angleStep
     * @param _turns
     */
    GLvoid startLetterRotation(GLuint _stringName, GLuint _letterName, GLint _angleStep, GLint _turns);

    /**
     * @brief
     *
     * @param _stringName
     * @param _angleStep
     * @param _turns
     */
    GLvoid startStringRotation(GLuint _stringName, GLint _angleStep, GLint _turns);

    /**
     * @brief
     *
     * @param _angleStep
     * @param _turns
     */
    GLvoid startStringListRotation(GLint _angleStep, GLint _turns);

    /**
     * @brief
     *
     * @param _stringName
     * @param _letterName
     */
    GLboolean isRotating(GLuint _stringName, GLuint _letterName);

    /**
     * @brief
     *
     * @param _firstLetterAngle
     * @param _nextLetterDelta
     */
    GLfloat setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta = 0.0f);


private:

    QList<CubeString*> cubeStrings; /**< TODO */
    GLuint name; /**< TODO */
    GLfloat interline; /**< TODO */
    GLfloat firstStringHeight; /**< TODO */
    GLfloat stringsHeightDelta; /**< TODO */

    /**
     * @brief
     *
     * @param _cubeDimension
     */
    GLvoid computeHeights(GLfloat _cubeDimension);

    /**
     * @brief
     *
     * @param _name
     */
    CubeString *getCubeStringFromName(GLuint _name);

    /**
     * @brief
     *
     * @param _label
     */
    CubeString *getCubeStringFromLabel(QString _label);

    /**
     * @brief
     *
     * @param _labels
     */
    QList< QPair<QString,GLuint> > splitLabels(QString _labels);

    /**
     * @brief
     *
     * @param _labels
     * @param _cubeDimension
     * @param _alphabet
     */
    GLvoid init(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet);

    /**
     * @brief
     *
     * @param _labels
     * @param _maxWidth
     * @param _maxHeight
     * @param _alphabet
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     */
    GLvoid init(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f);

};

#endif // CUBESTRINGLIST_H
