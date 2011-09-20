#include "texture.h"

Texture::Texture(QString filename)
{
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    ilGenImages(1, &imageID);
    ilBindImage(imageID);

    if (!ilLoadImage(filename.toStdString().c_str()))
        std::cout << "Errore Apertura file: " << filename.toStdString() << std::endl;

    ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

    p = ilGetData();
    w = ilGetInteger(IL_IMAGE_WIDTH);
    h = ilGetInteger(IL_IMAGE_HEIGHT);

    DestFormat = ilGetInteger(IL_IMAGE_FORMAT);
    DestType = ilGetInteger(IL_IMAGE_TYPE);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, DestFormat, w, h, 0, DestFormat, DestType, p);
}

ILuint Texture::getTextureID()
{
    return textureID;
}
