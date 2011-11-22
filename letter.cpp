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


#include "letter.h"

Letter::Letter(QChar _letter) :
    letter(_letter)
{
}

Letter::~Letter()
{
    textures.~QList();
}

GLuint Letter::getRandomTexture()
{
    QList<GLuint> sequence = getRandomTextures(1);

    return (sequence.isEmpty() ? 0 : sequence.first());
}

QList<GLuint> Letter::getRandomTextures(int numberOfTextures)
{
    QList<int> indices = getRandomUniqueSequence(0, textures.count() - 1, numberOfTextures);
    QList<GLuint> sequence;

    while (!indices.isEmpty())
        sequence.append(textures.at(indices.takeFirst()));

    return sequence;
}

QList<GLuint> Letter::getAllTextures()
{
    return textures;
}

GLvoid Letter::appendTexture(GLuint textureID)
{
    if (!textures.contains(textureID))
        textures.append(textureID);
}

QList<int> Letter::getRandomUniqueSequence(int from, int to, int cases)
{
    QList<int> sequence;
    int delta = to - from;

    if (delta > 0)
    {
        if (cases <= delta)
        {
            // Sequenza senza ripetizioni
            QList<int> numbers;
            int extracted;

            for (int i = from; i <= to; i++)
                numbers.append(i);

            // Estrazioni
            for (int i = 0; i < cases; i++)
            {
                extracted = qrand() % (delta + 1);
                sequence.append(numbers.at(extracted));
                numbers.removeAt(extracted);
                delta--;
            }
        }
        else
        {
            // Sequenza con ripetizioni
            for (int i = 0; i < cases; i++)
                sequence.append((qrand() % (delta + 1)) + from);
        }
    }

    return sequence;
}
