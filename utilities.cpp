#include "utilities.h"

GLvoid drawRectangle(GLfloat x, GLfloat y)
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

GLvoid drawCubesButton(QString label, QVector<GLint> angles, GLint Name)
{
   GLint lettersNumber = label.length();
   glPushMatrix();
        glTranslatef(-(lettersNumber -1) * 1.5, 0, 0);
        for (GLint i = 0; i < lettersNumber; i++)
        {
            glPushName(Name);
            glPushMatrix();
                glRotatef(angles.at(i), 1, 0, 0);
                drawPrism(3, 3, 3);
            glPopMatrix();
            glPopName();
            glTranslatef(3, 0, 0);
            Name++;
        }
   glPopMatrix();
}
