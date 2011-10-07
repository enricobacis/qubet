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
        drawPrism(6.0f, 6.0f, 3.0f);
        break;
    }
}

Vector3f *getModelViewPos(Vector3f *vect, bool computeZDepth)
{
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (GLfloat)vect->x;
    winY = (GLfloat)viewport[3] - vect->y;

    if (computeZDepth)
        glReadPixels(GLint(winX), GLint(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    else
        winZ = vect->z;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return new Vector3f(posX, posY, posZ);
}

Vector3f *getProjectionPos(Vector3f *vect)
{
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat objX, objY, objZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    objX = (GLfloat)vect->x;
    objY = (GLfloat)vect->y;
    objZ = (GLfloat)vect->z;

    gluProject(objX, objY, objZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return new Vector3f(posX, posY, posZ);

    // c'e' da sistemare le coordinate per OpenGL se si vuole fare una funzione generale.
}

Vector3f *getPointFromParametricLine(Vector3f* p0, Vector3f* p1, GLfloat t)
{
    GLfloat xr, yr, zr;

    xr = p0->x + t*(p1->x - p0->x);
    yr = p0->y + t*(p1->y - p0->y);
    zr = p0->z + t*(p1->z - p0->z);

    return new Vector3f(xr, yr, zr);
}

Vector3f *getObstacleBoundingBox(GLuint id)
{
    switch (id)
    {
    case 0:
        return new Vector3f(3.0f, 3.0f, 3.0f);
        break;

    case 1:
        return new Vector3f(6.0f, 6.0f, 3.0f);
        break;

    case 2:
        return new Vector3f(3.0f, 6.0f, 3.0f);
        break;

    case 3:
        return new Vector3f(6.0f, 6.0f, 3.0f);
        break;
    }
}
