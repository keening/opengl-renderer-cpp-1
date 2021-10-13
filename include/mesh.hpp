#pragma once
#include <vector>

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<float> vertices);
        ~Mesh();

        void Draw();
        void SetupVBO();

    private:
        int vbo, vao;
        std::vector<float> vertices = { 0 };
};