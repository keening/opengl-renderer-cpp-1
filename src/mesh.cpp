#include <Mesh.hpp>
#include <glad/glad.h>

Mesh::Mesh(std::vector<float> vertices)
{
	glGenVertexArrays(1, (GLuint*)&this->vao);
	glBindVertexArray(this->vao);

    this->vertices = vertices;
	SetupVBO();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 
                         (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, (GLuint*)&this->vao);
    glDeleteBuffers(1, (GLuint*)&this->vbo);
}

void Mesh::SetupVBO()
{
    glGenBuffers(1, (GLuint*)&this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), 
                 this->vertices.data(), GL_STATIC_DRAW);
}

void Mesh::Draw()
{
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
