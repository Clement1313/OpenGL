#ifndef TRANSFORM_HH
#define TRANSFORM_HH

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <iostream>

#include "matrix4.hh"

using namespace std;

namespace mygl
{

    matrix4 look_at(const GLfloat& eyeX, const GLfloat& eyeY,
                    const GLfloat& eyeZ, const GLfloat& centerX,
                    const GLfloat& centerY, const GLfloat& centerZ,
                    const GLfloat& upX, const GLfloat& upY, const GLfloat& upZ);

    matrix4 glFrustum(GLfloat& left, GLfloat& right, GLfloat& bottom,
                      GLfloat& top, GLfloat& z_near, GLfloat& z_far);

    struct vec3
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;

        vec3(GLfloat x, GLfloat y, GLfloat z)
            : x(x)
            , y(y)
            , z(z)
        {}

        vec3 cross(const vec3& o) const
        {
            return vec3(y * o.z - z * o.y, z * o.x - x * o.z,
                        x * o.y - y * o.x);
        }
    };

    struct vec4
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;

        vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        {}
    };

} // namespace mygl

#endif
