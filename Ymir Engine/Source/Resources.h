#pragma once

#include "Globals.h"

enum class ResourceType {

	NONE,
	TEXTURE,
	MESH,
	MODEL,
	SCENE,
	SHADER,
	MATERIAL,

};

class Resource {
public:

	Resource(uint UID, ResourceType type);

private:



};