#ifndef SKIN_H
#define SKIN_H

#include <QtOpenGL>
#include <QString>
#include <QImage>

#include "defines.h"


/**
 * @brief
 */
class Skin
{

public:

    /**
     * @brief
     *
     */
    explicit Skin();

    /**
     * @brief
     *
     */
    explicit Skin(QString _name);

    /**
     * @brief
     *
     */
    ~Skin();

    /**
     * @brief
     *
     * @param _name
     */
    void setName(QString _name);

    /**
     * @brief
     *
     */
    QString getName();

    /**
     * @brief
     *
     * @param _comment
     */
    void setComment(QString _comment);

    /**
     * @brief
     *
     */
    QString getComment();

    /**
     * @brief
     *
     * @param face
     * @param textureID
     */
    void setTexture(GLuint face, GLuint textureID);

    /**
     * @brief
     *
     * @param face
     */
    GLuint getTexture(GLuint face);

    /**
     * @brief
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
     * @brief
     *
     * @param _x_minus
     */
    void setTextureXMinus(GLuint _x_minus);

    /**
     * @brief
     *
     */
    GLuint getTextureXMinus();

    /**
     * @brief
     *
     * @param _y_plus
     */
    void setTextureYPlus(GLuint _y_plus);

    /**
     * @brief
     *
     */
    GLuint getTextureYPlus();

    /**
     * @brief
     *
     * @param _y_minus
     */
    void setTextureYMinus(GLuint _y_minus);

    /**
     * @brief
     *
     */
    GLuint getTextureYMinus();

    /**
     * @brief
     *
     * @param _z_plus
     */
    void setTextureZPlus(GLuint _z_plus);

    /**
     * @brief
     *
     */
    GLuint getTextureZPlus();

    /**
     * @brief
     *
     * @param _z_minus
     */
    void setTextureZMinus(GLuint _z_minus);

    /**
     * @brief
     *
     */
    GLuint getTextureZMinus();

    /**
     * @brief
     *
     * @param all
     */
    void setTextureForAllFaces(GLuint all);

    /**
     * @brief Print a string containing the GLuint textureIDs.
     *
     * @return QString a string containing the GLuint textureIDs.
     */
    QString toString();

private:

    QString name; /**< TODO */
    QString comment; /**< TODO */
    GLuint x_plus; /**< TODO */
    GLuint x_minus;  /**< TODO */
    GLuint y_plus; /**< TODO */
    GLuint y_minus;  /**< TODO */
    GLuint z_plus; /**< TODO */
    GLuint z_minus;  /**< TODO */

};

#endif // SKIN_H
