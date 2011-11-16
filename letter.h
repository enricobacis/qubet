#ifndef LETTER_H
#define LETTER_H

#include <QtOpenGL>

/**
 * @brief This class rapresents a single Letter (or number or special character),
 *        with a list of textures that graphically rapresents the letter.
 *
 *        In order to do this it stores the character in a QChar and a list GLuint that
 *        are the texture IDs.
 *
 * @version 1.0
 * @author \#34
 */
class Letter
{

public:

    /**
     * @brief Create a Letter that rapresents the character _letter.
     *
     * @param _letter is the character rapresented.
     */
    explicit Letter(QChar _letter);

    /**
     * @brief Safely destroy a Letter.
     */
    ~Letter();

    /**
     * @brief Returns a random selected texture from the list of texture IDs of the Letter.
     *
     * @returns a random selected texture from the list of texture IDs of the Letter.
     */
    GLuint getRandomTexture();

    /**
     * @brief Returns a QList of numberOfTextures random selected texture from the list of texture IDs of the Letter.
     *        If the Letter contains at least numberOfTextures textures, the textures doesn't repeat.
     *
     * @param numberOfTextures is the number of textures you want to extract.
     */
    QList<GLuint> getRandomTextures(int numberOfTextures);

    /**
     * @brief Returns a QList of all the textures of the Letter.
     *
     * @returns a QList of all the textures of the Letter.
     */
    QList<GLuint> getAllTextures();

    /**
     * @brief Appends a textures to the Letter's textures List.
     *
     * @param textureID is the texture ID to append to the Letter.
     */
    GLvoid appendTexture(GLuint textureID);

private:

    QChar letter; /**< It is the character rapresented. */
    QList<GLuint> textures; /**< It is the QList of the texture IDs associated to the Letter. */

    /**
     * @brief It is a private utility method that returns a QList of random unique (if possible)
     *        integer numbers from an interval.
     *
     *        It is a smart function and completes its task in a deterministic cases-linear time.
     *
     * @param from is the lower bound of the interval.
     * @param to is the upper bound of the interval.
     * @param cases is the number of integer to select.
     *
     * @returns a QList of random unique (if possible) integer numbers from an interval.
     */
    QList<int> getRandomUniqueSequence(int from, int to, int cases);
};

#endif // LETTER_H
