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
     */
    explicit CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet);

    /**
     * @brief
     *
     * @param _labels
     * @param _cubeDimension
     * @param _name
     * @param _alphabet
     */
    explicit CubeStringList(QString _labels, GLfloat _cubeDimension, GLuint _name, Alphabet *_alphabet);

    /**
     * @brief
     *
     * @param _labels
     * @param _maxWidth
     * @param _maxHeight
     * @param _name
     * @param _alphabet
     */
    explicit CubeStringList(QString _labels, GLfloat _maxWidth, GLfloat _maxHeight, GLuint _name, Alphabet *_alphabet);

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
    GLfloat setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta = 0);


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
     */
    GLvoid init(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet);

};

#endif // CUBESTRINGLIST_H
