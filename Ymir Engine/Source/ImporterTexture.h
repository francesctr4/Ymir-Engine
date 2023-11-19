#pragma once

#include "Globals.h"

#include "Texture.h"

namespace ImporterTexture {

	void Import(const char* path, Texture* ourTexture); // Import .dds or other formats
	uint Save(const Texture* ourTexture, char** fileBuffer); // Save as .dds on Library
	void Load(const char* fileBuffer, Texture* ourTexture); // Load .dds from Library

}