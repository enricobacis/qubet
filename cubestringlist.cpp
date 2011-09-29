#include "cubestringlist.h"

CubeStringList::CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _cubeDimension, Alphabet *_alphabet) :
    name(0),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(_labels, _cubeDimension, _alphabet);
}

CubeStringList::CubeStringList(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet) :
    name(0),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(_labels, _maxWidth, _maxHeight, _alphabet);
}

CubeStringList::CubeStringList(QString _labels, GLfloat _cubeDimension, GLuint _name, Alphabet *_alphabet) :
    name(_name),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(splitLabels(_labels), _cubeDimension, _alphabet);
}

CubeStringList::CubeStringList(QString _labels, GLfloat _maxWidth, GLfloat _maxHeight, GLuint _name, Alphabet *_alphabet) :
    name(_name),
    firstStringHeight(0),
    stringsHeightDelta(0)
{
    init(splitLabels(_labels), _maxWidth, _maxHeight, _alphabet);
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

        glTranslatef(0.0, firstStringHeight, 0.0);

        for (int i = 0; i < cubeStrings.count(); i++)
        {
            cubeString = cubeStrings.at(i);
            if (cubeString != NULL)
                cubeString->draw(simplifyForPicking);

            glTranslatef(0.0, -stringsHeightDelta, 0.0);
        }

    glPopMatrix();

    if (name != 0)
        glPopName();
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

GLint CubeStringList::setCurrentAngle(GLint _firstLetterAngle, GLint _nextLetterDelta)
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
        firstStringHeight = 0;
        stringsHeightDelta = 0;
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
        CubeString *cubeString = new CubeString(_labels.at(i).first, _cubeDimension, _labels.at(i).second, _alphabet);
        cubeStrings.append(cubeString);
    }

    interline = _cubeDimension * 0.66;
    computeHeights(_cubeDimension);
}

GLvoid CubeStringList::init(QList< QPair<QString,GLuint> > _labels, GLfloat _maxWidth, GLfloat _maxHeight, Alphabet *_alphabet)
{
    int strings = _labels.count();

    // Trovo la dimensione massima
    int maxLength = 0;

    for (int i = 0; i < strings; i++)
        maxLength = qMax(maxLength, _labels.at(i).first.length());

    GLfloat cubeWidth = _maxWidth / maxLength;
    GLfloat cubeHeight = (_maxHeight - (strings - 1)*interline) / strings;

    GLfloat cubeDimension = qMin(cubeWidth, cubeHeight);

    init(_labels, cubeDimension, _alphabet);
}
