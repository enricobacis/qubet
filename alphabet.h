#ifndef ALPHABET_H
#define ALPHABET_H

//#include <QtOpenGL>
//#include <QMap>
//#include <QList>

#include "letter.h"
#include "skin.h"

/**
 * @brief
 *
 */
class Alphabet
{

public:

    /**
     * @brief
     *
     */
    explicit Alphabet();

    /**
     * @brief
     *
     */
    ~Alphabet();

    /**
     * @brief
     *
     * @param letter
     */
    Skin *getRandomLetterSkin(QChar letter);

    /**
     * @brief
     *
     * @param letter
     */
    GLuint getRandomLetterTexture(QChar letter);

    /**
     * @brief
     *
     * @param letter
     * @param numberOfTextures
     */
    QList<GLuint> getRandomLetterTextures(QChar letter, GLint numberOfTextures);

    /**
     * @brief
     *
     * @param letter
     */
    QList<GLuint> getAllLetterTextures(QChar letter);

    /**
     * @brief
     *
     * @param letter
     * @param textureID
     */
    GLvoid appendLetterTexture(QChar letter, GLuint textureID);


private:

    QMap<QChar,Letter*> lettersList; /**< TODO */

};

#endif // ALPHABET_H
