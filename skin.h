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
     * @brief contructor for Skin object.
     *
     */
    explicit Skin();

    /**
     * @brief contructor for Skin object.
     *
     */
    explicit Skin(QString _name);

    /**
     * @brief contructor for Skin object.
     *
     * @param _x_plus
     * @param _x_minus
     * @param _y_plus
     * @param _y_minus
     * @param _z_plus
     * @param _z_minus
     */
    explicit Skin(GLuint _x_plus, GLuint _x_minus, GLuint _y_plus, GLuint _y_minus, GLuint _z_plus, GLuint _z_minus);

    /**
     * @brief safely destruct the Skin.
     *
     */
    ~Skin();

    /**
     * @brief set the name of the skin.
     *
     * @param _name
     */
    void setName(QString _name);

    /**
     * @brief returns the skin name.
     *
     * @returns the skin name.
     */
    QString getName();

    /**
     * @brief set the skin comment.
     *
     * @param _comment
     */
    void setComment(QString _comment);

    /**
     * @brief returns the skin comment.
     *
     * @returns the skin comment.
     */
    QString getComment();

    /**
     * @brief set the texture of the skin.
     *
     * @param face
     * @param textureID
     */
    void setTexture(GLuint face, GLuint textureID);

    /**
     * @brief returns the texture for the specified face.
     *
     * @param face
     *
     * @returns the texture for the specified face.
     */
    GLuint getTexture(GLuint face);

    /**
     * @brief set the texture for x+ face.
     *
     * @param _x_plus
     */
    void setTextureXPlus(GLuint _x_plus);

    /**
     * @brief
     *
     */
    GLuint getTextureXPlus();

    /**
     * @brief set the texture for x- face.
     *
     * @param _x_minus
     */
    void setTextureXMinus(GLuint _x_minus);

    /**
     * @brief returns the texture for x- face.
     *
     * @returns the texture for x- face.
     */
    GLuint getTextureXMinus();

    /**
     * @brief set the texture for y+ face.
     *
     * @param _y_plus
     */
    void setTextureYPlus(GLuint _y_plus);

    /**
     * @brief returns the texture for y+ face.
     *
     * @returns the texture for y+ face.
     */
    GLuint getTextureYPlus();

    /**
     * @brief set the texture for y- face.
     *
     * @param _y_minus
     */
    void setTextureYMinus(GLuint _y_minus);

    /**
     * @brief returns the texture for y- face.
     *
     * @returns the texture for y- face.
     */
    GLuint getTextureYMinus();

    /**
     * @brief set the texture for z+ face.
     *
     * @param _z_plus
     */
    void setTextureZPlus(GLuint _z_plus);

    /**
     * @brief returns the texture for z+ face.
     *
     * @returns the texture for z+ face.
     */
    GLuint getTextureZPlus();

    /**
     * @brief set the texture for z- face.
     *
     * @param _z_minus
     */
    void setTextureZMinus(GLuint _z_minus);

    /**
     * @brief returns the texture for z- face.
     *
     * @returns the texture for z- face.
     */
    GLuint getTextureZMinus();

    /**
     * @brief set all the textures.
     *
     * @param all
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
