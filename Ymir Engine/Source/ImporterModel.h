#pragma once

#include "Globals.h"

#include "Model.h"
#include "External/Assimp/include/scene.h"

namespace ImporterModel {

	void Import(const aiScene* model, Model* ourModel); // Import Model from Assimp
	uint Save(const Model* ourModel, char** fileBuffer); // Save Model as .ymodel on Library
	void Load(const char* fileBuffer, Model* ourModel); // Load Model from Library

}