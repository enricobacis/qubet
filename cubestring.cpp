#include "cubestring.h"

CubeString::CubeString(QString _label, GLfloat _cubeDimension, GLuint _name, Alphabet *_alphabet) :
    label(_label),
    cubeDimension(_cubeDimension),
    name(_name),
    alphabet(_alphabet)
{
    init();
}

CubeString::CubeString(QString _label, GLfloat _maxWidth, GLfloat _maxHeight, GLuint _name, Alphabet *_alphabet) :
    label(_label),
    name(_name),
    alphabet(_alphabet)
{
    // Calcolo della dimensione
    if (length > 1)
    {
        cubeDimension = _maxWidth/length;
        if (cubeDimension > _maxHeight)
            cubeDimension = _maxHeight;
    }

    init();
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

GLuint CubeString::getName()
{
    return name;
}

GLvoid CubeString::startLetterRotation(GLuint _letterName, GLint _angleStep, GLint _turns)
{
    if (_letterName >= GLuint(length))
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

GLvoid CubeString::startStringRotation(GLint _angleStep, GLint _turns)
{
    for (int letter = 0; letter < length; letter++)
        startLetterRotation(letter, _angleStep, _turns);
}

GLboolean CubeString::isRotating(GLuint _letterName)
{
    return (angleSteps[_letterName] == 0 ? false : true);
}

GLfloat CubeString::setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta)
{
    GLfloat currentAngle = _firstLetterAngle;
    for (int letter = 0; letter < length; letter++)
    {
        currentAngles[letter] = currentAngle;
        currentAngle += _nextLetterDelta;
    }

    return currentAngle;
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

GLvoid CubeString::init()
{
    length = label.length();

    for (int i = 0; i < length; i++)
    {
        angleSteps.append(0);
        currentAngles.append(0);
        finalAngles.append(0);

        if (label[i] == ' ')
            letterDisplayLists.append(0);
        else
            letterDisplayLists.append(createLetterDisplayList(label[i]));
    }
}
