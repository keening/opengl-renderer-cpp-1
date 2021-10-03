#pragma once
#include <vector>

class mesh 
{
public:
    mesh();
	mesh(std::vector<float> vertices);
    ~mesh();

    void draw();
    void setup_vbo();

private:
    int vbo, vao;
    std::vector<float> vertices = { 0 };
};