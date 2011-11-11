#include "skybox.h"

Skybox::Skybox(Skin *_skin, GLfloat _emissionFactor, GLfloat _cubeSide) :
    skin(_skin),
    emissionVector(QVector<GLfloat>(4)),
    disabledVector(QVector<GLfloat>(4)),
    cubeSide(_cubeSide)
{
    if (_emissionFactor < 0.0f)
        emissionVector.fill(0.0f, 3);
    else if (_emissionFactor > 1.0f)
        emissionVector.fill(1.0f, 3);
    else
        emissionVector.fill(_emissionFactor, 3);

    emissionVector.append(1.0f);

    disabledVector.fill(0.0f, 3);
    disabledVector.append(1.0f);
}

Skybox::~Skybox()
{
    if (skin != NULL)
        skin->~Skin();
}

GLvoid Skybox::setSkin(Skin *_skin)
{
    skin = _skin;
}

Skin *Skybox::getSkin()
{
    return skin;
}

GLvoid Skybox::setEmissionFactor(GLfloat _emissionFactor)
{
    if (_emissionFactor < 0.0f)
        emissionVector.fill(0.0f, 3);
    else if (_emissionFactor > 1.0f)
        emissionVector.fill(1.0f, 3);
    else
        emissionVector.fill(_emissionFactor, 3);

    emissionVector.append(1.0f);
}

GLfloat Skybox::getEmssionFactor()
{
    return emissionVector.at(1);
}

GLvoid Skybox::setCubeSide(GLfloat _cubeSide)
{
    cubeSide = _cubeSide;
}

GLfloat Skybox::getCubeSide()
{
    return cubeSide;
}

GLvoid Skybox::draw()
{
    glDisable(GL_DEPTH_TEST);
    glDepthMask(false);

    glMaterialfv(GL_FRONT, GL_EMISSION, emissionVector.data());
    drawPrism(cubeSide, cubeSide, cubeSide, skin);
    glMaterialfv(GL_FRONT, GL_EMISSION, disabledVector.data());

    glDepthMask(true);
    glEnable(GL_DEPTH_TEST);
}
