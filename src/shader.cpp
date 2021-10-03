#include <shader.hpp>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

shader::shader(const char *vertex_path, const char *frag_path) {
    std::ifstream vertex_file, frag_file;
    std::string vertex_code, frag_code;
    std::stringstream vertex_string, frag_string;

    vertex_file.open(vertex_path);
    if (!vertex_file)
    {
        std::cout << "Failed to load vertex shader: " << vertex_path << std::endl;
        exit(1);
    }  
    vertex_string << vertex_file.rdbuf();
    vertex_file.close();
    vertex_code = vertex_string.str();
    
    const char *vertex_shader_src = vertex_code.c_str();
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    frag_file.open(frag_path);
    frag_string << frag_file.rdbuf();
    frag_file.close();
    frag_code = frag_string.str();

    const char *frag_shader_src = frag_code.c_str();
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_src, NULL);
    glCompileShader(frag_shader);

    frag_file.close();

    this->id = glCreateProgram();

    glAttachShader(id, vertex_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}

shader::~shader() {}

void shader::use() 
{
    glUseProgram(this->id);
}

void shader::set_mat4(const std::string &name, const glm::mat4 &mat) 
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
