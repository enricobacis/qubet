#ifndef CUBESTRING_H
#define CUBESTRING_H

#include "utilities.h"

/**
 * @brief This class is used to draw, a string composed the horizontal justapposition of
 *        Different cubes on which the skin is a letter that compose the string. Letters
 *        are generated from an instance of the class Alphabet.
 *
 *        You can create a CubeString defining its cubes dimension or defining the maximum
 *        width and height the entire CubeString can grow up to.
 *
 *        CubeString uses OpenGL displayLists to speed the drawing process.
 *
 * @version 1.0
 * @author \#34
 */
class CubeString
{

public:

    /**
     * @brief Creates a CubeString of the text _label, using the Alphabet _alphabet and
     *        every cube letter of the string will be of dimension _cubeDimension.
     *
     *        You can define a name for the entire string setting the parameter _name
     *        for picking purposes. If you don't set a name 0 will be used.
     *
     * @param _label is the text you want to write using the CubeString.
     * @param _cubeDimension is the dimension of the single cube of the string.
     * @param _alphabet is the reference to the Alphabet you want to use.
     * @param _name is the name given to the entire string (for picking purposes). [default = 0]
     */
    explicit CubeString(QString _label, GLfloat _cubeDimension, Alphabet *_alphabet, GLuint _name = 0);

    /**
     * @brief Creates a CubeString of the text _label, using the Alphabet _alphabet and
     *        the entire CubeString can grow up to _maxWidth as width and _maxHeight
     *        as height.
     *
     *        You can define a name for the entire string setting the parameter _name
     *        for picking purposes. If you don't set a name 0 will be used.
     *
     * @param _label is the text you want to write using the CubeString.
     * @param _maxWidth is the maximum width the CubeString can grow up to.
     * @param _maxHeight is the maximum height the CubeString can grow up to.
     * @param _alphabet is the reference to the Alphabet you want to use.
     * @param _maxCubeDimension is the maximum cubeDimension. If set to a number <= 0 it
     *        will not be computated. [default = 0.0f]
     * @param _name is the name given to the entire string (for picking purposes). [default = 0]
     */
    explicit CubeString(QString _label, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension = 0.0f, GLuint _name = 0);

    /**
     * @brief Safely destroys a CubeString.
     *
     *        It also safely deletes the displayList associated to the CubeString.
     */
    ~CubeString();

    /**
     * @brief Draws the CubeString in the current selected point of the scene.
     *
     *        The CubeString will be drawn using the current point as the center of
     *        the drawn CubeString.
     *
     * @param simplifyForPicking is the is used to draw a simplified scene used for the picking function
     *        and does not compute the change to angles. [default = false]
     */
    GLvoid draw(GLboolean simplifyForPicking = false);

    /**
     * @brief Returns the text of the CubeString.
     *
     * @returns the text of the CubeString.
     */
    QString getLabel();

    /**
     * @brief Returns the name given to the entire string (for picking purposes). [default = 0]
     *
     * @returns the name given to the entire string (for picking purposes). [default = 0]
     */
    GLuint getName();

    /**
     * @brief Start the rotation of a letter in the CubeString.
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
     * @param _letterName is the name of the Letter (it is the second name (after the entire string name) in the nameList of the picking function.
     *        You don't have to know which is, let the picking function and the CubeString code work for you.
     * @param _angleStep is the angle that will be summed to letter on each frame.
     * @param _turns is an integer that states how many 90 degrees turns you
     *        want the letter to do.
     */
    GLvoid startLetterRotation(GLuint _letterName, GLint _angleStep, GLint _turns);

    /**
     * @brief Start the rotation of the entire CubeString.
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
     * @param _angleStep is the angle that will be summed to every letter on each frame.
     * @param _turns is an integer that states how many 90 degrees turns you
     *        want each letter to do.
     */
    GLvoid startStringRotation(GLint _angleStep, GLint _turns);

    /**
     * @brief Check if a letter of the CubeString is already rotating.
     *
     * @param _letterName is the name of the letter (it is the second name (after the entire string name) in the nameList of the picking function.
     *        You don't have to know which is, let the picking function and the CubeString code work for you.
     *
     * @returns true if the letter is already rotating, else false.
     */
    GLboolean isRotating(GLuint _letterName);

    /**
     * @brief Set the current angle for the letters in the CubeString.
     *
     * @param _firstLetterAngle is the angle of the current letter of the CubeString.
     * @param _nextLetterDelta is the delta you want to apply from the previous and
     *        the next letter's angle. [default = 0]
     *
     * @returns the angle the next letter after this CubeString should have.
     */
    GLfloat setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta = 0);


private:

    QString label; /**<  It is the text of the CubeString. */
    GLfloat cubeDimension; /**<  It is the dimension of the single cube of the CubeString. */
    GLuint name; /**< It is the name given to the entire string (for picking purposes). [default = 0] */
    Alphabet *alphabet; /**< It is the reference to the Alphabet you want to use.  */

    QList<GLint> angleSteps; /**< It is a list to save the angle step of each letter. */
    QList<GLint> currentAngles;  /**< It is a list to save the current angle of each letter. */
    QList<GLint> finalAngles; /**< It is a list to save the final angle of each letter. */

#ifdef USE_DISPLAY_LISTS_FOR_LETTERS

    QList<GLuint> letterDisplayLists;  /**< It is a list to save the Display List ID of each letter. */

#else

    QList<Skin*> letterSkins; /**< It is a list to save the skin of each letter. */

#endif

    /**
     * @brief It is an internal function to create the OpenGL displayList of a letter.
     *
     * @param _letter is the QChar letter you want to create a displayList for.
     *
     * @returns the displayList ID.
     */
    GLuint createLetterDisplayList(QChar _letter);

    /**
     * @brief It is an internal function to create the OpenGL displayList from a skin.
     *
     * @param _skin is the skin you want to create a displayList for.
     *
     * @returns the displayList ID.
     */
    GLuint createLetterDisplayList(Skin *_skin);

    /**
     * @brief It is an internal function used to initialize CubeString's values.
     */
    GLvoid init();

};

#endif // CUBESTRING_H
