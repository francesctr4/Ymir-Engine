#pragma once

#include "Resources.h"

enum class ShaderType {

	UNKNOWN = -1,	// NULL Type

	VERTEX,			// Mandatory
	TESSELLATION,	// Optional
	GEOMETRY,		// Optional
	FRAGMENT,		// Mandatory

	NUM_TYPES		// Total Quantity of Types

};

class ResourceShader : public Resource {
public:

	ResourceShader(uint UID);

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};