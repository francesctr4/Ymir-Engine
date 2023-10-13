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

struct Vertex {

    float3 position;
    float3 normal;
    float2 textureCoordinates;
};

class Texture;

class Mesh {
public:

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    virtual ~Mesh();

    void DrawMesh();

public:

    // Mesh Data

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    bool enableNormals;

private:

    // Buffers Data

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    void LoadMesh();

};