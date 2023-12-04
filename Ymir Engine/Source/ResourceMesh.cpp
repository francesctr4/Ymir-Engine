#include "ResourceMesh.h"
#include "ImporterMesh.h"

#include "ResourceMaterial.h"

#include "Log.h"

ResourceMesh::ResourceMesh(uint UID) : Resource(UID, ResourceType::MESH)
{
    VBO = 0;
    EBO = 0;
    VAO = 0;

    material = ResourceMaterial::defaultMaterial;
}

ResourceMesh::~ResourceMesh()
{

}

bool ResourceMesh::LoadInMemory()
{
    bool ret = true;

    // 0. Load Mesh from Library (retrieve the vectors info)
    
    ImporterMesh::Load(this->GetLibraryFilePath().c_str(), this);

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

    isLoaded = true;

    return ret;
}

bool ResourceMesh::UnloadFromMemory()
{
    bool ret = true;

    // Delete buffers

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

    // Delete the material

    if (material != 0) {

        delete material;
        material = nullptr;

    }

    // Clear the vectors

    vertices.clear();
    indices.clear();

    isLoaded = false;

    return ret;
}

bool ResourceMesh::Render() const
{
    bool ret = true;

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    return ret;
}
