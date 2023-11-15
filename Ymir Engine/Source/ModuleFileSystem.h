#pragma once

#include <string>

#include "Module.h"

class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, bool start_enabled = true);

	virtual ~ModuleFileSystem();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	void CreateLibraryFolder();

public:

	std::string workingDirectory;
	std::string libraryPath;

	std::string libraryScenesPath;
	std::string libraryModelsPath;
	std::string libraryMeshesPath;
	std::string libraryMaterialsPath;
	std::string libraryShadersPath;
	std::string libraryTexturesPath;
	std::string librarySettingsPath;

};