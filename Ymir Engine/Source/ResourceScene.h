#pragma once

#include "Resources.h"

class ResourceScene : public Resource {
public:

	ResourceScene(uint UID);

	bool IsLoadedInMemory() override;
	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};