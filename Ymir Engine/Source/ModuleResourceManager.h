#pragma once

#include <map>

#include "Module.h"
#include "Resources.h"

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

	bool ExistsInLibrary(ResourceType type, const uint& UID) const;

	uint GetUIDFromAssetsPath(const std::string& assetsFilePath) const;

	uint ImportFile(const std::string& assetsFilePath);
	uint GenerateNewUID();

	Resource* RequestResource(const uint& UID);
	void ReleaseResource(const uint& UID);

	Resource* CreateResourceFromAssets(std::string assetsFilePath, ResourceType type, const uint& UID);
	Resource* CreateResourceFromLibrary(std::string libraryFilePath, ResourceType type, const uint& UID);

	ResourceType GetTypeFromAssetsPath(std::string assetsFilePath);
	ResourceType GetTypeFromLibraryPath(std::string libraryFilePath);

	std::map<uint, Resource*> GetResourcesMap() const; 

private:

	std::map<uint, Resource*> resources;

};