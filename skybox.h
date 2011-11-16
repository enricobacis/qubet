#ifndef SKYBOX_H
#define SKYBOX_H

#include "utilities.h"

/**
 * @brief It is the Skybox Class.
 *
 */
class Skybox
{

public:

    /**
     * @brief constructor of skybox object.
     *
     * @param _skin
     * @param _emissionFactor
     * @param _cubeSide
     */
    explicit Skybox(Skin *_skin, GLfloat _emissionFactor = 0.6f, GLfloat _cubeSide = 40.0f);

    /**
     * @brief safely destroy skybox object.
     *
     */
    ~Skybox();

    /**
     * @brief set the skybox skin.
     *
     * @param _skin
     */
    GLvoid setSkin(Skin *_skin);

    /**
     * @brief returns the skybox skin.
     *
     * @returns the skybox skin.
     */
    Skin *getSkin();

    /**
     * @brief set the skybox emission factor.
     *
     * @param _emissionFactor
     */
    GLvoid setEmissionFactor(GLfloat _emissionFactor);

    /**
     * @brief returns the emissionFactor value.
     *
     * @returns the emissionFactor value.
     */
    GLfloat getEmssionFactor();

    /**
     * @brief set the side of the skybox cube.
     *
     * @param _side
     */
    GLvoid setCubeSide(GLfloat _cubeSide);

    /**
     * @brief returns the side length of the skybox cube.
     *
     * @returns the side length of the skybox cube.
     */
    GLfloat getCubeSide();

    /**
     * @brief the draw function of the skybox.
     *
     */
    GLvoid draw();

private:

    Skin *skin; /**< It is the skybox skin.  */
    QVector<GLfloat> emissionVector; /**< It is the skybox emissionVector. */
    QVector<GLfloat> disabledVector; /**< It is the vector used to disable components in OGL. */
    GLfloat cubeSide; /**< It is the skybox cube side length. */
};

#endif // SKYBOX_H
