#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <string>

using namespace std;

namespace mygl
{
    class program
    {
        program();
        ~program();

        char* log();

        static program* make_program(string& vertex_shader_src,
                                     string& fragement_shader_src);
        char* get_log();
        bool is_ready();
        void use();
    };

} // namespace mygl

#endif