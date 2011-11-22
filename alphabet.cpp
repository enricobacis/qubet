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


#include "alphabet.h"

Alphabet::Alphabet()
{
    // Inizializzo il generatore di numeri casuali
    qsrand(QTime::currentTime().msec());
}

Alphabet::~Alphabet()
{
    for (QMap<QChar,Letter*>::iterator i = lettersList.begin(); i != lettersList.end(); i++)
    {
        if (i.value() != NULL)
            dynamic_cast<Letter*>(i.value())->~Letter();
    }

    lettersList.~QMap();
}

Skin *Alphabet::getRandomLetterSkin(QChar letter)
{
    letter = letter.toLower();
    Skin *skin = new Skin();
    bool empty = true;

    if (lettersList.find(letter) != lettersList.end())
    {
        QList<GLuint> textureIDs = lettersList.value(letter)->getRandomTextures(6);

        if (!textureIDs.isEmpty())
        {
            for (int i = 0; i < 6; i++)
                skin->setTexture(i, textureIDs.at(i));

            empty = false;
        }
    }

    if (empty)
    {
        for (int i = 0; i < 6; i++)
            skin->setTexture(i, 0);
    }

    return skin;
}

GLuint Alphabet::getRandomLetterTexture(QChar letter)
{
    letter = letter.toLower();
    GLuint texture = 0;

    if (lettersList.find(letter) != lettersList.end())
        lettersList.value(letter)->getRandomTexture();

    return texture;
}

QList<GLuint> Alphabet::getRandomLetterTextures(QChar letter, GLint numberOfTextures)
{
    letter = letter.toLower();
    QList<GLuint> textures;

    if ((numberOfTextures > 0) && lettersList.find(letter) != lettersList.end())
    {
        textures = lettersList.value(letter)->getRandomTextures(numberOfTextures);
    }
    else
    {
        for (int i = 0; i < 6; i++)
            textures.append(0);
    }

    return textures;
}

QList<GLuint> Alphabet::getAllLetterTextures(QChar letter)
{
    letter = letter.toLower();
    QList<GLuint> textures;

    if (lettersList.find(letter) != lettersList.end())
        textures = lettersList.value(letter)->getAllTextures();

    return textures;
}

GLvoid Alphabet::appendLetterTexture(QChar letter, GLuint textureID)
{
    letter = letter.toLower();

    if (lettersList.find(letter) == lettersList.end())
        lettersList.insert(letter, new Letter(letter));

    lettersList.value(letter)->appendTexture(textureID);
}
