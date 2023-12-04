#include "ModuleResourceManager.h"

#include "Log.h"
#include "External/Optick/include/optick.h"
#include "Random.h"
#include "ModuleFileSystem.h"
#include "PhysfsEncapsule.h"
#include "JsonFile.h"

#include "ResourceModel.h"
#include "ResourceMesh.h"
#include "ResourceScene.h"
#include "ResourceTexture.h"
#include "ResourceMaterial.h"
#include "ResourceShader.h"

#include "ImporterModel.h"
#include "ImporterMesh.h"
#include "ImporterScene.h"
#include "ImporterTexture.h"
#include "ImporterMaterial.h"
#include "ImporterShader.h"

ModuleResourceManager::ModuleResourceManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Creating ModuleResourceManager");
}

ModuleResourceManager::~ModuleResourceManager()
{
	
}

bool ModuleResourceManager::Init()
{
	bool ret = true;

	LOG("Loading Resource Manager");

	return ret;
}

update_status ModuleResourceManager::PreUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

update_status ModuleResourceManager::Update(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

update_status ModuleResourceManager::PostUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

bool ModuleResourceManager::CleanUp()
{
	bool ret = true;

	LOG("Deleting Resource Manager");

	return ret;
}

Resource* ModuleResourceManager::ImportFile(const std::string& assetsFilePath)
{
	// Create Meta

	std::string metaFilePath = assetsFilePath + ".meta"; // Assuming the meta file exists.

	// Retrieve info from Meta

	JsonFile* metaFile = JsonFile::GetJSON(metaFilePath);

	uint UID = metaFile->GetInt("UID");
	ResourceType type = GetTypeFromString(metaFile->GetString("Type"));

	Resource* resource = CreateResourceFromAssets(assetsFilePath, type, UID);

	/* The resources that have to be transformed to Ymir Engine format have to be imported,
	but the resources that are already in the custom format only have to be loaded. */

	switch (resource->GetType()) {

		case ResourceType::MESH:

			//ImporterMesh::Load(assetsFilePath.c_str(), (ResourceMesh*)resource);
			break;

		case ResourceType::MODEL:

			//ImporterModel::Import(assetsFilePath.c_str(), (ResourceModel*)resource);
			break;

		case ResourceType::SCENE:

			//ImporterScene::Load(assetsFilePath.c_str(), (ResourceScene*)resource);
			break;

		case ResourceType::TEXTURE:

			//ImporterTexture::Import(assetsFilePath.c_str(), (ResourceTexture*)resource);
			break;

		case ResourceType::MATERIAL:

			//ImporterMaterial::Load(assetsFilePath.c_str(), (ResourceMaterial*)resource);
			break;

		case ResourceType::SHADER:

			//ImporterShader::Import(assetsFilePath.c_str(), (ResourceShader*)resource);
			break;

	}

	return resource;
}

void ModuleResourceManager::SaveResourceToLibrary(Resource* resource)
{
	switch (resource->GetType()) {

		case ResourceType::MESH:
		
			//ImporterMesh::Save((ResourceMesh*)resource, resource->GetLibraryFilePath());
			break;

		case ResourceType::MODEL:

			//ImporterModel::Save((ResourceModel*)resource, resource->GetLibraryFilePath());
			break;

		case ResourceType::SCENE:

			//ImporterScene::Save((ResourceScene*)resource, resource->GetLibraryFilePath());
			break;

		case ResourceType::TEXTURE:

			//ImporterTexture::Save((ResourceTexture*)resource, resource->GetLibraryFilePath());
			break;

		case ResourceType::MATERIAL:

			//ImporterMaterial::Save((ResourceMaterial*)resource, resource->GetLibraryFilePath());
			break;

		case ResourceType::SHADER:

			//ImporterShader::Save((ResourceShader*)resource, resource->GetLibraryFilePath());
			break;

	}

}

uint ModuleResourceManager::GenerateNewUID()
{
	return Random::Generate();
}

uint ModuleResourceManager::ExistsInLibrary(const std::string& assetsFilePath) const
{
	std::string metaFilePath = assetsFilePath + ".meta";

	if (PhysfsEncapsule::FileExists(metaFilePath))
	{
		JsonFile* metaFile = JsonFile::GetJSON(metaFilePath);

		std::string libraryFilePath = metaFile->GetString("Library Path");

		if (PhysfsEncapsule::FileExists(libraryFilePath)) {

			uint UID = metaFile->GetInt("UID");

			return UID;

		}
		
	}

	return 0;
}

bool ModuleResourceManager::ExistsInLibrary(ResourceType type, const uint& UID) const
{
	std::string libraryFilePath = resourceTypeToLibraryFolder.at(type) + std::to_string(UID) + "." + resourceTypeToString.at(type);

	if (PhysfsEncapsule::FileExists(libraryFilePath)) 
	{
		return true;
	}

	return false;
}

void ModuleResourceManager::ReleaseResource(Resource* resource)
{
	resource->UnloadFromMemory();

	resources.erase(resource->GetUID());

	delete resource;
}

bool ModuleResourceManager::IsResourceLoaded(const uint& UID)
{
	std::map<uint, Resource*>::iterator it = resources.find(UID);

	if (it != resources.end()) {

		return true;

	}
		
	return false;
}

void ModuleResourceManager::LoadResource(const uint& UID)
{
	std::map<uint, Resource*>::iterator it = resources.find(UID);

	if (it == resources.end()) 
	{
		return;
	}

	Resource* tmpResource = it->second;

	tmpResource->IncreaseReferenceCount();

	tmpResource->LoadInMemory();
}

Resource* ModuleResourceManager::RequestResource(const uint& UID, const char* libraryFilePath)
{
	std::map<uint, Resource*>::iterator it = resources.find(UID);

	if (it != resources.end())
	{
		it->second->IncreaseReferenceCount();

		return it->second;
	}
	else {

		if (libraryFilePath != nullptr)
		{
			Resource* tmpResource = nullptr;

			if (PhysfsEncapsule::FileExists(libraryFilePath))
			{
				ResourceType tmpType = GetTypeFromLibraryPath(libraryFilePath);

				switch (tmpType) {

					case ResourceType::MESH:

						tmpResource = new ResourceMesh(UID);

						break;

					case ResourceType::MODEL:

						tmpResource = new ResourceModel(UID);

						break;

					case ResourceType::SCENE:

						tmpResource = new ResourceScene(UID);

						break;

					case ResourceType::TEXTURE:

						tmpResource = new ResourceTexture(UID);

						break;

					case ResourceType::MATERIAL:

						tmpResource = new ResourceMaterial(UID);

						break;

					case ResourceType::SHADER:

						tmpResource = new ResourceShader(UID);

						break;

				}

				if (tmpResource != nullptr)
				{
					resources[UID] = tmpResource;

					tmpResource->SetLibraryFilePath(libraryFilePath);

					tmpResource->IncreaseReferenceCount();

					tmpResource->LoadInMemory();
				}

			}

			return tmpResource;

		}
		else {

			LOG("Resource requested isn't loaded and hasn't a library file.");

			return nullptr;

		}

	}

}

void ModuleResourceManager::UnloadResource(const uint& UID)
{
	std::map<uint, Resource*>::iterator it = resources.find(UID);

	if (it == resources.end())
	{
		return;
	}

	Resource* tmpResource = it->second;

	tmpResource->DecreaseReferenceCount();

	if (tmpResource->GetReferenceCount() == 0) {

		ReleaseResource(tmpResource);

	}
}

Resource* ModuleResourceManager::CreateResourceFromAssets(std::string assetsFilePath, ResourceType type, const uint& UID)
{
	Resource* tmpResource = nullptr;

	switch (type) {

		case ResourceType::MESH:

			tmpResource = new ResourceMesh(UID);
			break;

		case ResourceType::MODEL:

			tmpResource = new ResourceModel(UID);
			break;

		case ResourceType::SCENE: 

			tmpResource = new ResourceScene(UID);
			break;

		case ResourceType::TEXTURE: 

			tmpResource = new ResourceTexture(UID);
			break;

		case ResourceType::MATERIAL:

			tmpResource = new ResourceMaterial(UID);
			break;

		case ResourceType::SHADER:

			tmpResource = new ResourceShader(UID);
			break;

	}

	if (tmpResource != nullptr)
	{
		resources[UID] = tmpResource;

		tmpResource->SetAssetsFilePath(assetsFilePath);

		/*std::string libraryFilePath = GenerateLibraryFile(UID, type);
		tmpResource->SetLibraryFilePath(libraryFilePath);*/

		tmpResource->IncreaseReferenceCount();
	}

	return tmpResource;
}

Resource* ModuleResourceManager::CreateResourceFromLibrary(std::string libraryFilePath, ResourceType type, const uint& UID)
{
	Resource* tmpResource = nullptr;

	switch (type) {

	case ResourceType::MESH:

		tmpResource = new ResourceMesh(UID);
		break;

	case ResourceType::MODEL:

		tmpResource = new ResourceModel(UID);
		break;

	case ResourceType::SCENE:

		tmpResource = new ResourceScene(UID);
		break;

	case ResourceType::TEXTURE:

		tmpResource = new ResourceTexture(UID);
		break;

	case ResourceType::MATERIAL:

		tmpResource = new ResourceMaterial(UID);
		break;

	case ResourceType::SHADER:

		tmpResource = new ResourceShader(UID);
		break;

	}

	if (tmpResource != nullptr)
	{
		resources[UID] = tmpResource;

		tmpResource->SetLibraryFilePath(libraryFilePath);

		tmpResource->IncreaseReferenceCount();
	}

	return tmpResource;
}

ResourceType ModuleResourceManager::GetTypeFromAssetsPath(std::string assetsFilePath)
{
	std::string extension = assetsFilePath.substr(assetsFilePath.find_last_of('.') + 1);

	// Convert to lowercase in case the extension is on uppercase
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	if (extension == "fbx" || extension == "dae" || extension == "obj") return ResourceType::MODEL;
	else if (extension == "yscene") return ResourceType::SCENE;
	else if (extension == "png" || extension == "dds" || extension == "jpg" || extension == "tga") return ResourceType::TEXTURE;

	return ResourceType::UNKNOWN;
}

ResourceType ModuleResourceManager::GetTypeFromLibraryPath(std::string libraryFilePath)
{
	std::string extension = libraryFilePath.substr(libraryFilePath.find_last_of('.') + 1);

	if (extension == "ymesh") return ResourceType::MESH;
	else if (extension == "ymodel") return ResourceType::MODEL;
	else if (extension == "yscene") return ResourceType::SCENE;
	else if (extension == "ymat") return ResourceType::MATERIAL;
	else if (extension == "dds") return ResourceType::TEXTURE;
	else if (extension == "spv") return ResourceType::SHADER;
	
	return ResourceType::UNKNOWN;
}

ResourceType ModuleResourceManager::GetTypeFromString(std::string typeString)
{
	ResourceType tmpType = ResourceType::UNKNOWN;

	for (const auto& pair : resourceTypeToString) {

		if (pair.second == typeString) {

			tmpType = pair.first;

		}

	}

	return tmpType;
}

std::string ModuleResourceManager::GetStringFromType(ResourceType type)
{
	return resourceTypeToString.at(type);
}

std::map<uint, Resource*> ModuleResourceManager::GetResourcesMap() const
{
	return resources;
}
