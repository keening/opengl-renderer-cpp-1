#include <mesh.hpp>
#include <glad/glad.h>

mesh::mesh(std::vector<float> vertices)
{
	glGenVertexArrays(1, (GLuint*)&this->vao);
	glBindVertexArray(this->vao);

    this->vertices = vertices;
	setup_vbo();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 
                        (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
}

mesh::~mesh()
{
    glDeleteVertexArrays(1, (GLuint*)&this->vao);
    glDeleteBuffers(1, (GLuint*)&this->vbo);
}

void mesh::setup_vbo()
{
    glGenBuffers(1, (GLuint*)&this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), 
                this->vertices.data(), GL_STATIC_DRAW);
}

void mesh::draw()
{
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
