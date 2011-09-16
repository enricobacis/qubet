#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>
#include <GL/gl.h>

/**
 * @brief Structure that rapresents a Vector of float in a 3-D space.
 *
 * @version 1.0
 * @author \#34
 */
struct Vector3f
{
    GLfloat x; /**< It is the x coordinate. */
    GLfloat y; /**< It is the y coordinate. */
    GLfloat z; /**< It is the z coordinate. */

    //Constructors
    /**
     * @brief Create a new Vector3f in coordinates (0, 0, 0).
     */
    Vector3f()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    /**
     * @brief Create a new Vector3f copying the coordinates of v.
     *
     * @param v is the other vector to copy coordinates.
     */
    Vector3f(const Vector3f &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    /**
     * @brief Create a new Vector3f copying the coordinates of v.
     *
     * @param v is the other vector to copy coordinates.
     */
    Vector3f(const Vector3f *v)
    {
        x = v->x;
        y = v->y;
        z = v->z;
    }

    /**
     * @brief Create a Vector3f using the coordinates of parameters.
     *
     * @param _x is the coordinate of x.
     * @param _y is the coordinate of y.
     * @param _z is the coordinate of z.
     */
    Vector3f(const GLfloat _x, const GLfloat _y, const GLfloat _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    /**
     * @brief Create a Vector3f using the coordinates of array a[].
     *
     * @param a[] is the array to copy coordinates.
     */
    Vector3f(const GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    /**
     * @brief Operator = overloading function.
     *
     * @param a[] is the array to copy coordinates.
     */
    inline GLvoid operator=(const GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    /**
     * @brief Operator += overloading function.
     *
     * @param a is the vector to sum to the current vector.
     */
    inline GLvoid operator+=(const Vector3f a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
    }

    /**
     * @brief Copy the array a content in the vector.
     *
     * @param a[] is the array to copy coordinates.
     */
    inline GLvoid copyInto(GLfloat a[3])
    {
        x = a[0];
        y = a[1];
        z = a[2];
    }

    /**
     * @brief Operator [] overloading function.
     *
     * @param i is the index [1, 3].
     * @return GLfloat coordinate.
     */
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

    /**
     * @brief Operator [] overloading function.
     *
     * @param i is the index [1, 3].
     * @return const GLfloat coordinate
     */
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

    /**
     * @brief Compute the lenght^2 of the vector.
     *
     * The lenght^2 is less resource expensive then length().
     * You can use it for check which vector is longer.
     *
     * @return GLfloat lenght^2 of vector.
     */
    inline GLfloat lengthSq()
    {
        return pow(x,2) + pow(y,2) + pow(z,2);
    }

    /**
     * @brief Compute the length of the vector.
     *
     * If you have to check only which vector among others
     * is longer you can use the lengthSq() function that
     * is less resource expensive.
     *
     * @return GLfloat length of the vector.
     */
    inline GLfloat length()
    {
        return sqrt(lengthSq());
    }

    /**
     * @brief Normalize a vector.
     */
    inline GLvoid normalize()
    {
        GLfloat l = length();
        x = x/l;
        y = y/l;
        z = z/l;
    }

    /**
     * @brief Set all cordinates of the vector to zero.
     */
    inline GLvoid zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    //check if it is zero
    /**
     * @brief Check if the vector is (0, 0, 0).
     *
     * @return GLboolean true if it is (0, 0, 0), else false.
     */
    inline GLboolean isZero()
    {
        if ((x == 0) && (y == 0) && (z == 0))
            return true;
        else
            return false;
    }

    /**
     * @brief Set the vector coordinates.
     *
     * @param _x is the coordinate of x.
     * @param _y is the coordinate of y.
     * @param _z is the coordinate of z.
     */
    inline GLvoid set(const GLfloat _x, const GLfloat _y, const GLfloat _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    // Products

    /**
     * @brief Compute the dot product of the vector with the vector v.
     *
     * @param v the other vector to compute the dot product.
     * @return GLfloat the dot product.
     */
    inline GLfloat dot(const Vector3f &v)
    {
        return x*v.x + y*v.y + z*v.z;
    }

    /**
     * @brief Compute the cross product of the vector with the vector v.
     *
     * @param v the other vector to compute the cross product.
     * @return Vector3f* the cross product.
     */
    inline Vector3f *cross(const Vector3f &v)
    {
        GLfloat newx = y*v.z - z*v.y;
        GLfloat newy = z*v.x - x*v.z;
        GLfloat newz = x*v.y - y*v.x;
        return new Vector3f(newx, newy, newz);
    }

    // Projections

    /**
     * @brief Compute the XY plan projection.
     */
    inline GLvoid projectOnXY()
    {
        z = 0;
    }

    /**
     * @brief Compute the YX plan projection.
     */
    inline GLvoid projectOnYX()
    {
        return projectOnXY();
    }

    /**
     * @brief Compute the XZ plan projection.
     */
    inline GLvoid projectOnXZ()
    {
        y = 0;
    }

    /**
     * @brief Compute the ZX plan projection.
     */
    inline GLvoid projectOnZX()
    {
        return projectOnXZ();
    }

    /**
     * @brief Compute the YZ plan projection.
     */
    inline GLvoid projectOnYZ()
    {
        x = 0;
    }

    /**
     * @brief Compute the ZY plan projection.
     */
    inline GLvoid projectOnZY()
    {
        return projectOnYZ();
    }

    // Rotations

    /**
     * @brief Rotate on the x axis.
     *
     * @param angle is the angle of rotation.
     */
    inline GLvoid rotateX(const GLfloat angle)
    {
        GLfloat newy = y*cos(angle) - z*sin(angle);
        z = y*sin(angle) + z*cos(angle);
        y = newy;
    }

    /**
     * @brief Rotate on the y axis.
     *
     * @param angle is the angle of rotation.
     */
    inline GLvoid rotateY(const GLfloat angle)
    {
        GLfloat newx = x*cos(angle) + z*sin(angle);
        z = -x*sin(angle) + z*cos(angle);
        x = newx;
    }

    /**
     * @brief Rotate on the z axis.
     *
     * @param angle is the angle of rotation.
     */
    inline GLvoid rotateZ(const GLfloat angle)
    {
        GLfloat newx = x*cos(angle) - y*sin(angle);
        y = x*sin(angle) + y*cos(angle);
        x = newx;
    }

    /**
     * @brief Rotate on the parameter given axis.
     *
     * @param axis is the axis on which compute the rotation.
     * @param angle is the angle of rotation.
     */
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

    /**
     * @brief Compute one of the orthogonal vectors of the vector.
     *
     * @return Vector3f* an orthogonal vector.
     */
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

// Operators

/**
 * @brief Operator == overloading function.
 *        It Checks if two vectors are equals.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return GLboolean true if v1 and v2 are equal, else false.
 */
inline GLboolean operator==(const Vector3f &v1, const Vector3f &v2)
{
    if ((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
        return true;
    else
        return false;
}

/**
 * @brief Operator + overloading function.
 *        Compute the sum of two vectors.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return Vector3f is the sum of v1 and v2.
 */
inline Vector3f operator+(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

/**
 * @brief Operator - overloading function.
 *        Compute the difference of two vectors.
 *
 * @param v1 the first vector.
 * @param v2 the second vector.
 * @return Vector3f is the difference of v1 and v2.
 */
inline Vector3f operator-(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/**
 * @brief Operator * overloading function.
 *        Compute the scalar product of a scalar and a vector.
 *
 * @param v is the vector.
 * @param a is the scalar.
 * @return Vector3f is the scalar product a*v.
 */
inline Vector3f operator*(const Vector3f &v, const GLfloat &a)
{
    return Vector3f(a*v.x, a*v.y, a*v.z);
}

/**
 * @brief Operator * overloading function.
 *        Compute the scalar product of a scalar and a vector.
 *
 * @param a is the scalar.
 * @param v is the vector.
 * @return Vector3f is the scalar product a*v.
 */
inline Vector3f operator*(const GLfloat &a, const Vector3f &v)
{
    return operator*(v, a);
}

/**
 * @brief Operator unary - overloading function.
 *        Multiply for -1 all vector components.
 *
 * @param v is the vector.
 * @return Vector3f is the negated vector.
 */
inline Vector3f operator-(const Vector3f &v)
{
    return operator*(v, -1);
}

#endif // VECTOR3F_H
