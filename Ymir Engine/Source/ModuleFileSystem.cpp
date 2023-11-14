#include "ModuleFileSystem.h"

#include "Log.h"
#include "External/Optick/include/optick.h"

#include "PhysfsEncapsule.h"
#include "JsonEncapsule.h"

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	workingDirectory = "./";
	libraryPath = workingDirectory + "Library/";

	LOG("Creating ModuleFileSystem");
}

ModuleFileSystem::~ModuleFileSystem()
{

}

bool ModuleFileSystem::Init()
{
	bool ret = true;

	LOG("Loading File System");

	PhysfsEncapsule::InitializePhysFS();

	CreateLibraryFolder();

	if (PhysfsEncapsule::FolderExists(libraryPath)) {

		JsonEncapsule::CreateJSON(libraryPath, "output.json");

	}

	return ret;
}

update_status ModuleFileSystem::PreUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

update_status ModuleFileSystem::Update(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

update_status ModuleFileSystem::PostUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

bool ModuleFileSystem::CleanUp()
{
	bool ret = true;

	LOG("Deleting File System");

	PhysfsEncapsule::DeinitializePhysFS();

	return ret;
}

void ModuleFileSystem::CreateLibraryFolder()
{
	PhysfsEncapsule::CreateFolder(workingDirectory, "Library");

	PhysfsEncapsule::CreateFolder(libraryPath, "Scenes"); // Custom File Format (JSON)
	libraryScenesPath = libraryPath + "Scenes/";

	PhysfsEncapsule::CreateFolder(libraryPath, "Models"); // Custom File Format (JSON)
	libraryModelsPath = libraryPath + "Models/";

	PhysfsEncapsule::CreateFolder(libraryPath, "Meshes"); // Custom File Format
	libraryMeshesPath = libraryPath + "Meshes/";

	PhysfsEncapsule::CreateFolder(libraryPath, "Materials"); // Custom File Format (JSON)
	libraryMaterialsPath = libraryPath + "Materials/";

	PhysfsEncapsule::CreateFolder(libraryPath, "Shaders"); // GLSL
	libraryShadersPath = libraryPath + "Shaders/";

	PhysfsEncapsule::CreateFolder(libraryPath, "Textures"); // DDS 
	libraryTexturesPath = libraryPath + "Textures/";
}
