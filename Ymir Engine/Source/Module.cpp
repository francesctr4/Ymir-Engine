#include "Module.h"

Module::Module(Application* parent, bool start_enabled) : App(parent)
{

}

Module::~Module()
{

}

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

update_status Module::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status Module::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status Module::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}

void Module::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}