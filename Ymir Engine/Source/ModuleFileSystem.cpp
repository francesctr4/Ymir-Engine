#include "ModuleFileSystem.h"

#include "Log.h"
#include "External/Optick/include/optick.h"

#include "JsonEncapsule.h"

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Creating ModuleFileSystem");
}

ModuleFileSystem::~ModuleFileSystem()
{

}

bool ModuleFileSystem::Init()
{
	bool ret = true;

	LOG("Loading scene");

	JsonEncapsule::Example();

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