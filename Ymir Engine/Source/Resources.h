#pragma once

#include "Globals.h"

enum class ResourceType {

	NONE,
	TEXTURE,
	MESH,
	MODEL,
	SCENE,
	SHADER,

};

class Resource {
public:

	Resource(uint UID, ResourceType type);

private:



};