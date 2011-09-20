#include "utilities.h"

GLvoid drawSquare(GLfloat x, GLfloat y)
{
    x = x/2;
    y = y/2;

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y,  0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y,  0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y,  0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y,  0.0f);

    glEnd();
}

GLvoid drawPrism(GLfloat x, GLfloat y, GLfloat z)
{
    x = x/2;
    y = y/2;
    z = z/2;

    glBegin(GL_QUADS);

        // Front Face
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y,  z);

        // Back Face
        glNormal3f(0.0f, 0.0f,-1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-x,  y, -z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-x,  y, -z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x,  y, -z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y, -z);

        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y, -z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,  y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);

        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, -y, -z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x, -y, -z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, -y,  z);

        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y, -z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y,  z);

        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, -z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, -y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-x,  y,  z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y, -z);

    glEnd();
}
