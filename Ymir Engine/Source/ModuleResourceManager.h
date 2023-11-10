#pragma once

#include "Module.h"

class ModuleResourceManager : public Module
{
public:

	ModuleResourceManager(Application* app, bool start_enabled = true);

	virtual ~ModuleResourceManager();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

public:



};