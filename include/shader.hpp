#pragma once
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class Shader {
    public:
        Shader();
        Shader(const char *vertexPath, const char *fragPath);
        ~Shader();

        void Use();

        void SetMat4(const std::string &name, const glm::mat4 &mat);
        void SetVec3(const std::string &name, const glm::vec3 &vec);
        int GetID() { return id; }   

    private:
        int id = 0;
};