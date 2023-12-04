#pragma once

#include <vector>

#include "Resources.h"
#include "Mesh.h" // Temporal

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float2.h"

//struct Vertex {
//
//	float3 position;
//	float3 normal;
//	float2 textureCoordinates;
//
//};

class ResourceTexture;

class ResourceMesh : public Resource {
public:

	// Constructor & Destructor

	ResourceMesh(uint UID);
	virtual ~ResourceMesh();

	// Inherited Functions

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

	// Specific Functions

	bool Render() const;

public:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<ResourceTexture*> textures;

private:

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

};