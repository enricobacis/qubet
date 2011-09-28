#include "cubestring.h"

CubeString::CubeString(QString _label, GLfloat _cubeDimension, GLuint _name, Alphabet *_alphabet) :
    label(_label),
    cubeDimension(_cubeDimension),
    name(_name),
    alphabet(_alphabet)
{
    length = label.length();

    for (int i = 0; i < length; i++)
    {
        angleSteps.append(0);
        currentAngles.append(0);
        finalAngles.append(0);

        letterDisplayLists.append(createLetterDisplayList(label[i]));
    }
}

CubeString::~CubeString()
{
    for (int i = 0; i < letterDisplayLists.count(); i++)
    {
        if (letterDisplayLists[i] != 0)
            glDeleteLists(letterDisplayLists[i], 1);
    }
}

GLvoid CubeString::draw(GLboolean simplifyForPicking)
{
    GLuint currentName = 0;

    glPushName(name);
    glPushMatrix();

    glTranslatef(-(length - 1)*(cubeDimension/2), 0.0, 0.0);

        for (int i = 0; i < length; i++)
        {
            // Increment After
            glPushName(currentName++);
            glPushMatrix();

                if (!simplifyForPicking)
                {
                    if (currentAngles[i] != finalAngles[i])
                    {
                        currentAngles[i] += angleSteps[i];
                    }
                    else if (angleSteps[i] != 0)
                    {
                        currentAngles[i] = currentAngles[i] % 360;
                        finalAngles[i] = finalAngles[i] % 360;
                        angleSteps[i] = 0;
                    }
                }

                glRotatef(currentAngles[i], 1.0, 0.0, 0.0);
                glCallList(letterDisplayLists[i]);
            glPopMatrix();
            glPopName();

            glTranslatef(cubeDimension, 0.0, 0.0);
        }

    glPopMatrix();
    glPopName();
}

QString CubeString::getLabel()
{
    return label;
}

GLvoid CubeString::startLetterRotation(GLuint _letterName, GLint _angleStep, GLint _turns)
{
    if ((_letterName < 0) || (_letterName >= length))
        return;

    angleSteps[_letterName] = _angleStep;
    finalAngles[_letterName] += _turns * 90;

    if ((finalAngles[_letterName] - currentAngles[_letterName]) * angleSteps[_letterName] < 0)
    {
        // Rotazione corrente e Rotazione richiesta incompatibili
        finalAngles[_letterName] = -finalAngles[_letterName];
        currentAngles[_letterName] = -currentAngles[_letterName];
    }
}

GLboolean CubeString::isRotating(GLuint _letterName)
{
    return (angleSteps[_letterName] == 0 ? false : true);
}

GLuint CubeString::createLetterDisplayList(QChar letter)
{
    return createLetterDisplayList(alphabet->getRandomLetterSkin(letter));
}

GLuint CubeString::createLetterDisplayList(Skin *_skin)
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    drawPrism(cubeDimension, cubeDimension, cubeDimension, _skin, true);
    glEndList();
    return list;
}
