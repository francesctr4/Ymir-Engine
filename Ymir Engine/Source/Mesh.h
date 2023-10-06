#pragma once

#include <vector>
#include <string>
#include <cstddef>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float2.h"
#include "External/MathGeoLib/include/Math/float3.h"

#include "Globals.h"

struct Vertex {

    float3 position;
    float3 normal;
    float2 textureCoordinates;

};

struct Texture {

    uint id;
    std::string type;

};

class Mesh {
public:

    Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::vector<Texture>& textures);
    virtual ~Mesh();

    void DrawMesh();

public:

    // Mesh Data

    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;
    
private:

    // Buffers Data

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    void LoadMesh();
    
};