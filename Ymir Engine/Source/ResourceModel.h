#pragma once

#include "Resources.h"

class ResourceModel : public Resource {
public:

	ResourceModel(uint UID);

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:



};