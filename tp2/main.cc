#include "matrix4.hh"
#include "program.hh"
#include "transform.hh"
#include "program.hh"

#include <GL/freeglut.h>
#include <GL/glew.h>

using namespace std;
using namespace mygl;

int main(int argc, char* argv[]) {
    program p = program();
    current_program = &p;
    p.init_glut(argc, argv);
    p.init_glew();
    p.init_gl();
    p.init_shaders();
    p.init_object();
    p.init_POV();
    
    glutMainLoop();

    return 0;
}