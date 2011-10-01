#ifndef ALPHABET_H
#define ALPHABET_H

#include "letter.h"
#include "skin.h"

/**
 * @brief This class is used to keep a list of Letter (from this the name Alphabet)
 *        It provide access to Letter function such as appending textures to a Letter
 *        and getting textures from a Letter.
 *
 * @version 1.0
 * @author \#34
 */
class Alphabet
{

public:

    /**
     * @brief Creates an empty Alphabet and initializes the seed of random number generation
     *        used to extract a set of random Letter textures.
     */
    explicit Alphabet();

    /**
     * @brief Safely destroy an Alphabet (and all the Letter in its list).
     */
    ~Alphabet();

    /**
     * @brief Returns a random generated Skin of the letter given as parameter.
     *
     *        If the letter has got at least 6 textures, the skin faces are
     *        not repeated, else they are choosen in a completely random way.
     *
     *        If the letter is not present in the Alphabet or contains no textures,
     *        the function will return a Skin of zeros.
     *
     * @param letter is the QChar letter of the Alphabet you want to generate the skin.
     *
     * @return a random skin of parameter letter textures.
     */
    Skin *getRandomLetterSkin(QChar letter);

    /**
     * @brief Returns a random texture of the letter given as parameter.
     *
     *        If the letter is not present in the Alphabet or contains no textures,
     *        the function will return 0.
     *
     * @param letter is the letter you want a texture.
     *
     * @return the random extracted texture ID.
     */
    GLuint getRandomLetterTexture(QChar letter);

    /**
     * @brief Returns a list of random textures of the letter given as parameter.
     *
     *        If the letter has got at least numberOfTextures textures, the skin faces
     *        are not repeated, else they are choosen in a completely random way.
     *
     *        If the letter is not present in the Alphabet or contains no textures,
     *        the function will return a list of zeros.
     *
     * @param letter is the QChar letter of the Alphabet you want to extract textures.
     * @param numberOfTextures is the number of textures you want to extract from the Letter.
     *
     * @return the random extracted list of texture IDs.
     */
    QList<GLuint> getRandomLetterTextures(QChar letter, GLint numberOfTextures);

    /**
     * @brief Returns a list of all the textures of the letter given as parameter.
     *
     *        If the letter is not present in the Alphabet or contains no textures,
     *        the function will return an empty list.
     *
     * @param letter is the QChar letter of the Alphabet you want to extract textures.
     *
     * @return the list of all letter's Texture IDs.
     */
    QList<GLuint> getAllLetterTextures(QChar letter);

    /**
     * @brief Appends the textureID given as parameter to the Letter's textures of the
     *        letter given as parameter.
     *
     * @param letter is the letter to which you want to append the textureID.
     * @param textureID is the texture ID to append.
     */
    GLvoid appendLetterTexture(QChar letter, GLuint textureID);


private:

    QMap<QChar,Letter*> lettersList; /**< It is the QMap of Letter* that compose the Alphabet. */

};

#endif // ALPHABET_H
