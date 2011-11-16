#ifndef SKIN_H
#define SKIN_H

#include <QtOpenGL>

/**
 * @brief It is the Skin Class.
 *
 * @version 1.0
 * @author \#34
 */
class Skin
{

public:

    /**
     * @brief Create a Skin object.
     */
    explicit Skin();

    /**
     * @brief Create a Skin object with a name.
     */
    explicit Skin(QString _name);

    /**
     * @brief Create a Skin object giving the faces.
     *
     * @param _x_plus is the x+ texture ID.
     * @param _x_minus is the x- texture ID.
     * @param _y_plus is the y+ texture ID.
     * @param _y_minus is the y- texture ID.
     * @param _z_plus is the z+ texture ID.
     * @param _z_minus is the z- texture ID.
     */
    explicit Skin(GLuint _x_plus, GLuint _x_minus, GLuint _y_plus, GLuint _y_minus, GLuint _z_plus, GLuint _z_minus);

    /**
     * @brief Safely destroy the Skin.
     */
    ~Skin();

    /**
     * @brief Set the name of the Skin.
     *
     * @param _name is the name to set.
     */
    void setName(QString _name);

    /**
     * @brief Returns the name of the Skin.
     *
     * @returns the name of the Skin.
     */
    QString getName();

    /**
     * @brief Set the comment of the Skin.
     *
     * @param _comment is the comment to set.
     */
    void setComment(QString _comment);

    /**
     * @brief Returns the comment of the Skin.
     *
     * @returns the comment of the Skin.
     */
    QString getComment();

    /**
     * @brief Set one texture of the Skin.
     *
     * @param face is the face to set the texture.
     * @param textureID is the texture ID to set.
     */
    void setTexture(GLuint face, GLuint textureID);

    /**
     * @brief Returns the texture for the specified face.
     *
     * @param face is the face to get the texture.
     *
     * @returns the texture for the specified face.
     */
    GLuint getTexture(GLuint face);

    /**
     * @brief Set the texture for x+ face.
     *
     * @param _x_plus is the texture to set.
     */
    void setTextureXPlus(GLuint _x_plus);

    /**
     * @brief Returns the texture for x+ face.
     *
     * @returns the texture for x+ face.
     *
     */
    GLuint getTextureXPlus();

    /**
     * @brief Set the texture for x- face.
     *
     * @param _x_minus is the texture to set.
     */
    void setTextureXMinus(GLuint _x_minus);

    /**
     * @brief Returns the texture for x- face.
     *
     * @returns the texture for x- face.
     */
    GLuint getTextureXMinus();

    /**
     * @brief Set the texture for y+ face.
     *
     * @param _y_plus is the texture to set.
     */
    void setTextureYPlus(GLuint _y_plus);

    /**
     * @brief Returns the texture for y+ face.
     *
     * @returns the texture for y+ face.
     */
    GLuint getTextureYPlus();

    /**
     * @brief Set the texture for y- face.
     *
     * @param _y_minus is the texture to set.
     */
    void setTextureYMinus(GLuint _y_minus);

    /**
     * @brief Returns the texture for y- face.
     *
     * @returns the texture for y- face.
     */
    GLuint getTextureYMinus();

    /**
     * @brief Set the texture for z+ face.
     *
     * @param _z_plus is the texture to set.
     */
    void setTextureZPlus(GLuint _z_plus);

    /**
     * @brief Returns the texture for z+ face.
     *
     * @returns the texture for z+ face.
     */
    GLuint getTextureZPlus();

    /**
     * @brief Set the texture for z- face.
     *
     * @param _z_minus is the texture to set.
     */
    void setTextureZMinus(GLuint _z_minus);

    /**
     * @brief Returns the texture for z- face.
     *
     * @returns the texture for z- face.
     */
    GLuint getTextureZMinus();

    /**
     * @brief Set the same texture for all the faces.
     *
     * @param all is the texture to set.
     */
    void setTextureForAllFaces(GLuint all);

    /**
     * @brief Print a string containing the GLuint textureIDs.
     *
     * @returns a string containing the GLuint textureIDs.
     */
    QString toString();


private:

    QString name; /**< It is the name of the skin */
    QString comment; /**< It is the coment of the skin */
    GLuint x_plus; /**< It is the x+ face texture of the skin */
    GLuint x_minus;  /**< It is the x- face texture of the skin */
    GLuint y_plus; /**< It is the y+ face texture of the skin */
    GLuint y_minus;  /**< It is the y- face texture of the skin */
    GLuint z_plus; /**< It is the z+ face texture of the skin */
    GLuint z_minus;  /**< It is the z- face texture of the skin */

};

#endif // SKIN_H
