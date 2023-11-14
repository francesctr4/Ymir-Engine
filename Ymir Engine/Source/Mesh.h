#pragma once

#include <vector>
#include <string>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float4.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float2.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

#include "Globals.h"
#include "Texture.h"
#include "Shader.h"

#include "External/MathGeoLib/include/Geometry/AABB.h"
#include "External/MathGeoLib/include/Geometry/OBB.h"

struct NodeTransform;
class GameObject;

struct Vertex {

    float3 position;
    float3 normal;
    float2 textureCoordinates;

};

class Mesh {
public:

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, GameObject* linkGO, NodeTransform* transform);
    virtual ~Mesh();

    void DrawMesh();

    void ApplyTransformation(Vertex& vertex);

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

    bool showNormalMap;

    float4x4 previousModelMatrix;

private:

    // Buffers Data

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    void LoadMesh();

    // Bounding Boxes Handling

    AABB globalAABB;

    AABB aabb;
    OBB obb;

    void InitBoundingBoxes();

    void UpdateBoundingBoxes();

    void RenderBoundingBoxes();

};