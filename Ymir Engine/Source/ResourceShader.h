#pragma once

#include "Resources.h"

class ResourceShader : public Resource {
public:

	ResourceShader(uint UID);

	bool IsLoadedInMemory() override;
	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};