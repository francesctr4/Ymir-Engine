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

	//if (PhysfsEncapsule::FolderExists(libraryPath)) {

		JsonEncapsule::CreateJSON(libraryPath, "output.json");

	//}

	PhysfsEncapsule::DeinitializePhysFS();

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

	return ret;
}

void ModuleFileSystem::CreateLibraryFolder()
{
	PhysfsEncapsule::CreateFolder(workingDirectory, "Library");

	PhysfsEncapsule::CreateFolder(libraryPath, "Scenes"); // JSON
	PhysfsEncapsule::CreateFolder(libraryPath, "Models"); // Custom File Format
	PhysfsEncapsule::CreateFolder(libraryPath, "Meshes"); // Custom File Format
	PhysfsEncapsule::CreateFolder(libraryPath, "Materials"); // JSON
	PhysfsEncapsule::CreateFolder(libraryPath, "Shaders"); // GLSL
	PhysfsEncapsule::CreateFolder(libraryPath, "Textures"); // DDS 
}
