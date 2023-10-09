#pragma once

#include <vector>
#include <string>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float3.h"

#include "Globals.h"

class Mesh {
public:

    Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
    virtual ~Mesh();

    void DrawMesh();

public:

    // Mesh Data

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    
private:

    // Buffers Data

    GLuint VBO;
    GLuint EBO;

    void LoadMesh();
    
};