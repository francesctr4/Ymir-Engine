#pragma once

#include "Resources.h"

class ResourceTexture : public Resource {
public:

	ResourceTexture(uint UID);

	bool IsLoadedInMemory() override;
	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};