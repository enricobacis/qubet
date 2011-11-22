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


#include "cubestringlist.h"

CubeStringList::CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet) :
    name(0),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(_labels, _cubeDimension, _alphabet);
}

CubeStringList::CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension) :
    name(0),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(_labels, _maxWidth, _maxHeight, _alphabet, _maxCubeDimension);
}

CubeStringList::CubeStringList(QString _labels, GLfloat _cubeDimension, Alphabet *_alphabet, GLuint _name) :
    name(_name),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(splitLabels(_labels), _cubeDimension, _alphabet);
}

CubeStringList::CubeStringList(QString _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension, GLuint _name) :
    name(_name),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(splitLabels(_labels), _maxWidth, _maxHeight, _alphabet, _maxCubeDimension);
}

CubeStringList::~CubeStringList()
{
    CubeString *cubeString = NULL;

    while (!cubeStrings.isEmpty())
    {
        cubeString = cubeStrings.takeFirst();
        if (cubeString != NULL)
            cubeString->~CubeString();
    }
}

GLvoid CubeStringList::draw(GLboolean simplifyForPicking)
{
    CubeString *cubeString = NULL;

    if (name != 0)
        glPushName(name);

    glPushMatrix();

        glTranslatef(0.0f, firstStringHeight, 0.0f);

        for (int i = 0; i < cubeStrings.count(); i++)
        {
            cubeString = cubeStrings.at(i);
            if (cubeString != NULL)
                cubeString->draw(simplifyForPicking);

            glTranslatef(0.0f, -stringsHeightDelta, 0.0f);
        }

    glPopMatrix();

    if (name != 0)
        glPopName();
}

GLint CubeStringList::getLabelCount()
{
    return cubeStrings.count();
}

QString CubeStringList::getLabel(GLuint _stringName)
{
    QString label;
    CubeString *cubeString = getCubeStringFromName(_stringName);

    if (cubeString != NULL)
        label = cubeString->getLabel();

    return label;
}

GLvoid CubeStringList::startLetterRotation(GLuint _stringName, GLuint _letterName, GLint _angleStep, GLint _turns)
{
    getCubeStringFromName(_stringName)->startLetterRotation(_letterName, _angleStep, _turns);
}

GLvoid CubeStringList::startStringRotation(GLuint _stringName, GLint _angleStep, GLint _turns)
{
    getCubeStringFromName(_stringName)->startStringRotation(_angleStep, _turns);
}

GLvoid CubeStringList::startStringListRotation(GLint _angleStep, GLint _turns)
{
    CubeString *cubeString = NULL;

    for (int i = 0; i < cubeStrings.count(); i++)
    {
        cubeString = cubeStrings.at(i);
        if (cubeString != NULL)
            cubeString->startStringRotation(_angleStep, _turns);
    }
}

GLboolean CubeStringList::isRotating(GLuint _stringName, GLuint _letterName)
{
    return getCubeStringFromName(_stringName)->isRotating(_letterName);
}

GLfloat CubeStringList::setCurrentAngle(GLfloat _firstLetterAngle, GLfloat _nextLetterDelta)
{
    GLfloat angle = _firstLetterAngle;
    CubeString *cubeString = NULL;

    for (int i = 0; i < cubeStrings.count(); i++)
    {
        cubeString = cubeStrings.at(i);
        if (cubeString != NULL)
            angle = cubeString->setCurrentAngle(angle, _nextLetterDelta);
    }

    return angle;
}

GLvoid CubeStringList::computeHeights(GLfloat _cubeDimension)
{
    int strings = cubeStrings.count();

    if (strings < 2)
    {
        firstStringHeight = 0.0f;
        stringsHeightDelta = 0.0f;
    }
    else
    {
        firstStringHeight = (((strings - 1) * _cubeDimension) + ((strings - 1) * interline)) / 2;
        stringsHeightDelta = _cubeDimension + interline;
    }
}

CubeString *CubeStringList::getCubeStringFromName(GLuint _name)
{
    CubeString *cubeString = NULL;
    CubeString *result = NULL;

    for (int i = 0; i < cubeStrings.count(); i++)
    {
        cubeString = cubeStrings.at(i);

        if (cubeString != NULL)
        {
            if (cubeString->getName() == _name)
            {
                result = cubeString;
                break;
            }
        }
    }

    return result;
}

CubeString *CubeStringList::getCubeStringFromLabel(QString _label)
{
    CubeString *cubeString = NULL;
    CubeString *result = NULL;

    for (int i = 0; i < cubeStrings.count(); i++)
    {
        cubeString = cubeStrings.at(i);

        if (cubeString != NULL)
        {
            if (cubeString->getLabel() == _label)
            {
                result = cubeString;
                break;
            }
        }
    }

    return result;
}

QList< QPair<QString,GLuint> > CubeStringList::splitLabels(QString _labels)
{
    GLuint currentName = 0;
    QStringList stringList = _labels.split(" ", QString::SkipEmptyParts);
    QList< QPair<QString,GLuint> > labels;

    for (int i = 0; i < stringList.count(); i++)
    {
        QPair<QString,GLuint> pair;
        pair.first = stringList.at(i);
        pair.second = currentName++;
        labels.append(pair);
    }

    return labels;
}

GLvoid CubeStringList::init(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet)
{
    int strings = _labels.count();

    for (int i = 0; i < strings; i++)
    {
        CubeString *cubeString = new CubeString(_labels.at(i).first, _cubeDimension, _alphabet, _labels.at(i).second);
        cubeStrings.append(cubeString);
    }

    interline = _cubeDimension * 0.66f;
    computeHeights(_cubeDimension);
}

GLvoid CubeStringList::init(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet, GLfloat _maxCubeDimension)
{
    int strings = _labels.count();

    GLfloat cubeDimension = 0.0f;

    if (strings > 0)
    {
        // Trovo la dimensione massima
        int maxLength = 1;

        for (int i = 0; i < strings; i++)
            maxLength = qMax(maxLength, _labels.at(i).first.length());

        GLfloat cubeWidth = _maxWidth / maxLength;
        GLfloat cubeHeight = _maxHeight / ((strings * 1.66f) - 0.66f);

        cubeDimension = qMin(cubeWidth, cubeHeight);

        if (_maxCubeDimension > 0.0f)
            cubeDimension = qMin(cubeDimension, _maxCubeDimension);
    }

    init(_labels, cubeDimension, _alphabet);
}
