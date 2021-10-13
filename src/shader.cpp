#include <Shader.hpp>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const char *vertexPath, const char *fragPath) {
    std::ifstream vertexFile, fragFile;
    std::string vertexCode, fragCode;
    std::stringstream vertexStream, fragStream;

    vertexFile.open(vertexPath);
    if (!vertexFile)
    {
        std::cout << "Failed to load vertex shader: " << vertexPath;
        exit(1);
    }  
    vertexStream << vertexFile.rdbuf();
    vertexFile.close();
    vertexCode = vertexStream.str();
    
    const char *vertexShaderSource = vertexCode.c_str();
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragFile.open(fragPath);
    if (!fragFile)
    {
        std::cout << "Failed to load fragment shader: " << fragPath;
        exit(1);
    }  
    fragStream << fragFile.rdbuf();
    fragFile.close();
    fragCode = fragStream.str();

    const char *fragShaderSource = fragCode.c_str();
    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);

    this->id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

Shader::~Shader() {}

void Shader::Use() 
{
    glUseProgram(this->id);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) 
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &vec) 
{
	glUniform3f(glGetUniformLocation(this->id, name.c_str()), vec.x, vec.y, vec.z);
}