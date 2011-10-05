#include "utilities.h"

GLvoid drawRectangle(GLfloat x, GLfloat y, GLuint texture)
{
    x = x/2;
    y = y/2;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y,  0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y,  0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y,  0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y,  0.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

GLvoid drawPrism(GLfloat x, GLfloat y, GLfloat z, Skin *skin, GLboolean invertBackTexture)
{
    x = x/2;
    y = y/2;
    z = z/2;

    glEnable(GL_TEXTURE_2D);

    // Front Face (Z+)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureZPlus()));
    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y,  z);

    glEnd();

    // Back Face (Z-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureZMinus()));
    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f,-1.0f);

        if (invertBackTexture)
        {
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, -y, -z);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,  y, -z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( x,  y, -z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( x, -y, -z);
        }
        else
        {
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, -y, -z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-x,  y, -z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f( x,  y, -z);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y, -z);
        }

    glEnd();

    // Top Face (Y+)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureYPlus()));
    glBegin(GL_QUADS);

        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y, -z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,  y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);

    glEnd();

    // Bottom Face (Y-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureYMinus()));
    glBegin(GL_QUADS);

        glNormal3f( 0.0f,-1.0f, 0.0f);

        if (invertBackTexture)
        {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, -z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y, -z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( x, -y,  z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, -y,  z);
        }
        else
        {
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, -y, -z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f( x, -y, -z);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y,  z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, -y,  z);
        }

    glEnd();

    // Right face (X+)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureXPlus()));
    glBegin(GL_QUADS);

        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y, -z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y,  z);

    glEnd();

    // Left Face (X-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureXMinus()));
    glBegin(GL_QUADS);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, -z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, -y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-x,  y,  z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y, -z);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

GLvoid drawObstacle(GLuint id)
{
    switch (id)
    {
    case 0:
        drawPrism(3.0f, 3.0f, 3.0f);
        break;

    case 1:
        glBegin(GL_QUADS);

            glNormal3f(-1.0f,  0.0f,  0.0f);
            glVertex3f(-3.0f, -3.0f,  1.5f);
            glVertex3f(-3.0f, -3.0f, -1.5f);
            glVertex3f(-3.0f,  0.0f, -1.5f);
            glVertex3f(-3.0f,  0.0f,  1.5f);

            glNormal3f( 0.0f,  1.0f,  0.0f);
            glVertex3f(-3.0f,  0.0f,  1.5f);
            glVertex3f(-3.0f,  0.0f, -1.5f);
            glVertex3f( 0.0f,  0.0f, -1.5f);
            glVertex3f( 0.0f,  0.0f,  1.5f);

            glNormal3f(-1.0f,  0.0f,  0.0f);
            glVertex3f( 0.0f,  0.0f,  1.5f);
            glVertex3f( 0.0f,  0.0f, -1.5f);
            glVertex3f( 0.0f,  3.0f, -1.5f);
            glVertex3f( 0.0f,  3.0f,  1.5f);

            glNormal3f( 0.0f,  1.0f,  0.0f);
            glVertex3f( 0.0f,  3.0f,  1.5f);
            glVertex3f( 0.0f,  3.0f, -1.5f);
            glVertex3f( 3.0f,  3.0f, -1.5f);
            glVertex3f( 3.0f,  3.0f,  1.5f);

            glNormal3f( 1.0f,  0.0f,  0.0f);
            glVertex3f( 3.0f,  3.0f,  1.5f);
            glVertex3f( 3.0f,  3.0f, -1.5f);
            glVertex3f( 3.0f, -3.0f, -1.5f);
            glVertex3f( 3.0f, -3.0f,  1.5f);

            glNormal3f( 0.0f, -1.0f,  0.0f);
            glVertex3f( 3.0f, -3.0f,  1.5f);
            glVertex3f( 3.0f, -3.0f, -1.5f);
            glVertex3f(-3.0f, -3.0f, -1.5f);
            glVertex3f(-3.0f, -3.0f,  1.5f);

        glEnd();

        glBegin(GL_TRIANGLE_STRIP);

            glNormal3f( 0.0f,  0.0f,  1.0f);
            glVertex3f(-3.0f, -3.0f,  1.5f);
            glVertex3f(-3.0f,  0.0f,  1.5f);
            glVertex3f( 3.0f, -3.0f,  1.5f);
            glVertex3f( 0.0f,  0.0f,  1.5f);
            glVertex3f( 3.0f,  3.0f,  1.5f);
            glVertex3f( 0.0f,  3.0f,  1.5f);

        glEnd();

        glBegin(GL_TRIANGLE_STRIP);

            glNormal3f( 0.0f,  0.0f, -1.0f);
            glVertex3f(-3.0f, -3.0f, -1.5f);
            glVertex3f(-3.0f,  0.0f, -1.5f);
            glVertex3f( 3.0f, -3.0f, -1.5f);
            glVertex3f( 0.0f,  0.0f, -1.5f);
            glVertex3f( 3.0f,  3.0f, -1.5f);
            glVertex3f( 0.0f,  3.0f, -1.5f);

        glEnd();

        break;

    case 2:
        drawPrism(3.0f, 6.0f, 3.0f);
        break;

    case 3:
        drawPrism(6.0f, 6.0f, 6.0f);
        break;
    }
}

Vector3f *getOGLPosition(GLfloat x, GLfloat y, GLfloat z)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];

    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    y = (GLfloat)viewport[3] - (GLfloat)y;
    gluUnProject(x, y, z, modelview, projection, viewport, &posX, &posY, &posZ);

    return new Vector3f(posX, posY, posZ);
}

Vector3f *getOGLPosition(GLfloat x, GLfloat y)
{
    GLfloat z;
    glReadPixels(x, GLint(y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

    return getOGLPosition(x, y, z);
}
