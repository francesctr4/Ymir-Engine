#pragma once

#include "Globals.h"

#include "Scene.h"

namespace ImporterScene {

	uint Save(const Scene& ourScene, char** fileBuffer); // Save Scene as .yscene on Library
	void Load(const char* fileBuffer, Scene& ourScene); // Load Scene from Library

}