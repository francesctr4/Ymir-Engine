#pragma once

#include "Resources.h"

class ResourceMesh : public Resource {
public:

	ResourceMesh(uint UID);

	bool IsLoadedInMemory() override;
	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};