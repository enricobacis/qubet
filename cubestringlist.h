#ifndef CUBESTRINGLIST_H
#define CUBESTRINGLIST_H

#include "cubestring.h"

/**
 * @brief This class is used to draw a vertical list of CubeString.
 *        Look at CubeString to have a better specification of the class.
 *
 * @version 1.0
 * @author \#34
 */
class CubeStringList
{

public:

    /**
     * @brief Creates a CubeStringList from a QList of QPair, the first item of each pair
     *        is the string to draw, the second the OpenGL name you want to give the string.
     *        Using this constructor you can define the dimension of the cubes.
     *
     * @param _labels is a QList of QPair, the first item of each pair is the string to draw,
     *        the second the OpenGL name you want to give the string.
     * @param _cubeDimension is the dimension of each cube of the single CubeString.
     * @param _alphabet is the Alphabet to use.
     */
    explicit CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet);

    /**
     * @brief Creates a CubeStringList from a QList of QPair, the first item of each pair
     *        is the string to draw, the second the OpenGL name you want to give the string.
     *        Using this constructor you can define a maximum space the CubeStringList can grow,
     *        the class then will manage the list to fit this space.
     *
     * @param _labels is a QList of QPair, the first item of each pair is the string to draw,
     *        the second the OpenGL name you want to give the string.
     * @param _maxWidth is the maximum width the CubeStringList can grow.
     * @param _maxHeight is the maximum height the CubeStringList can grow.
     * @param _alphabet is the Alphabet to use.
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     */
    explicit CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f);

    /**
     * @brief Creates a CubeStringList from QString, it will be splitted on the
     *        character space to tokenize the string and create the list of words.
     *        You can also set the OpenGL name of the CubeStringList (the same for all the lines).
     *        Using this constructor you can define a maximum space the CubeStringList can grow,
     *        the class then will manage the list to fit this space.
     *
     * @param _labels is the QString that will be splitted on the character space to create the list of words.
     * @param _cubeDimension is the dimension of each cube of the single CubeString.
     * @param _alphabet is the Alphabet to use.
     * @param _name is the OpenGL name of the CubeStringList (the same for all the lines). [default = 0]
     */
    explicit CubeStringList(QString _labels, GLfloat _cubeDimension, Alphabet *_alphabet, GLuint _name = 0);

    /**
     * @brief Creates a CubeStringList from QString, it will be splitted on the
     *        character space to tokenize the string and create the list of words.
     *        You can also set the OpenGL name of the CubeStringList (the same for all the lines).
     *        Using this constructor you can define a maximum space the CubeStringList can grow,
     *        the class then will manage the list to fit this space.
     *
     * @param _labels is the QString that will be splitted on the character space to create the list of words.
     * @param _maxWidth is the maximum width the CubeStringList can grow.
     * @param _maxHeight is the maximum height the CubeStringList can grow.
     * @param _alphabet is the Alphabet to use.
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     * @param _name is the OpenGL name of the CubeStringList (the same for all the lines). [default = 0]
     */
    explicit CubeStringList(QString _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f, GLuint _name = 0);

    /**
     * @brief Safely destroy a CubeStringList.
     */
    ~CubeStringList();

    /**
     * @brief Draws the CubeStringList at the current position.
     *
     * @param simplifyForPicking
     */
    GLvoid draw(GLboolean simplifyForPicking);

    /**
     * @brief Returns the number of labels in the CubeStringList.
     *
     * @return the number of labels in the CubeStringList.
     */
    GLint getLabelCount();

    /**
     * @brief Returns the label which name is _stringName.
     *
     * @param _stringName is the name of the string you want the label.
     *
     * @return the label which name is _stringName.
     */
    QString getLabel(GLuint _stringName);

    /**
     * @brief Start the rotation of a single letter in a single CubeString contained in the CubeStrigList.
     *
     *        If you use this function when a letter is already rotating, the
     *        _turns will be summed to the current rotation but the new
     *        _angleStep will be used only if:
     *        (current angleStep) % _angleStep == 0
     *        This is the only sure way to keep the validity.
     *
     * @warning In order to prevent infinite rotations, only valid rotations
     *          will be accepted, a rotation is valid if:
     *          (_turns * 90) % _angleStep == 0
     *
     * @param _stringName is the string that contains the letter you want to start the rotation.
     * @param _letterName is the name of the Letter (it is the second name (after the entire string name) in the nameList of the picking function.
     *        You don't have to know which is, let the picking function and the CubeString code work for you.
     * @param _angleStep is the angle that will be summed to letter on each frame.
     * @param _turns is an integer that tells how many 90 degrees turns you
     *        want the letter to do.
     */
    GLvoid startLetterRotation(GLuint _stringName, GLuint _letterName, GLint _angleStep, GLint _turns);

    /**
     * @brief Start the rotation of a whole CubeString contained in the CubeStringList
     *
     *        If you use this function when a CubeString is already rotating, the
     *        _turns will be summed to the current rotation but the new
     *        _angleStep will be used only if:
     *        (current angleStep) % _angleStep == 0
     *        This is the only sure way to keep the validity.
     *
     * @warning In order to prevent infinite rotations, only valid rotations
     *          will be accepted, a rotation is valid if:
     *          (_turns * 90) % _angleStep == 0
     *
     * @param _stringName is the string you want to start the rotation.
     * @param _angleStep is the angle that will be summed to every letter on each frame.
     * @param _turns is an integer that tells how many 90 degrees turns you
     *        want each letter to do.
     */
    GLvoid startStringRotation(GLuint _stringName, GLint _angleStep, GLint _turns);

    /**
     * @brief Start the rotation of the whole CubeStringList (woo-woo-wao).
     *
     * @param _angleStep is the angle that will be summed to every letter on each frame.
     * @param _turns is an integer that tells how many 90 degrees turns you
     *        want each letter to do.
     */
    GLvoid startStringListRotation(GLint _angleStep, GLint _turns);

    /**
     * @brief Check if a letter of the CubeString is already rotating.
     *
     * @param _stringName is the name of the string (it is the second name (after the entire list name) in the nameList of the picking function.
     *        You don't have to know which is, let the picking function and the CubeStringList code work for you.
     * @param _letterName is the name of the letter (it is the third name (after the entire list and the string names) in the nameList of the picking function.
     *        You don't have to know which is, let the picking function and the CubeStringList code work for you.
     */
    GLboolean isRotating(GLuint _stringName, GLuint _letterName);

    /**
     * @brief Set the current angle for the letters in the CubeString.
     *
     * @param _firstLetterAngle is the angle of the current letter of the CubeStringList.
     * @param _nextLetterDelta is the delta you want to apply from the previous and
     *        the next letter's angle. [default = 0]
     *
     * @return the angle the next letter after this CubeString should have.
     */
    GLfloat setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta = 0.0f);


private:

    QList<CubeString*> cubeStrings; /**< It is the list of CubeStrings. */
    GLuint name; /**< It is the OpenGL name of the CubeStringList. */
    GLfloat interline; /**< It is the interline from one line to the following one. */
    GLfloat firstStringHeight; /**< It is the height of the first string of the list. */
    GLfloat stringsHeightDelta; /**< It is the delta from the centers of two strings in the list. */

    /**
     * @brief It compute the heights (firstStringHeight and stringsHeightDelta) basing on constructor parameters.
     *
     * @param _cubeDimension is the dimension of the cubes.
     */
    GLvoid computeHeights(GLfloat _cubeDimension);

    /**
     * @brief Return a pointer to the CubeString having the parameter OpenGL name.
     *
     * @param _name is the OpenGL name you want the CubeString.
     * @return a pointer to the CubeString having the parameter OpenGL name.
     */
    CubeString *getCubeStringFromName(GLuint _name);

    /**
     * @brief Return a pointer to the CubeString having the parameter label.
     *
     * @param _labelis the label you want the CubeString.
     * @return a pointer to the CubeString having the parameter OpenGL label.
     */
    CubeString *getCubeStringFromLabel(QString _label);

    /**
     * @brief Split the QString in a QList of QPair.
     *
     * @param _labels is the QString to split.
     *
     * @return the splitted QList of QPair.
     */
    QList< QPair<QString,GLuint> > splitLabels(QString _labels);

    /**
     * @brief Common part to the constructors that uses the cubeDimension.
     *
     * @param _labels is the QString that will be splitted on the character space to create the list of words.
     * @param _cubeDimension is the dimension of each cube of the single CubeString.
     * @param _alphabet is the Alphabet to use.
     */
    GLvoid init(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet);

    /**
     * @brief Common part to the constructors that uses the maxWidth and maxHeight.
     *
     * @param _labels is the QString that will be splitted on the character space to create the list of words.
     * @param _maxWidth is the maximum width the CubeStringList can grow.
     * @param _maxHeight is the maximum height the CubeStringList can grow.
     * @param _alphabet is the Alphabet to use.
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0.0f it
     *        will not be computated. [default = 0.0f]
     */
    GLvoid init(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f);

};

#endif // CUBESTRINGLIST_H
