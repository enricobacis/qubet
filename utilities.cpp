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
    if (id == 1)
    {
        drawPrism(3.0f, 3.0f, 3.0f);
    }
    else if (id == 2)
    {
        //glEnable(GL_TEXTURE_2D);

        // Front Face (Z+)
        //glBindTexture();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  0.0f,  1.0f);
        glVertex3f(-3.0f, 0.0f,  1.5f);
        glVertex3f( 0.0f, 0.0f,  1.5f);
        glVertex3f( 0.0f, 3.0f,  1.5f);
        glVertex3f(3.0f,  3.0f,  1.5f);
        glVertex3f(-3.0f, 0.0f,  1.5f);
        glVertex3f( 0.0f, 0.0f,  1.5f);
        glVertex3f( 0.0f, 3.0f,  1.5f);
        glVertex3f(3.0f,  3.0f,  1.5f);
        glVertex3f(3.0f,  -3.0f, 1.5);
        glVertex3f(-3.0f, -3.0f, 1.5f);
        glVertex3f(-3.0f, -3.0f, 1.5f);

        glEnd();

        // Back Face (Z-)
        //glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureZMinus()));
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  0.0f,  -1.0f);
        glVertex3f(-3.0f, 0.0f,  -1.5f);
        glVertex3f( 0.0f, 0.0f,  -1.5f);
        glVertex3f( 0.0f, 3.0f,  -1.5f);
        glVertex3f(3.0f,  3.0f,  -1.5f);
        glVertex3f(-3.0f, 0.0f,  -1.5f);
        glVertex3f( 0.0f, 0.0f,  -1.5f);
        glVertex3f( 0.0f, 3.0f,  -1.5f);
        glVertex3f(3.0f,  3.0f,  -1.5f);
        glVertex3f(3.0f,  -3.0f, -1.5f);
        glVertex3f(-3.0f, -3.0f, -1.5f);
        glVertex3f(-3.0f, -3.0f, -1.5f);

        glEnd();

        // Top Face (Y+)
        //glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureYPlus()));
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  1.0f,  0.0f);
        glVertex3f(0.0f, 3.0f,  -1.5f);
        glVertex3f(0.0f,  3.0f,  1.5f);
        glVertex3f(3.0f, 3.0f,  1.5f);
        glVertex3f(3.0f, 3.0f,  -1.5f);
        glEnd();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  1.0f,  0.0f);
        glVertex3f(0.0f, 0.0f,  -1.5f);
        glVertex3f(0.0f,  0.0f,  1.5f);
        glVertex3f(-3.0f, 0.0f,  1.5f);
        glVertex3f(-3.0f, 0.0f,  -1.5f);
        glEnd();


        // Bottom Face (Y-)
        //glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureYMinus()));
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  -1.0f,  0.0f);
        glVertex3f(-3.0f, -3.0f,  1.5f);
        glVertex3f(3.0f, -3.0f,  1.5f);
        glVertex3f(3.0f, -3.0f,  -1.5f);
        glVertex3f(-3.0f, -3.0f,  -1.5f);
        glEnd();

        // Right face (X+)
        //glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureXPlus()));
        glBegin(GL_QUADS);
        glNormal3f(1.0f,  0.0f,  0.0f);
        glVertex3f(3.0f, 3.0f,  1.5f);
        glVertex3f(3.0f,  -3.0f,  1.5f);
        glVertex3f(3.0f, -3.0f,  -1.5f);
        glVertex3f(3.0f, 3.0f,  -1.5f);
        glEnd();

        // Left Face (X-)
        //glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureXMinus()));
        glBegin(GL_QUADS);
        glNormal3f(-1.0f,  0.0f,  0.0f);
        glVertex3f(0.0f, 3.0f,  1.5f);
        glVertex3f(0.0f,  3.0f,  -1.5f);
        glVertex3f(0.0f, 0.0f,  -1.5f);
        glVertex3f(0.0f, 0.0f,  1.5f);
        glEnd();
        glBegin(GL_QUADS);
        glNormal3f(-1.0f,  0.0f,  0.0f);
        glVertex3f(-3.0f, 0.0f,  -1.5f);
        glVertex3f(-3.0f,  0.0f,  1.5f);
        glVertex3f(-3.0f, -3.0f,  1.5f);
        glVertex3f(-3.0f, -3.0f,  -1.5f);
        glEnd();

        //glBindTexture(GL_TEXTURE_2D, 0);
        //glDisable(GL_TEXTURE_2D);
    }
    else if (id == 2)
    {
        //Front Face Z+
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  0.0f,  1.0f);
        glVertex3f(1.5f, 3.0f,  1.5f);
        glVertex3f(-1.5f,  3.0f,  1.5f);
        glVertex3f(-1.5f, -3.0f,  1.5f);
        glVertex3f(1.5f, -3.0f,  1.5f);
        glEnd();

        //Front Face Z-
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(1.5f, 3.0f, -1.5f);
        glVertex3f(-1.5f, 3.0f, -1.5f);
        glVertex3f(-1.5f, -3.0f, -1.5f);
        glVertex3f(1.5f, -3.0f, -1.5f);
        glEnd();

        //Top Face Y+
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.5f, 3.0f, 1.5f);
        glVertex3f(1.5f, 3.0f, -1.5f);
        glVertex3f(-1.5f, 3.0f, -1.5f);
        glVertex3f(-1.5f, 3.0f, 1.5f);
        glEnd();

        //Bottom Face Y-
        glBegin(GL_QUADS);
        glNormal3f(0.0f,  -1.0f,  0.0f);
        glVertex3f(1.5f, -3.0f, 1.5f);
        glVertex3f(1.5f, -3.0f, -1.5f);
        glVertex3f(-1.5f, -3.0f, -1.5f);
        glVertex3f(-1.5f, -3.0f, 1.5f);
        glEnd();

        //Left Face X-
        glBegin(GL_QUADS);
        glNormal3f(-1.0f,  0.0f,  0.0f);
        glVertex3f(-1.5f, 3.0f,  1.5f);
        glVertex3f(-1.5f,  3.0f, -1.5f);
        glVertex3f(-1.5f, -3.0f, -1.5f);
        glVertex3f(-1.5f, -3.0f, 1.5f);
        glEnd();

        //Left Face X+
        glBegin(GL_QUADS);
        glNormal3f(1.0f,  0.0f,  0.0f);
        glVertex3f(1.5f, 3.0f,  1.5f);
        glVertex3f(1.5f,  3.0f, -1.5f);
        glVertex3f(1.5f, -3.0f, -1.5f);
        glVertex3f(1.5f, -3.0f, 1.5f);
        glEnd();

    }
}
