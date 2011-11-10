#include "cube.h"

Cube::Cube(Level *_level, Skin *_skin, QObject *_parent):
    sideLength(),
    normsMatrix(),
    t(0)
{
    createNormsMatrix();
}

void Cube::createNormsMatrix()
{
    GLfloat gap = sideLength/8.0f;
    Vector3f *tempNorm = new Vector3f(0.0f, 0.0f, -3.0f*gap);
    for(int k = 0; k < 8; k++)
        {
            tempNorm->y -= 3.0f*gap;

            for(int j = 0; j < 8; j++)
            {
                tempNorm->x -= 3.0f*gap;

                for(int i = 0; i < 8; i++)
                {
                    normsMatrix[i][j][k] = tempNorm;
                    tempNorm->x += gap;
                }
                tempNorm->x -= 3.0f*gap;
                tempNorm->y += gap;
            }
            tempNorm->x -= 3.0f*gap;
            tempNorm->y -= 3.0f*gap;
            tempNorm->z += gap;
        }
}

Cube::~Cube()
{

}

Vector3f *Cube::getPosition()
{
    return position;
}

void Cube::setPosition(Vector3f *_position)
{
    position = _position;
}

void Cube::jump()
{

}

void Cube::draw()
{
    /*
    if(collided)
    {
        for(int k = 0; k < 8; k++)
        {
            for(int j = 0; j < 8; j++)
            {
                for(int i = 0; i < 8; i++)
                {
                    glPushMatrix();
                        glTranslatef(normsMatrices[i][j][k]->x, normsMatrices[i][j][k]->y, normsMatrices[i][j][k]->z);
                        glTranslatef(normsMatrices[i][j][k]->x * cos(3.14f * t/100.0f));
                        glTranslatef(normsMatrices[i][j][k]->z * cos(3.14f * t/100.0f));
                        glTranslatef(normsMatrices[i][j][k]->y * sin(3.14f * t/100.0f) - (((t/100.0f) * (t/100.0f)) * gravity / 2.0f));
                        drawPrism((1-(t/100.0f)) * sideLength / 8.0f, (1-(t/100.0f)) * sideLength / 8.0f, (1-(t/100.0f)) * sideLength / 8.0f);
                    glPopMatrix();
                }
            }
        }
    }else{
    **/

    //}
}

void Cube::updatePosition()
{

}

void Cube::collided()
{

}

void Cube::keyPressed(QKeyEvent *e)
{

}
