#pragma once

#include "Globals.h"

#include "Mesh.h"
#include "ResourceMesh.h"

#include "External/Assimp/include/mesh.h"

namespace ImporterMesh {

	void Import(const aiMesh* mesh, Mesh* ourMesh); // Import Mesh from Assimp
	uint Save(const Mesh* ourMesh, char** fileBuffer); // Save Mesh as .ymesh on Library
	void Load(const char* fileBuffer, ResourceMesh* ourMesh); // Load Mesh from Library

}