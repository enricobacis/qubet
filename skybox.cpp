#include "skybox.h"

Skybox::Skybox(Skin *_skin, GLfloat _emissionFactor, GLfloat _cubeSide) :
    skin(_skin),
    cubeSide(_cubeSide)
{
    if (_emissionFactor < 0.0f)
        emissionFactor = 0.0f;
    else if (_emissionFactor > 1.0f)
        emissionFactor = 1.0f;
    else
        emissionFactor = _emissionFactor;
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
        emissionFactor = 0.0f;
    else if (_emissionFactor > 1.0f)
        emissionFactor = 1.0f;
    else
        emissionFactor = _emissionFactor;
}

GLfloat Skybox::getEmssionFactor()
{
    return emissionFactor;
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
    GLfloat mat_emission[] = {emissionFactor, emissionFactor, emissionFactor, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

    drawPrism(cubeSide, cubeSide, cubeSide, skin);

    GLfloat mat_noemission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_noemission);
}
