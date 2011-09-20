#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>

using namespace std;

/**
 * @brief
 *
 */
class Shader  : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief
     *
     * @param _vertexFilename
     * @param _fragmentFilename
     */
    Shader(QString _vertexFilename, QString _fragmentFilename);

    /**
     * @brief
     *
     * @param filename
     */
    const char *readText(QString filename);

    /**
     * @brief
     *
     */
    GLuint getProgramID();

private:
    QString vertexFilename; /**< TODO */
    QString fragmentFilename; /**< TODO */
    GLuint programID; /**< TODO */
    GLuint vertexShaderID; /**< TODO */
    GLuint fragmentShaderID; /**< TODO */
};

#endif // SHADER_H
