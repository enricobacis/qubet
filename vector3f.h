#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>
#include <GL/gl.h>

struct Vector3f
{
    GLfloat x, y, z;

    //Constructors
    Vector3f()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3f(const Vector3f &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Vector3f(const Vector3f *v)
    {
        x = v->x;
        y = v->y;
        z = v->z;
    }

    Vector3f(const GLfloat newx, const GLfloat newy, const GLfloat newz)
    {
        x = newx;
        y = newy;
        z = newz;
    }

    Vector3f(const GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    //operator overloading
    inline GLvoid operator=(const GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    inline GLvoid operator+=(const Vector3f a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
    }

    inline GLvoid copyInto(GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    //referencing as array
    inline GLfloat &operator[](GLint i)
    {
        switch(i)
        {
        case 0:
            return x;

        case 1:
            return y;

        case 2:
            return z;
        }

    }

    inline const GLfloat &operator[](GLint i) const
    {
        switch(i)
        {
        case 0:
            return x;

        case 1:
            return y;

        case 2:
            return z;
        }
    }

    //vector length square
    inline GLfloat lengthSq()
    {
        return pow(x,2) + pow(y,2) + pow(z,2);
    }

    //vector length
    inline GLfloat length()
    {
        return sqrt(lengthSq());
    }

    //normalization
    inline GLvoid normalize()
    {
        GLfloat l = length();
        x = x/l;
        y = y/l;
        z = z/l;
    }

    //set to zero
    inline GLvoid zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    //check if it is zero
    inline bool isZero()
    {
        if ((x == 0) && (y == 0) && (z == 0))
            return true;
        else
            return false;
    }

    //set to argument values
    inline GLvoid set(const GLfloat newx, const GLfloat newy, const GLfloat newz)
    {
        x = newx;
        y = newy;
        z = newz;
    }

    //dot product
    inline GLfloat dot(const Vector3f &v)
    {
        return x*v.x + y*v.y + z*v.z;
    }

    //cross product
    inline Vector3f *cross(const Vector3f &v)
    {
        GLfloat newx = y*v.z - z*v.y;
        GLfloat newy = z*v.x - x*v.z;
        GLfloat newz = x*v.y - y*v.x;
        return new Vector3f(newx, newy, newz);
    }

    //projections
    inline GLvoid projectOnXY()
    {
        z = 0;
    }

    inline GLvoid projectOnYX()
    {
        return projectOnXY();
    }

    inline GLvoid projectOnXZ()
    {
        y = 0;
    }

    inline GLvoid projectOnZX()
    {
        return projectOnXZ();
    }

    inline GLvoid projectOnYZ()
    {
        x = 0;
    }

    inline GLvoid projectOnZY()
    {
        return projectOnYZ();
    }

    //rotations
    inline GLvoid rotateX(const GLfloat angle)
    {
        GLfloat newy = y*cos(angle) - z*sin(angle);
        z = y*sin(angle) + z*cos(angle);
        y = newy;
    }

    inline GLvoid rotateY(const GLfloat angle)
    {
        GLfloat newx = x*cos(angle) + z*sin(angle);
        z = -x*sin(angle) + z*cos(angle);
        x = newx;
    }

    inline GLvoid rotateZ(const GLfloat angle)
    {
        GLfloat newx = x*cos(angle) - y*sin(angle);
        y = x*sin(angle) + y*cos(angle);
        x = newx;
    }

    inline GLvoid rotate(const Vector3f &axis, const GLfloat angle)
    {
        // calcolo la phi per portare il sistema di riferimento di axis sul piano YZ
        Vector3f axy = new Vector3f(axis);
        axy.projectOnXY();
        GLfloat phi = atan2(axy.x, axy.y);

        // ruoto il sistema di riferimento sul piano YZ
        Vector3f *a1 = new Vector3f(axis);
        a1->rotateZ(phi);
        rotateZ(phi);

        // calcolo la theta per spostare axis sull'asse Z
        GLfloat theta = atan2(a1->y, a1->z);

        // ruoto solo il punto nel nuovo sistema di riferimento, l'asse ora Ã¨ Z
        rotateX(theta);

        // effettuo la rotazione richiesta
        rotateZ(angle);

        // torno al sistema di riferimento originale di axis
        rotateX(-theta);
        rotateZ(-phi);
    }

    inline Vector3f* getOneOrthogonal()
    {
        Vector3f *ortho;
        if ((x == 0) && (z == 0))
            ortho = new Vector3f(1, 0, 0);

        else if (z == 0)
            ortho = new Vector3f(0, 0, 1);

        else
            ortho = new Vector3f(1, 0, -x/z);

        ortho->normalize();
        return ortho;
    }
};

//operators

//equality
inline bool operator==(const Vector3f &v1, const Vector3f &v2)
{
    if ((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
        return true;
    else
        return false;
}

//vector sum
inline Vector3f operator+(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

//vector difference
inline Vector3f operator-(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

//vector-scalar product
inline Vector3f operator*(const Vector3f &v, const GLfloat &a)
{
    return Vector3f(a*v.x, a*v.y, a*v.z);
}

//scalar-vector product
inline Vector3f operator*(const GLfloat &a, const Vector3f &v)
{
    return operator*(v, a);
}

// unary minus
inline Vector3f operator-(const Vector3f &v)
{
    return operator*(v, -1);
}

#endif // VECTOR3F_H
