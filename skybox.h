#ifndef SKYBOX_H
#define SKYBOX_H

#include "utilities.h"

/**
 * @brief
 *
 */
class Skybox
{

public:

    /**
     * @brief
     *
     * @param _skin
     * @param _emissionFactor
     * @param _cubeSide
     */
    explicit Skybox(Skin *_skin, GLfloat _emissionFactor = 0.6f, GLfloat _cubeSide = 40.0f);

    /**
     * @brief
     *
     */
    ~Skybox();

    /**
     * @brief
     *
     * @param _skin
     */
    GLvoid setSkin(Skin *_skin);

    /**
     * @brief
     *
     */
    Skin *getSkin();

    /**
     * @brief
     *
     * @param _emissionFactor
     */
    GLvoid setEmissionFactor(GLfloat _emissionFactor);

    /**
     * @brief
     *
     */
    GLfloat getEmssionFactor();

    /**
     * @brief
     *
     * @param _side
     */
    GLvoid setCubeSide(GLfloat _cubeSide);

    /**
     * @brief
     *
     */
    GLfloat getCubeSide();

    /**
     * @brief
     *
     */
    GLvoid draw();

private:

    Skin *skin; /**< TODO */
    QVector<GLfloat> emissionVector; /**< TODO */
    QVector<GLfloat> disabledVector; /**< TODO */
    GLfloat cubeSide; /**< TODO */
};

#endif // SKYBOX_H
