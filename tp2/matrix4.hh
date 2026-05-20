#ifndef MATRIX4_HH
#define MATRIX4_HH

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <iostream>

using namespace std;

namespace mygl
{
    class matrix4
    {
    public:
        matrix4();
        matrix4(GLfloat mat[4][4]);
        void operator*=(const matrix4& rhs);
        matrix4 operator*(const matrix4& rhs);
        static matrix4 identity();
        GLfloat mat[4][4];

    private:
    };

    ostream& operator<<(std::ostream& out, const mygl::matrix4& m);

} // namespace mygl

#endif
