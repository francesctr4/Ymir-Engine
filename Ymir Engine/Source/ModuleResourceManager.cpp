#include "ModuleResourceManager.h"

#include "Log.h"
#include "External/Optick/include/optick.h"

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

std::map<uint, Resource*> ModuleResourceManager::GetResourcesMap() const
{
	return resources;
}
