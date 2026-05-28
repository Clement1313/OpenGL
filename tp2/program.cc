#include "program.hh"
#include "object_vbo.hh"
#include "transform.hh"

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace mygl;
using namespace std;

namespace mygl
{
program* current_program = nullptr;
}

program::program(/* Jesaispasoskouraidezmoi */)
{}

program::~program()
{}

bool program::init_glut(int& argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 5);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("test-OpenGL");
    glutDisplayFunc(display);

    return true;
}

bool program::init_glew()
{
    return glewInit() == GLEW_OK;
}

bool program::init_gl()
{
    return true;
}

bool attach_and_link_program(const std::vector<GLuint>& shaders_id,
                             GLuint& program_id)
{
    GLint link_status = GL_TRUE;
    program_id = glCreateProgram();
    if (program_id == 0)
        return false;
    for (unsigned int i = 0; i < shaders_id.size(); i++)
    {
        glAttachShader(program_id, shaders_id[i]);
    }
    glLinkProgram(program_id);
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE)
    {
        GLint log_size;
        char* program_log;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
        program_log = (char*)std::malloc(
            log_size + 1); /* +1 pour le caractere de fin de chaine '\0' */
        if (program_log != 0)
        {
            glGetProgramInfoLog(program_id, log_size, &log_size, program_log);
            std::cerr << "FAILURE: Program can not be linked " << program_log
                      << std::endl;
            std::free(program_log);
        }
        for (unsigned int i = 0; i < shaders_id.size(); i++)
        {
            glDetachShader(program_id, shaders_id[i]);
        }
        glDeleteProgram(program_id);
        program_id = 0;
        return false;
    }

    return true;
}

bool program::init_shaders()
{
    // Read vertex shader source
    ifstream shader_src("vertex.shd", ios::in);
    if (!shader_src.is_open())
    {
        cerr << "Unable to open vertex.shd" << endl;
        return false;
    }
    string vertex_src((istreambuf_iterator<char>(shader_src)), istreambuf_iterator<char>());
    shader_src.close();

    // Read fragment shader source
    ifstream shader_src2("fragment.shd", ios::in);
    if (!shader_src2.is_open())
    {
        cerr << "Unable to open fragment.shd" << endl;
        return false;
    }
    string fragment_src((istreambuf_iterator<char>(shader_src2)), istreambuf_iterator<char>());
    shader_src2.close();

    program* p = program::make_program(vertex_src, fragment_src);
    if (p == nullptr)
    {
        cerr << "program::make_program failed:\n";
        return false;
    }

    this->program_id = p->program_id;
    this->compile_log = std::move(p->compile_log);
    delete p;

    glUseProgram(program_id);
    return true;
}

bool program::init_object() {
  int max_nb_vbo = 5;
  int nb_vbo = 0;
  int index_vbo = 0;
  GLuint vbo_ids[max_nb_vbo];

  GLint vertex_location = glGetAttribLocation(program_id,"position");
  GLint normal_flat_location = glGetAttribLocation(program_id,"normalFlat");
  GLint normal_smooth_location = glGetAttribLocation(program_id,"normalSmooth");
  GLint color_location = glGetAttribLocation(program_id,"color");
  GLint uv_location = glGetAttribLocation(program_id,"uv");

  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  if (vertex_location!=-1) nb_vbo++;
  if (normal_flat_location!=-1) nb_vbo++;
  if (normal_smooth_location!=-1) nb_vbo++;
  if (color_location!=-1) nb_vbo++;
  if (uv_location!=-1) nb_vbo++;
  glGenBuffers(nb_vbo, vbo_ids);

  if (vertex_location!=-1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(float), vertex_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertex_location);
  }

  if (normal_flat_location!=-1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);
    glBufferData(GL_ARRAY_BUFFER, normal_flat_buffer_data.size()*sizeof(float), normal_flat_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(normal_flat_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_flat_location);
  }

  if (normal_smooth_location!=-1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);
    glBufferData(GL_ARRAY_BUFFER, normal_smooth_buffer_data.size()*sizeof(float), normal_smooth_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(normal_smooth_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_smooth_location);
  }

  if (color_location!=-1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);
    glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size()*sizeof(float), color_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_location);
  }

  if (uv_location!=-1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);
    glBufferData(GL_ARRAY_BUFFER, uv_buffer_data.size()*sizeof(float), uv_buffer_data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(uv_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uv_location);
  }

  glBindVertexArray(0);
  return true;
}

bool program::init_POV()
{
    glViewport(0, 0, 1024, 1024);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.7f, 0.7f, 0.8f, 1.0f);

    glUseProgram(program_id);

    GLfloat eye_x = 10.0f;
    GLfloat eye_y = 10.0f;
    GLfloat eye_z = 10.0f;
    GLfloat center_x = 0.0f;
    GLfloat center_y = 0.0f;
    GLfloat center_z = 0.0f;
    GLfloat up_x = 0.0f;
    GLfloat up_y = 1.0f;
    GLfloat up_z = 0.0f;
    matrix4 model_view_matrix =
        mygl::look_at(eye_x, eye_y, eye_z, center_x, center_y, center_z,
                      up_x, up_y, up_z);

    GLfloat left = -1.0f;
    GLfloat right = 1.0f;
    GLfloat bottom = -1.0f;
    GLfloat top = 1.0f;
    GLfloat z_near = 1.0f;
    GLfloat z_far = 100.0f;
    matrix4 projection_matrix =
        mygl::glFrustum(left, right, bottom, top, z_near, z_far);

    GLint model_view_location =
        glGetUniformLocation(program_id, "model_view_matrix");
    if (model_view_location != -1)
    {
        glUniformMatrix4fv(model_view_location, 1, GL_TRUE,
                           &model_view_matrix.mat[0][0]);
    }

    GLint projection_location =
        glGetUniformLocation(program_id, "projection_matrix");
    if (projection_location != -1)
    {
        glUniformMatrix4fv(projection_location, 1, GL_TRUE,
                           &projection_matrix.mat[0][0]);
    }

    return true;
}

namespace mygl
{
void display()
{
    if (current_program == nullptr)
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(current_program->program_id);
    glBindVertexArray(current_program->vao_id);

    GLint object_color_location =
        glGetUniformLocation(current_program->program_id, "object_color");
    if (object_color_location != -1)
    {
        glUniform3f(object_color_location, 0.9f, 0.7f, 0.3f);
    }

    glDrawArrays(GL_TRIANGLES, 0,
                 static_cast<GLsizei>(vertex_buffer_data.size() / 3));

    glBindVertexArray(0);
    glutSwapBuffers();
}
} // namespace mygl

program* program::make_program(string& vertex_shader_src,
                               string& fragement_shader_src)
{
    program* p = new program();
    p->compile_log.clear();

    // Vertex shader
    const char* v_src = vertex_shader_src.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    if (vs == 0)
    {
        p->compile_log += "Failed to create vertex shader\n";
        delete p;
        return nullptr;
    }
    glShaderSource(vs, 1, &v_src, nullptr);
    glCompileShader(vs);
    GLint compiled = GL_FALSE;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        GLint log_len = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0)
        {
            char* logbuf = (char*)std::malloc(log_len + 1);
            if (logbuf)
            {
                glGetShaderInfoLog(vs, log_len, nullptr, logbuf);
                p->compile_log += "Vertex shader compile error:\n";
                p->compile_log += logbuf;
                std::free(logbuf);
            }
        }
        glDeleteShader(vs);
        delete p;
        return nullptr;
    }

    // Fragment shader
    const char* f_src = fragement_shader_src.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    if (fs == 0)
    {
        p->compile_log += "Failed to create fragment shader\n";
        glDeleteShader(vs);
        delete p;
        return nullptr;
    }
    glShaderSource(fs, 1, &f_src, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        GLint log_len = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0)
        {
            char* logbuf = (char*)std::malloc(log_len + 1);
            if (logbuf)
            {
                glGetShaderInfoLog(fs, log_len, nullptr, logbuf);
                p->compile_log += "Fragment shader compile error:\n";
                p->compile_log += logbuf;
                std::free(logbuf);
            }
        }
        glDeleteShader(vs);
        glDeleteShader(fs);
        delete p;
        return nullptr;
    }

    // Link program
    GLuint pid = glCreateProgram();
    if (pid == 0)
    {
        p->compile_log += "Failed to create program object\n";
        glDeleteShader(vs);
        glDeleteShader(fs);
        delete p;
        return nullptr;
    }
    glAttachShader(pid, vs);
    glAttachShader(pid, fs);
    glLinkProgram(pid);
    GLint link_status = GL_FALSE;
    glGetProgramiv(pid, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE)
    {
        GLint log_len = 0;
        glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0)
        {
            char* logbuf = (char*)std::malloc(log_len + 1);
            if (logbuf)
            {
                glGetProgramInfoLog(pid, log_len, nullptr, logbuf);
                p->compile_log += "Program link error:\n";
                p->compile_log += logbuf;
                std::free(logbuf);
            }
        }
        // cleanup
        glDetachShader(pid, vs);
        glDetachShader(pid, fs);
        glDeleteProgram(pid);
        glDeleteShader(vs);
        glDeleteShader(fs);
        delete p;
        return nullptr;
    }

    glDetachShader(pid, vs);
    glDetachShader(pid, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    p->program_id = pid;
    return p;
}

char* program::get_log()
{
    if (compile_log.empty())
        return nullptr;
    size_t sz = compile_log.size();
    char* buf = (char*)std::malloc(sz + 1);
    if (!buf)
        return nullptr;
    std::memcpy(buf, compile_log.c_str(), sz);
    buf[sz] = '\0';
    return buf;
}

char* program::log()
{
    return get_log();
}

bool program::is_ready()
{
    return program_id != 0;
}

void program::use()
{
    if (program_id != 0)
        glUseProgram(program_id);
}