#pragma once
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class shader 
{
public:
    shader();
    shader(const char *vertex_path, const char *frag_path);
    ~shader();

    void use();
	void set_mat4(const std::string &name, const glm::mat4 &mat);
    void set_vec3(const std::string &name, const glm::vec3 &vec);
    int get_id() { return id; }   

private:
	int id = 0;
};