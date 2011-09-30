#include "skin.h"
#include "defines.h"

Skin::Skin() :
    x_plus (NULL),
    x_minus(NULL),
    y_plus (NULL),
    y_minus(NULL),
    z_plus (NULL),
    z_minus(NULL)
{
}

Skin::Skin(QString _name) :
    name(_name),
    x_plus (NULL),
    x_minus(NULL),
    y_plus (NULL),
    y_minus(NULL),
    z_plus (NULL),
    z_minus(NULL)
{
}

Skin::Skin(GLuint _x_plus, GLuint _x_minus, GLuint _y_plus, GLuint _y_minus, GLuint _z_plus, GLuint _z_minus) :
    x_plus (_x_plus),
    x_minus(_x_minus),
    y_plus (_y_plus),
    y_minus(_y_minus),
    z_plus (_z_plus),
    z_minus(_z_minus)
{

}

Skin::~Skin()
{
    for (int i = 0; i < 6; i++)
    {
        GLuint textureID = getTexture(i);

        if (textureID != 0)
            glDeleteTextures(1, &textureID);
    }
}

void Skin::setName(QString _name)
{
    name = _name;
}

QString Skin::getName()
{
    return name;
}

void Skin::setComment(QString _comment)
{
    comment = _comment;
}

QString Skin::getComment()
{
    return comment;
}

void Skin::setTexture(GLuint face, GLuint textureID)
{
    switch (face)
    {
    case X_PLUS:
        setTextureXPlus(textureID);
        break;

    case X_MINUS:
        setTextureXMinus(textureID);
        break;

    case Y_PLUS:
        setTextureYPlus(textureID);
        break;

    case Y_MINUS:
        setTextureYMinus(textureID);
        break;

    case Z_PLUS:
        setTextureZPlus(textureID);
        break;

    case Z_MINUS:
        setTextureZMinus(textureID);
        break;
    }
}

GLuint Skin::getTexture(GLuint face)
{
    GLuint textureID = 0;

    switch (face)
    {
    case X_PLUS:
        textureID = getTextureXPlus();
        break;

    case X_MINUS:
        textureID = getTextureXMinus();
        break;

    case Y_PLUS:
        textureID = getTextureYPlus();
        break;

    case Y_MINUS:
        textureID = getTextureYMinus();
        break;

    case Z_PLUS:
        textureID = getTextureZPlus();
        break;

    case Z_MINUS:
        textureID = getTextureZMinus();
        break;
    }

    return textureID;
}

void Skin::setTextureXPlus(GLuint _x_plus)
{
    x_plus = _x_plus;
}

GLuint Skin::getTextureXPlus()
{
    return x_plus;
}

void Skin::setTextureXMinus(GLuint _x_minus)
{
    x_minus = _x_minus;
}

GLuint Skin::getTextureXMinus()
{
    return x_minus;
}

void Skin::setTextureYPlus(GLuint _y_plus)
{
    y_plus = _y_plus;
}

GLuint Skin::getTextureYPlus()
{
    return y_plus;
}

void Skin::setTextureYMinus(GLuint _y_minus)
{
    y_minus = _y_minus;
}

GLuint Skin::getTextureYMinus()
{
    return y_minus;
}

void Skin::setTextureZPlus(GLuint _z_plus)
{
    z_plus = _z_plus;
}

GLuint Skin::getTextureZPlus()
{
    return z_plus;
}

void Skin::setTextureZMinus(GLuint _z_minus)
{
    z_minus = _z_minus;
}

GLuint Skin::getTextureZMinus()
{
    return z_minus;
}

void Skin::setTextureForAllFaces(GLuint all)
{
    x_plus = all;
    x_minus = all;
    y_plus = all;
    y_minus = all;
    z_plus = all;
    z_minus = all;
}

QString Skin::toString()
{
    return QString("x+:" + QString::number(x_plus)  + " " +
                   "x-:" + QString::number(x_minus) + " " +
                   "y+:" + QString::number(y_plus)  + " " +
                   "y-:" + QString::number(y_minus) + " " +
                   "z+:" + QString::number(z_plus)  + " " +
                   "z-:" + QString::number(z_minus));
}
