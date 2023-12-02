#pragma once

#include "Resources.h"

class ResourceMaterial : public Resource {
public:

	ResourceMaterial(uint UID);

	bool IsLoadedInMemory() override;
	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};