#include "transform.hh"

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <iostream>
#include <math.h>

#include "matrix4.hh"

using namespace std;

namespace mygl
{
    matrix4 look_at(const GLfloat& eyeX, const GLfloat& eyeY,
                    const GLfloat& eyeZ, const GLfloat& centerX,
                    const GLfloat& centerY, const GLfloat& centerZ,
                    const GLfloat& upX, const GLfloat& upY, const GLfloat& upZ)
    {
        GLfloat a = centerX - eyeX;
        GLfloat b = centerY - eyeY;
        GLfloat c = centerZ - eyeZ;

        GLfloat norm = sqrt(a * a + b * b + c * c);
        vec3 F = vec3(a / norm, b / norm, c / norm);

        vec3 up = vec3(upX, upY, upZ);
        vec3 s = F.cross(up);

        vec3 correct_up = s.cross(F);

        GLfloat rep_mat[4][4] = { { s.x, s.y, s.z, 0.0f },
                                  { correct_up.x, correct_up.y, correct_up.z,
                                    0.0f },
                                  { -F.x, -F.y, -F.z, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };

        matrix4 rep = matrix4(rep_mat);

        GLfloat eye_mat[4][4] = { { 1.0f, 0.0f, 0.0f, -eyeX },
                                  { 0.0f, 1.0f, 0.0f, -eyeY },
                                  { 0.0f, 0.0f, 1.0f, -eyeZ },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };

        matrix4 eye = matrix4(eye_mat);

        matrix4 L = rep * eye;
        return L;
    }

    matrix4 glFrustum(GLfloat& left, GLfloat& right, GLfloat& bottom,
                      GLfloat& top, GLfloat& z_near, GLfloat& z_far)
    {}

} // namespace mygl