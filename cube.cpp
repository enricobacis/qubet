#include "cube.h"
#include "cube_defines.h"
#include "effects_defines.h"

Cube::Cube(Level *level, Skin *_skin, QObject *_parent):
    skin(_skin),
    parent(_parent),
    position(new Vector3f(0.0f, 0.0f, 0.0f)),
    state(0),
    jumpStep(0),
    movingStep(0),
    explosionStep(0),
    xCell(0)
{
    connect(parent, SIGNAL(keyPressedSignal(QKeyEvent*)), this, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(playEffect(QString)), parent, SIGNAL(playEffect(QString)));

    createNormalsMatrix();

    gravity = level->getGravity();
    levelCellsLength = (int)(level->getLength() / 3.0f);
    levelCellsWidth = (int)(level->getWidth() / 3.0f);

    jumpVelocity = gravity/2;
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
    return (state & (CUBESTATE_MOVING_LEFT | CUBESTATE_MOVING_RIGHT)) ? true : false;
}

void Cube::moveLeft()
{
    if (!isMoving() && -xCell < ((int)((levelCellsWidth - 1) / 2)))
    {
        state = state | CUBESTATE_MOVING_LEFT;
        xCell--;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::moveRight()
{
    if (!isMoving() && xCell < ((int)((levelCellsWidth - 1) / 2)))
    {
        state = state | CUBESTATE_MOVING_RIGHT;
        xCell++;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::draw()
{
    glPushMatrix();
    glTranslatef(position->x, position->y, position->z);

    if (state & CUBESTATE_COLLIDED)
    {
        for (int k = 0; k < 4; k++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    glPushMatrix();
                    glTranslatef(normalsMatrix[i][j][k]->x,
                                 normalsMatrix[i][j][k]->y ,normalsMatrix[i][j][k]->z);
                    glTranslatef( 4.0f * normalsMatrix[i][j][k]->x * (explosionStep/100.0f),
                                  4.0f * normalsMatrix[i][j][k]->y * (explosionStep/100.0f),
                                  4.0f * normalsMatrix[i][j][k]->z * (explosionStep/100.0f));

                    glRotatef(anglesMatrix[i][j][k]->x, 1.0f, 0.0f, 0.0f);
                    glRotatef(anglesMatrix[i][j][k]->y, 0.0f, 1.0f, 0.0f);
                    glRotatef(anglesMatrix[i][j][k]->x, 0.0f, 0.0f, 1.0f);

                    drawPrism(((1-(explosionStep/100.0f)) * 3.0f) / 4.0f,
                              ((1-(explosionStep/100.0f)) * 3.0f) / 4.0f,
                              ((1-(explosionStep/100.0f)) * 3.0f) / 4.0f);

                    glPopMatrix();
                }
            }
        }
        explosionStep += 5;
        if(explosionStep == 100)
        {
            explosionStep = 0;
            state = state & ~CUBESTATE_COLLIDED;
        }
    }
    else
    {
        updatePosition();
        drawPrism(3.0f, 3.0f, 3.0f);
    }

    glPopMatrix();
}

void Cube::updatePosition()
{
    if (state & CUBESTATE_JUMPING)
    {
        if (jumpStep > 100)
        {
            jumpStep = 0;
            position->y = 0;
            state = state & ~CUBESTATE_JUMPING;
        }
        else
        {
            position->y = 3 * (((-0.5f) * gravity * pow((jumpStep/100.0f), 2.0 )) + jumpVelocity * (jumpStep / 100.0f ));
            jumpStep += 4;
        }
    }

    if (state & (CUBESTATE_MOVING_LEFT | CUBESTATE_MOVING_RIGHT))
    {
        if (movingStep > 25)
        {
            movingStep = 0;
            state = state & ~CUBESTATE_MOVING_LEFT & ~CUBESTATE_MOVING_RIGHT;
        }
        else
        {
            position->x += (state & CUBESTATE_MOVING_LEFT) ? -0.12f : 0.12f;
            movingStep++;
        }
    }
}

void Cube::createNormalsMatrix()
{
    GLfloat gap = 3.0f / 4.0f;
    for (int k = 0; k < 4; k++)
        for (int j = 0; j < 4; j++)
            for (int i = 0; i < 4; i++)
            {
                normalsMatrix[i][j][k] = new Vector3f((-1.125f + (gap*i)),
                                                      (-1.125f + (gap*j)),
                                                      (-1.125f + (gap*k)));
                anglesMatrix[i][j][k] = new Vector3f(qrand(), qrand(), qrand());
            }

}

void Cube::explode()
{
    state = state | CUBESTATE_COLLIDED;
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
    case Qt::Key_Up:
        jump();
        break;

    case Qt::Key_Left:
        moveLeft();
        break;

    case Qt::Key_Right:
        moveRight();
        break;

    case Qt::Key_C:
        explode();
        break;
    }
}
