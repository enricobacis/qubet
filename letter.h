#ifndef LETTER_H
#define LETTER_H

#include <QtOpenGL>
#include <QList>

/**
 * @brief
 *
 */
class Letter
{

public:

    /**
     * @brief
     *
     * @param _letter
     */
    explicit Letter(QChar _letter);

    /**
     * @brief
     *
     */
    ~Letter();

    /**
     * @brief
     *
     */
    GLuint getRandomTexture();

    /**
     * @brief
     *
     * @param numberOfTextures
     */
    QList<GLuint> getRandomTextures(int numberOfTextures);

    /**
     * @brief
     *
     */
    QList<GLuint> getAllTextures();

    /**
     * @brief
     *
     * @param textureID
     */
    GLvoid appendTexture(GLuint textureID);

private:

    QChar letter; /**< TODO */
    QList<GLuint> textures; /**< TODO */

    /**
     * @brief
     *
     * @param from
     * @param to
     * @param cases
     */
    QList<int> getRandomUniqueSequence(int from, int to, int cases);
};

#endif // LETTER_H
