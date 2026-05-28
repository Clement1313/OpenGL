#include "matrix4.hh"
#include "program.hh"
#include "transform.hh"

#include <GL/freeglut.h>
#include <GL/glew.h>

using namespace std;
using namespace mygl;

int main(int argc, char* argv[]) {
    init_glut(argc, argv);
    init_glew();
    init_gl();

    // init_shaders();
    // init_object();
    // init_POV ( ) ;
    
    glutMainLoop();

    return 0;
}