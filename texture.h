#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <iostream>
#include <GL/glew.h>
#include <IL/ilut.h>

/**
 * @brief
 *
 */
class Texture : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief
     *
     * @param filename
     */
    Texture(QString filename);

    /**
     * @brief
     *
     */
    GLuint getTextureID();

private:

    ILubyte *p; /**< TODO */
    ILuint imageID; /**< TODO */
    ILint w; /**< TODO */
    ILint h; /**< TODO */
    ILenum DestFormat; /**< TODO */
    ILenum DestType; /**< TODO */
    GLuint textureID; /**< TODO */
};

#endif // TEXTURE_H
