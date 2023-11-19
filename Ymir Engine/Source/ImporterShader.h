#pragma once

#include "Globals.h"

#include "Shader.h"

// Maybe will be necessary to add shaderc library, to compile shaders on runtime.

namespace ImporterShader {

	void Import(const char* filePath, Shader* ourShader); // Import .glsl shaders from Assets
	uint Compile(const char* vertexShader, const char* fragmentShader); // Compile shaders with shaderc
	uint Save(const Shader* ourShader, char** fileBuffer); // Save shaders on SPIR-V format in Library
	void Load(const char* fileBuffer, Shader* ourShader); // Load shaders from Library
}