#pragma once

#include <vector>
#include <string>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float2.h"

#include "Globals.h"
#include "Texture.h"
#include "Shader.h"

class GameObject;

struct Vertex {

    float3 position;
    float3 normal;
    float2 textureCoordinates;

};

class Mesh {
public:

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, GameObject* linkGO);
    virtual ~Mesh();

    void DrawMesh();

public:

    // Mesh Data

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    GameObject* meshGO;

    Shader meshShader;

    bool enableVertexNormals;
    bool enableFaceNormals;

    bool loadedTextures;
    bool applyCheckerTexture;

    bool addedMaterialComponent;

private:

    // Buffers Data

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    void LoadMesh();

};