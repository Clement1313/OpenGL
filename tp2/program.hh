#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

using namespace std;

namespace mygl
{
    class program;

    extern program* current_program;
    void display();

    class program
    {
    public:
        GLuint vertex_shader_id;
        GLuint fragment_shader_id;
        GLuint program_id;
        GLuint vao_id;


        program();
        ~program();

        char* log();

        static program* make_program(string& vertex_shader_src,
                                     string& fragement_shader_src);
        char* get_log();
        bool is_ready();
        void use();

        // stores compilation / link logs
        std::string compile_log;

        bool init_glut(int& argc, char* argv[]);
        bool init_glew();
        bool init_gl();
        bool init_shaders();
        bool init_object();
        bool init_POV();
    };

} // namespace mygl

#endif