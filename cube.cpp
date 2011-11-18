#include "cube.h"
#include "cube_defines.h"
#include "effects_defines.h"

Cube::Cube(Level *level, Skin *_skin, QObject *_parent):
    skin(_skin),
    parent(_parent),
    position(new Vector3f())
    deaths(0)
{
    startXCell = (int)(((level->getWidth() / 3) - 1) / 2);
    resetCube();

    connect(parent, SIGNAL(keyPressedSignal(QKeyEvent*)), this, SLOT(keyPressed(QKeyEvent*)));
    connect(parent, SIGNAL(collision()), this, SLOT(collided()));
    connect(this, SIGNAL(playEffect(QString)), parent, SIGNAL(playEffect(QString)));
    connect(this, SIGNAL(explosionFinished()), parent, SLOT(explosionFinished()));
    connect(this, SIGNAL(levelCompleted()), parent, SLOT(levelCompleted()));

    createNormalsMatrix();

    gravity = level->getGravity();
    levelCellsLength = (int)(level->getLength() / 3.0f);
    levelCellsWidth = (int)(level->getWidth() / 3.0f);

    jumpVelocity = gravity / 2;
}

Cube::~Cube()
{
    this->disconnect(parent);
    parent->disconnect(this);
}

Vector3f *Cube::getPosition()
{
    return new Vector3f(position);
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
    if (!isMoving() && (xCell > 0))
    {
        state = state | CUBESTATE_MOVING_LEFT;
        xCell--;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::moveRight()
{
    if (!isMoving() && (xCell < levelCellsWidth - 1))
    {
        state = state | CUBESTATE_MOVING_RIGHT;
        xCell++;
        playEffect(EFFECT_JUMP);
    }
}

void Cube::draw()
{
    glPushMatrix();
    glTranslatef(position->x, position->y, 0.0f);

    if (state & CUBESTATE_COLLIDED)
    {
        for (int k = 0; k < 4; k++)
            for (int j = 0; j < 4; j++)
                for (int i = 0; i < 4; i++)
                    drawExplosion(i, j, k);

        explosionStep += 5;
        if(explosionStep == 100)
        {
            explosionStep = 0;
            state = state & ~CUBESTATE_COLLIDED;
            resetCube();
            emit explosionFinished();
        }
    }
    else
    {
        updatePosition();
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        drawPrism(3.0f, 3.0f, 3.0f, skin);
    }

    glPopMatrix();
}

void Cube::updatePosition()
{
    position->z += 0.5;

    if (position->z >= levelCellsLength * 3.0f)
    {
        completed();
        return;
    }

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
            position->y = 3 * (((-0.5f) * gravity * pow((jumpStep/(10.0f * gravity)), 2.0 )) + (gravity / 2.0f) * (jumpStep / (10.0f*gravity) ));
            //position->y = (jumpStep/20.0f) - (0.015f * pow(jumpStep, 2.0) / gravity) ;
            jumpStep += 4;
        }
    }

    if (state & (CUBESTATE_MOVING_LEFT | CUBESTATE_MOVING_RIGHT))
    {
        if (movingStep >= 25)
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
                normalsMatrix[i][j][k] = new Vector3f(((qrand() % 2)+1 )*(-1.125f + (gap*i)),
                                                      ((qrand() % 2)+1 ) *(-1.125f + (gap*j)),
                                                      ((qrand() % 2)+1 ) *(-1.125f + (gap*k)));
                anglesMatrix[i][j][k] = new Vector3f(qrand(), qrand(), qrand());
            }

}

void Cube::drawExplosion(int i, int j, int k)
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

void Cube::explode()
{
    state = state | CUBESTATE_COLLIDED;
}

void Cube::completed()
{
    playEffect(EFFECT_HEREWEGO);
    // emit levelCompleted();
    resetCube();
}

void Cube::resetCube()
{
    xCell = startXCell;
    position->x = startXCell * 3.0f;
    position->y = 0.0f;
    position->z = 0.0f;
    state = 0;
    jumpStep = 0;
    movingStep = 0;
    explosionStep = 0;
}

void Cube::collided()
{
    playEffect(EFFECT_EXPLOSION);
    playEffect(EFFECT_HAHA);
    explode();
    createNormalsMatrix();
    deaths++;
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
        collided();
        break;
    }
}
