#ifndef SKYBOX_H
#define SKYBOX_H

#include "utilities.h"

/**
 * @brief It is the Skybox Class.
 *
 * @version 1.0
 * @author \#34
 */
class Skybox
{

public:

    /**
     * @brief Create a Skybox object.
     *
     * @param _skin is the skin to use for the Skybox.
     * @param _emissionFactor is the emission factor of the Skybox.
     * @param _cubeSide is the side of the Skybox cube.
     */
    explicit Skybox(Skin *_skin, GLfloat _emissionFactor = 0.6f, GLfloat _cubeSide = 40.0f);

    /**
     * @brief Safely destroy skybox object.
     */
    ~Skybox();

    /**
     * @brief Set the Skybox Skin.
     *
     * @param _skin is the skin to use for the Skybox.
     */
    GLvoid setSkin(Skin *_skin);

    /**
     * @brief Returns the Skybox Skin.
     *
     * @returns the Skybox Skin.
     */
    Skin *getSkin();

    /**
     * @brief Set the emission factor of the Skybox.
     *
     * @param _emissionFactor is the emission factor of the Skybox.
     */
    GLvoid setEmissionFactor(GLfloat _emissionFactor);

    /**
     * @brief Returns the emission factor of the Skybox.
     *
     * @returns the emission factor of the Skybox.
     */
    GLfloat getEmssionFactor();

    /**
     * @brief Set the side of the Skybox cube.
     *
     * @param _cubeSide is the side of the Skybox cube.
     */
    GLvoid setCubeSide(GLfloat _cubeSide);

    /**
     * @brief Returns the side of the Skybox cube.
     *
     * @returns the side of the Skybox cube.
     */
    GLfloat getCubeSide();

    /**
     * @brief Draw the Skybox.
     */
    GLvoid draw();

private:

    Skin *skin; /**< It is the Skybox Skin. */
    QVector<GLfloat> emissionVector; /**< It is the Skybox emission vector. */
    QVector<GLfloat> disabledVector; /**< It is the vector used to disable components in OGL. */
    GLfloat cubeSide; /**< It is the Skybox cube side length. */
};

#endif // SKYBOX_H
