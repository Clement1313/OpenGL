#include "matrix4.hh"

using namespace mygl;

matrix4::matrix4()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            this->mat[i][j] = 0.0f;
        }
    }
}

matrix4::matrix4(GLfloat mat[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            this->mat[i][j] = mat[i][j];
        }
    }
}

matrix4 matrix4::identity()
{
    GLfloat id[4][4] = { { 1.0f, 0.0f, 0.0f, 0.0f },
                         { 0.0f, 1.0f, 0.0f, 0.0f },
                         { 0.0f, 0.0f, 1.0f, 0.0f },
                         { 0.0f, 0.0f, 0.0f, 1.0f } };
    return matrix4(id);
}

void matrix4::operator*=(const matrix4& rhs)
{
    GLfloat result[4][4] = { { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f } };

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result[i][j] += mat[i][k] * rhs.mat[k][j];
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = result[i][j];
        }
    }
}

matrix4 matrix4::operator*(const matrix4& rhs)
{
    GLfloat result[4][4] = { { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f },
                             { 0.0f, 0.0f, 0.0f, 0.0f } };

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result[i][j] += mat[i][k] * rhs.mat[k][j];
            }
        }
    }

    return result;
}

ostream& mygl::operator<<(std::ostream& out, const mygl::matrix4& m)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            out << m.mat[i][j] << ", ";
        }
        out << "\n";
    }

    return out;
}
