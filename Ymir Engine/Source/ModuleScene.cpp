#include "ModuleScene.h"

#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Log.h"

#include "External/Optick/include/optick.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = CreateGameObject("Scene", nullptr);

	LOG("Creating ModuleScene");
}

ModuleScene::~ModuleScene()
{
	delete mRootNode;
}

bool ModuleScene::Start()
{
	bool ret = true;

	LOG("Loading scene");

	return ret;
}

update_status ModuleScene::PreUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	OPTICK_EVENT();

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update();
	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			(*it)->DestroyGameObject();
		}

	}

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	OPTICK_EVENT();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	LOG("Deleting scene");

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
