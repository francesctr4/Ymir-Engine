#include "ModuleScene.h"

#include "GameObject.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = new GameObject();
}

ModuleScene::~ModuleScene()
{
	delete mRootNode;
}

bool ModuleScene::Start()
{

	return false;
}

update_status ModuleScene::PreUpdate(float dt)
{

	return update_status();
}

update_status ModuleScene::Update(float dt)
{

	return update_status();
}

update_status ModuleScene::PostUpdate(float dt)
{

	return update_status();
}

bool ModuleScene::CleanUp()
{

	return false;
}

GameObject* ModuleScene::CreateGameObject()
{

	return nullptr;
}
