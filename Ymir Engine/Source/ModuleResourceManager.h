#pragma once

#include <map>
#include <string>

#include "Module.h"
#include "Resources.h"

class ModuleResourceManager : public Module
{
public:

	// Constructor & Destructor

	ModuleResourceManager(Application* app, bool start_enabled = true);
	virtual ~ModuleResourceManager();

	// Module Functions

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	// Specific Functions

	Resource* ImportFile(const std::string& assetsFilePath);
	void SaveResourceToLibrary(Resource* resource);

	uint GenerateNewUID();
	std::string GenerateLibraryFile(const uint& UID, ResourceType type);

	uint ExistsInLibrary(const std::string& assetsFilePath) const;
	bool ExistsInLibrary(ResourceType type, const uint& UID) const;

	bool IsResourceLoaded(const uint& UID);
	
	Resource* RequestResource(const uint& UID);
	void UnloadResource(const uint& UID);

	Resource* CreateResourceFromAssets(std::string assetsFilePath, ResourceType type, const uint& UID);
	Resource* CreateResourceFromLibrary(std::string libraryFilePath, ResourceType type, const uint& UID);

	ResourceType GetTypeFromAssetsPath(std::string assetsFilePath);
	ResourceType GetTypeFromLibraryPath(std::string libraryFilePath);

	ResourceType GetTypeFromString(std::string typeString);
	std::string GetStringFromType(ResourceType type);

	std::map<uint, Resource*> GetResourcesMap() const; 

private:

	void LoadResource(const uint& UID);
	void ReleaseResource(Resource* resource);

private:

	std::map<uint, Resource*> resources;

	// Utility maps

	std::map<ResourceType, std::string> resourceTypeToString {

		{ResourceType::MESH, "ymesh"},
		{ResourceType::MODEL, "ymodel"},
		{ResourceType::SCENE, "yscene"},
		{ResourceType::MATERIAL, "ymat"},
		{ResourceType::TEXTURE, "dds"},
		{ResourceType::SHADER, "spv"},

	};

	std::map<ResourceType, std::string> resourceTypeToLibraryFolder {

		{ResourceType::MESH, "Library/Meshes/"},
		{ResourceType::MODEL, "Library/Models/"},
		{ResourceType::SCENE, "Library/Scenes/"},
		{ResourceType::MATERIAL, "Library/Materials/"},
		{ResourceType::TEXTURE, "Library/Textures/"},
		{ResourceType::SHADER, "Library/Shaders/"},

	};

};