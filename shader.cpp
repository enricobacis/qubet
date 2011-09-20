#include "shader.h"

Shader::Shader(QString _vertexFilename, QString _fragmentFilename) :
    vertexFilename(_vertexFilename),
    fragmentFilename(_fragmentFilename)
{
    const char *vertexShaderText = readText(vertexFilename);
    const char *fragmentShaderText = readText(fragmentFilename);

    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    programID = glCreateProgram();

    glShaderSource(vertexShaderID, 1, &vertexShaderText, NULL);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderText, NULL);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    glAttachShader(programID, fragmentShaderID);
    glAttachShader(programID, vertexShaderID);

    glLinkProgram(programID);
}

const char *Shader::readText(QString filename)
{
    FILE *fp;
    char *content = NULL;
    int count = 0;
    bool error = false;

    if (filename != NULL)
    {
        fp = fopen(filename.toStdString().c_str(), "rt");
        if (fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);

            if (count > 0)
            {
                content = (char *)malloc(sizeof(char) * (count + 1));
                count = fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }
            else
                error = true;

            fclose(fp);
        }
        else
            error = true;
    }
    else
        error = true;

    if (error)
        cout << "Errore lettura file: " << (filename == NULL ? "NULL" : filename.toStdString()) << endl;

    return content;
}

GLuint Shader::getProgramID()
{
    return programID;
}
