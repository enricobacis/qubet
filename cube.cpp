#include "cube.h"
#include "cube_defines.h"
#include "effects_defines.h"

Cube::Cube(Level *level, Skin *_skin, QObject *_parent):
    skin(_skin),
    parent(_parent),
    state(0),
    t(0)
{
    connect(parent, SIGNAL(keyPressedSignal(QKeyEvent*)), this, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(playEffect(QString)), parent, SIGNAL(playEffect(QString)));

    createNormalsMatrix();

    gravity = level->getGravity();
    levelCellsLength = (int)(level->getLength() / 3.0f);
    levelCellsWidth = (int)(level->getWidth() / 3.0f);
}

Cube::~Cube()
{
    this->disconnect(parent);
    parent->disconnect(this);
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
    if (!(state & CUBESTATE_JUMPING))
    {
        state = state | CUBESTATE_JUMPING;
        playEffect(EFFECT_JUMPSMALL);
    }
}

bool Cube::isMoving()
{
    if (state & (CUBESTATE_MOVING_LEFT | CUBESTATE_MOVING_RIGHT))
        return true;
    else
        return false;
}

void Cube::moveLeft()
{
    if (!(state & CUBESTATE_MOVING_LEFT))
    {
        state = state | CUBESTATE_MOVING_LEFT;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::moveRight()
{
    if (!(state & CUBESTATE_MOVING_RIGHT))
    {
        state = state | CUBESTATE_MOVING_RIGHT;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::draw()
{
//    if (collided)
//    {
//        for (int k = 0; k < 8; k++)
//        {
//            for (int j = 0; j < 8; j++)
//            {
//                for (int i = 0; i < 8; i++)
//                {
//                    glPushMatrix();
//                        glTranslatef(normsMatrices[i][j][k]->x, normsMatrices[i][j][k]->y, normsMatrices[i][j][k]->z);
//                        glTranslatef(normsMatrices[i][j][k]->x * cos(3.14f * t/100.0f));
//                        glTranslatef(normsMatrices[i][j][k]->z * cos(3.14f * t/100.0f));
//                        glTranslatef(normsMatrices[i][j][k]->y * sin(3.14f * t/100.0f) - (((t/100.0f) * (t/100.0f)) * gravity / 2.0f));
//                        drawPrism((1-(t/100.0f)) * 3.0f / 8.0f, (1-(t/100.0f)) * 3.0f / 8.0f, (1-(t/100.0f)) * 3.0f / 8.0f);
//                    glPopMatrix();
//                }
//            }
//        }
//    } else {
//    }
}

void Cube::updatePosition()
{

}

void Cube::createNormalsMatrix()
{
    GLfloat gap = 3.0f / 4.0f;
    Vector3f *tempNorm = new Vector3f(0.0f, 0.0f, -3.0f * gap);
    for (int k = 0; k < 4; k++)
    {
        tempNorm->y -= 3.0f * gap;

        for (int j = 0; j < 4; j++)
        {
            tempNorm->x -= 3.0f * gap;

            for (int i = 0; i < 4; i++)
            {
                normalsMatrix[i][j][k] = tempNorm;
                tempNorm->x += gap;
            }

            tempNorm->x -= 3.0f * gap;
            tempNorm->y += gap;
        }

        tempNorm->x -= 3.0f * gap;
        tempNorm->y -= 3.0f * gap;
        tempNorm->z += gap;
    }
}

void Cube::explode()
{

}

void Cube::collided()
{
    explode();
}

void Cube::keyPressed(QKeyEvent *event)
{
    int key = event->key();

    switch(key)
    {
    case Qt::Key_Space:
        jump();
        break;

    case Qt::Key_Left:
        moveLeft();
        break;

    case Qt::Key_Right:
        moveRight();
        break;
    }
}
