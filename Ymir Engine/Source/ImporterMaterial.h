#pragma once

#include "Globals.h"

#include "Material.h"
#include "External/Assimp/include/material.h"

namespace ImporterMaterial {

	void Import(const aiMaterial* material, Material* ourMaterial); // Import Material from Assimp
	uint Save(const Material* ourMaterial, char** fileBuffer); // Save Material as .ymat on Library
	void Load(const char* fileBuffer, Material* ourMaterial); // Load Material from Library

}