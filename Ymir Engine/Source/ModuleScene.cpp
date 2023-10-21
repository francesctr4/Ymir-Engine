#include "ModuleScene.h"

#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Log.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = CreateGameObject("Scene", nullptr);
}

ModuleScene::~ModuleScene()
{
	delete mRootNode;
}

bool ModuleScene::Start()
{
	bool ret = true;

	return ret;
}

update_status ModuleScene::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update();
	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {

		DestroyGameObject(mRootNode);

	}

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}

GameObject* ModuleScene::CreateGameObject(std::string name, GameObject* parent)
{
	GameObject* tempGameObject = new GameObject(name, parent);

	if (parent != nullptr) {

		parent->AddChild(tempGameObject);

	}

	gameObjects.push_back(tempGameObject);

	return tempGameObject;
}

void ModuleScene::DestroyGameObject(GameObject* toDestroy)
{
	toDestroy->DestroyGameObject();
}
