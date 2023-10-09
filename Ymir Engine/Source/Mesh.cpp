#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
    VBO = 0;
    EBO = 0;

    this->vertices = vertices;
    this->indices = indices;

    LoadMesh();
}

Mesh::~Mesh()
{
	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (EBO != 0) {
		glDeleteBuffers(1, &EBO);
		EBO = 0;
	}

}

void Mesh::DrawMesh()
{
	// Draw Textures

		/* TODO */

	// Draw Geometry

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

}

void Mesh::LoadMesh()
{
	// Vertex Buffer Object

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Element Buffer Object

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
