#include "Mesh.h"
#include "Log.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"
#include "ModuleFileSystem.h"
#include "GameObject.h"
#include "Model.h"

#include "DefaultShader.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, GameObject* linkGO, NodeTransform* transform, const std::string& shaderPath)
{
	VBO = 0;
	EBO = 0;
    VAO = 0;

	this->vertices = vertices;
	this->indices = indices;
    this->textures = textures;

    meshGO = linkGO;

    enableVertexNormals = false;
    enableFaceNormals = false;
    loadedTextures = false;
    loadedShader = false;
    applyCheckerTexture = false;
    addedMaterialComponent = false;

    previousModelMatrix = meshShader.model;

	LoadMesh();

    InitBoundingBoxes();

    // Load transformation from Assimp

    this->meshShader.translation = transform->translation;
    this->meshShader.rotation = transform->rotation * RADTODEG;
    this->meshShader.scale = transform->scale;

    this->shaderPath = shaderPath;
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

void Mesh::DrawMesh()
{
    // ------------------- Load Mesh Textures --------------------

    if (!loadedTextures) {

        if (applyCheckerTexture) {

            for (auto it = textures.begin(); it != textures.end(); ++it) {

                (*it).LoadCheckerImage();

                if ((*it).IsLoaded() && !addedMaterialComponent) {

                    CMaterial* cmaterial = new CMaterial(meshGO);
                    cmaterial->path = (*it).path;
                    cmaterial->ID = (*it).ID;
                    cmaterial->meshShader = &meshShader;
                    meshGO->AddComponent(cmaterial);

                    addedMaterialComponent = true;

                }

            }

        }
        else {

            for (auto it = textures.begin(); it != textures.end(); ++it) {

                (*it).LoadTexture((*it).path);

                JsonFile textureMetaFile;

                textureMetaFile.SetString("Assets Path", (*it).path.c_str());
                textureMetaFile.SetString("Library Path", (External->fileSystem->libraryTexturesPath + std::to_string((*it).UID) + ".dds").c_str());
                textureMetaFile.SetInt("UID", (*it).UID);
                textureMetaFile.SetString("Type", "Texture");

                External->fileSystem->CreateMetaFileFromAsset((*it).path, textureMetaFile);

                if ((*it).IsLoaded() && !addedMaterialComponent) {

                    CMaterial* cmaterial = new CMaterial(meshGO);
                    cmaterial->path = (*it).path;
                    cmaterial->ID = (*it).ID;
                    cmaterial->meshShader = &meshShader;
                    meshGO->AddComponent(cmaterial);

                    addedMaterialComponent = true;

                }

            }

        }

        loadedTextures = true;
        applyCheckerTexture = false;

    }

    if (!loadedShader) {

        meshShader.LoadShader(shaderPath);

        loadedShader = true;
    }

    meshShader.selected = this->meshGO->selected;

	// ------------------- Draw Mesh Geometry and Textures --------------------
    
    // Draw Vertex Positions

    if (External->renderer3D->texturingEnabled) {

        for (auto it = textures.begin(); it != textures.end(); ++it) {

            (*it).BindTexture(true);

        }

    }

    meshShader.UseShader(true);

    meshShader.SetShaderUniforms();

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    meshShader.UseShader(false);

    if (External->renderer3D->texturingEnabled) {

        for (auto it = textures.begin(); it != textures.end(); ++it) {

            (*it).BindTexture(false);

        }

    }
    
    // Draw Vertex Normals (Direct Mode)

    if (enableVertexNormals) {

        glColor3f(1.0f, 0.0f, 0.0f); // Set the color of the normals (red)

        for (size_t i = 0; i < vertices.size(); ++i) {

            Vertex& vertex = vertices[i];
            float3& normal = vertex.normal * 0.1;

            if (!previousModelMatrix.Equals(meshShader.model)) ApplyTransformation(vertex);

            glBegin(GL_LINES);
            
            glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
            glVertex3f(vertex.position.x + normal.x, vertex.position.y + normal.y, vertex.position.z + normal.z);

            glEnd();


        }

        glColor3f(1.0f, 1.0f, 1.0f);

    }

    // Draw Face Normals (Direct Mode) 

    if (enableFaceNormals) {

        glColor3f(0.0f, 0.0f, 1.0f); 

        for (size_t i = 0; i < indices.size(); i += 3) {

            // Get the indices of the vertices for the current face
            size_t index1 = indices[i];
            size_t index2 = indices[i + 1];
            size_t index3 = indices[i + 2];

            // Get the vertices for the current face
            const Vertex& vertex1 = vertices[index1];
            const Vertex& vertex2 = vertices[index2];
            const Vertex& vertex3 = vertices[index3];

            // Calculate the face normal (cross product of two edges)
            float3 edge1 = vertex2.position - vertex1.position;
            float3 edge2 = vertex3.position - vertex1.position;

            float3 cross = Cross(edge1, edge2);

            // Normalize the result to make the lines shorter
            float3 faceNormal = cross.Normalized() * 0.1;

            // Calculate the average position of the vertices for drawing the normal line
            float3 normalLineStart = (vertex1.position + vertex2.position + vertex3.position) / 3.0f;

            // Draw the Face normal lines

            glBegin(GL_LINES);

            glVertex3f(normalLineStart.x, normalLineStart.y, normalLineStart.z);
            glVertex3f(normalLineStart.x + faceNormal.x, normalLineStart.y + faceNormal.y, normalLineStart.z + faceNormal.z);

            glEnd();

        }

        glColor3f(1.0f, 1.0f, 1.0f);

    }

    previousModelMatrix = meshShader.model;

}

void Mesh::ApplyTransformation(Vertex& vertex)
{
    float4 homogeneousVertex(vertex.position.x, vertex.position.y, vertex.position.z, 1.0f);

    // Multiply by the transformation matrix
    homogeneousVertex = meshShader.model.Transform(homogeneousVertex);

    // Update the vertex coordinates
    vertex.position.x = homogeneousVertex.x;
    vertex.position.y = homogeneousVertex.y;
    vertex.position.z = homogeneousVertex.z;
}

void Mesh::InitBoundingBoxes()
{
    obb.SetNegativeInfinity();
    globalAABB.SetNegativeInfinity();

    std::vector<float3> floatArray;

    floatArray.reserve(vertices.size());

    for (const auto& vertex : vertices) {

        floatArray.push_back(vertex.position);

    }

    aabb.SetFrom(&floatArray[0], floatArray.size());
}

void Mesh::UpdateBoundingBoxes()
{
    obb = aabb;
    obb.Transform(meshShader.model);

    globalAABB.SetNegativeInfinity();
    globalAABB.Enclose(obb);
}

void Mesh::RenderBoundingBoxes()
{
    float3 verticesOBB[8];
    obb.GetCornerPoints(verticesOBB);
    External->renderer3D->DrawBox(verticesOBB, float3(255, 0, 0));

    float3 verticesAABB[8];
    globalAABB.GetCornerPoints(verticesAABB);
    External->renderer3D->DrawBox(verticesAABB, float3(0, 0, 255));
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
