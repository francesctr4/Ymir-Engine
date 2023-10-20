#include "Mesh.h"
#include "Log.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	VBO = 0;
	EBO = 0;
    VAO = 0;

	this->vertices = vertices;
	this->indices = indices;
    this->textures = textures;

    enableNormals = false;

	LoadMesh();

    loadTex = false;
    
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

    if (VAO != 0) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }

}

void Mesh::DrawMesh(Shader& shader)
{
    // ------------------- Draw Mesh Textures --------------------

    /* TODO */
    //if (!loadTex && !textures.empty()) {

    //   /* for (auto it = textures.begin(); it != textures.end(); ++it) {

    //        (*it).LoadTexture(textures[0].path);

    //    }*/
    //    textures[0].LoadTexture(textures[0].path);
    //    loadTex = true;
    //}
    

	// ------------------- Draw Mesh Geometry --------------------
    
    // Draw Vertex Positions

    //for (auto it = textures.begin(); it != textures.end(); ++it) {

    //    (*it).BindTexture(true);

    //}

    //textures[0].BindTexture(true);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    //textures[0].BindTexture(false);

    //for (auto it = textures.begin(); it != textures.end(); ++it) {

    //    (*it).BindTexture(false);

    //}

    
    
    // Draw Vertex Normals (Direct Mode)

    if (enableNormals) {

        glColor3f(1.0f, 0.0f, 0.0f); // Set the color of the normals (red)

        for (size_t i = 0; i < vertices.size(); ++i) {

            const Vertex& vertex = vertices[i];
            const float3& normal = vertex.normal * 0.1;

            glBegin(GL_LINES);

            glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
            glVertex3f(vertex.position.x + normal.x, vertex.position.y + normal.y, vertex.position.z + normal.z);

            glEnd();


        }

        glColor3f(1.0f, 1.0f, 1.0f);

    }

    // Draw Face Normals (Direct Mode) 

    /* TODO */

}

void Mesh::LoadMesh()
{
    // 1. Create Buffers

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 2. Bind Buffers

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 3. Set the Vertex Attribute Pointers

        // Vertex Positions

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Vertex Normals

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // Vertex Texture Coordinates

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

    // 4. Load data into Vertex Buffers

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    LOG("Mesh loaded with: %d vertices, %d indices", vertices.size(), indices.size());

    // 5. Unbind Buffers

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
