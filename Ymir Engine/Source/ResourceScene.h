#pragma once

#include "Resources.h"

class ResourceScene : public Resource {
public:

	ResourceScene(uint UID);

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};