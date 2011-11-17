#include "utilities.h"
#include "defines.h"

GLvoid drawRectangle(GLfloat x, GLfloat y, GLuint texture)
{
    x = x / 2;
    y = y / 2;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture);
    setTextureClampToEdge();

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
    x = x / 2;
    y = y / 2;
    z = z / 2;

    glEnable(GL_TEXTURE_2D);

    // Front Face (Z+)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureZPlus()));
    setTextureClampToEdge();

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y,  z);

    glEnd();

    // Back Face (Z-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureZMinus()));
    setTextureClampToEdge();

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
    setTextureClampToEdge();

    glBegin(GL_QUADS);

        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x,  y, -z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x,  y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);

    glEnd();

    // Bottom Face (Y-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureYMinus()));
    setTextureClampToEdge();

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
    setTextureClampToEdge();

    glBegin(GL_QUADS);

        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y, -z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x,  y, -z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x,  y,  z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( x, -y,  z);

    glEnd();

    // Left Face (X-)
    glBindTexture(GL_TEXTURE_2D, (skin == NULL ? 0 : skin->getTextureXMinus()));
    setTextureClampToEdge();

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

GLvoid setTextureClampToEdge()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GLvoid drawObstacle(GLuint id)
{
    switch (id)
    {
    case 0:
        drawPrism(3.0f, 3.0f, 3.0f);
        break;

    case 1:
        drawPrism(3.0f, 6.0f, 3.0f);
        break;

    case 2:
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

Vector3f *getPointFromParametricLine(Vector3f *p0, Vector3f *p1, GLfloat t)
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
        return new Vector3f(3.0f, 6.0f, 3.0f);
        break;

    case 2:
        return new Vector3f(6.0f, 6.0f, 3.0f);
        break;

    case 3:
        return new Vector3f(6.0f, 6.0f, 3.0f);
        break;
    }

    return NULL;
}

GLvoid setMaterialColor(int color)
{
    QVector<GLfloat> mat_ambient;
    QVector<GLfloat> mat_diffuse;
    QVector<GLfloat> mat_specular;
    QVector<GLfloat> mat_emission;

    switch (color)
    {
    case COLOR_DISABLED:
        mat_ambient  << 0.2f << 0.2f << 0.2f << 1.0f;
        mat_diffuse  << 0.8f << 0.8f << 0.8f << 1.0f;
        mat_specular << 0.0f << 0.0f << 0.0f << 1.0f;
        mat_emission << 0.0f << 0.0f << 0.0f << 1.0f;
        break;

    case COLOR_RED:
        mat_ambient  << 0.2f << 0.0f << 0.0f << 1.0f;
        mat_diffuse  << 0.8f << 0.0f << 0.0f << 1.0f;
        mat_specular << 0.1f << 0.0f << 0.0f << 1.0f;
        mat_emission << 0.1f << 0.0f << 0.0f << 1.0f;
        break;

    case COLOR_GREEN:
        mat_ambient  << 0.0f << 0.2f << 0.0f << 1.0f;
        mat_diffuse  << 0.0f << 0.8f << 0.0f << 1.0f;
        mat_specular << 0.0f << 0.1f << 0.0f << 1.0f;
        mat_emission << 0.0f << 0.1f << 0.0f << 1.0f;
        break;

    case COLOR_BLUE:
        mat_ambient  << 0.0f << 0.0f << 0.2f << 1.0f;
        mat_diffuse  << 0.0f << 0.0f << 0.8f << 1.0f;
        mat_specular << 0.0f << 0.0f << 0.1f << 1.0f;
        mat_emission << 0.0f << 0.0f << 0.1f << 1.0f;
        break;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_ambient.data());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  mat_diffuse.data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular.data());
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission.data());
}

GLvoid setMaterialColor(QColor color)
{
    QVector<GLfloat> mat_ambient;
    QVector<GLfloat> mat_diffuse;
    QVector<GLfloat> mat_specular;
    QVector<GLfloat> mat_emission;

    mat_ambient  << color.redF() / 4.0f << color.greenF() / 4.0f << color.blueF() / 4.0f << 1.0f;
    mat_diffuse  << color.redF() << color.greenF() << color.blueF() << 1.0f;
    mat_specular << color.redF() / 8.0f << color.greenF() / 8.0f << color.blueF() / 8.0f << 1.0f;
    mat_emission << color.redF() / 8.0f << color.greenF() / 8.0f << color.blueF() / 8.0f << 1.0f;

    glMaterialfv(GL_FRONT, GL_DIFFUSE,  mat_ambient.data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse.data());
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_specular.data());
    glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_emission.data());
}
