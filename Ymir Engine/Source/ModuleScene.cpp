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

bool ModuleScene::Init()
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

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {

		ClearScene();

	}

	//if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {

	//	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	//	{
	//		if ((*it)->selected) {

	//			/*DestroyGameObject((*it));*/

	//			/*delete (*it);
	//			(*it) = nullptr;*/
	//			//gameObjects.erase(it);
	//			//delete (*it);
	//			//(*it) = nullptr;
	//			
	//			//App->renderer3D->models.erase(it);

	//		}

	//	}

	//}

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
	if (toDestroy) {

		toDestroy->DestroyGameObject();

	}

}

void ModuleScene::ClearScene()
{
	App->editor->DestroyHierarchyTree(mRootNode);
	delete mRootNode;
	mRootNode = nullptr;

	gameObjects.clear();

	App->renderer3D->models.clear();
	mRootNode = CreateGameObject("Scene", nullptr); // Recreate scene
}
