//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "cubestring.h"

CubeString::CubeString(QString _label, GLfloat _cubeDimension, Alphabet *_alphabet, GLuint _name) :
    label(_label),
    cubeDimension(_cubeDimension),
    name(_name),
    alphabet(_alphabet)
{
    init();
}

CubeString::CubeString(QString _label, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension, GLuint _name) :
    label(_label),
    name(_name),
    alphabet(_alphabet)
{
    // Calcolo della dimensione
    int length = label.length();

    if (length > 1)
    {
        cubeDimension = qMin((_maxWidth / length), _maxHeight);

        if (_maxCubeDimension > 0)
            cubeDimension = qMin(cubeDimension, _maxCubeDimension);
    }

    init();
}

CubeString::~CubeString()
{
#ifdef USE_DISPLAY_LISTS_FOR_LETTERS

    for (int i = 0; i < letterDisplayLists.count(); i++)
        if (letterDisplayLists.at(i) != 0)
            glDeleteLists(letterDisplayLists.at(i), 1);

#else

    for (int i = 0; i < letterSkins.count(); i++)
        if (letterSkins.at(i) != NULL)
            letterSkins.at(i)->~Skin();

#endif
}

GLvoid CubeString::draw(GLboolean simplifyForPicking)
{
    GLuint currentName = 0;
    int length = label.length();

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

#ifdef USE_DISPLAY_LISTS_FOR_LETTERS

                if (letterDisplayLists[i] != 0)
                    glCallList(letterDisplayLists[i]);

#else

                if (letterSkins[i] != NULL)
                    drawPrism(cubeDimension, cubeDimension, cubeDimension, letterSkins[i], true);

#endif

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
    // Check Parameters Validity
    if (_letterName >= GLuint(label.length()))
        return;

    if (_angleStep == 0)
        return;

    GLint turnDegrees = _turns * 90;

    // Check Rotation Validity
    if (angleSteps[_letterName] != 0)
    {
        // Already Rotating
        finalAngles[_letterName] += turnDegrees;
        if ((angleSteps[_letterName] % _angleStep) == 0)
            angleSteps[_letterName] = _angleStep;
    }
    else
    {
        // Not Already Rotating
        if ((turnDegrees % _angleStep) == 0)
        {
            angleSteps[_letterName] = _angleStep;
            finalAngles[_letterName] += turnDegrees;
        }
    }
}

GLvoid CubeString::startStringRotation(GLint _angleStep, GLint _turns)
{
    for (int letter = 0; letter < label.length(); letter++)
        startLetterRotation(letter, _angleStep, _turns);
}

GLboolean CubeString::isRotating(GLuint _letterName)
{
    return (angleSteps[_letterName] == 0 ? false : true);
}

GLfloat CubeString::setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta)
{
    GLfloat currentAngle = _firstLetterAngle;

    for (int letter = 0; letter < label.length(); letter++)
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
    for (int i = 0; i < label.length(); i++)
    {
        angleSteps.append(0);
        currentAngles.append(0);
        finalAngles.append(0);

#ifdef USE_DISPLAY_LISTS_FOR_LETTERS

        if (label[i] == ' ')
            letterDisplayLists.append(0);
        else
            letterDisplayLists.append(createLetterDisplayList(label[i]));

#else

        if (label[i] == ' ')
            letterSkins.append(NULL);
        else
            letterSkins.append(alphabet->getRandomLetterSkin(label[i]));

#endif

    }
}
