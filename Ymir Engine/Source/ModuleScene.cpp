#include "ModuleScene.h"

#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"

#include "GameObject.h"
#include "Log.h"
#include "CCamera.h"

#include "ModuleFileSystem.h"
#include "PhysfsEncapsule.h"

#include "External/Optick/include/optick.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = CreateGameObject("Scene", nullptr);

	editorCameraObject = CreateGameObject("Editor Camera", mRootNode);

	gameCameraObject = CreateGameObject("Game Camera", mRootNode);

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

	ysceneFile.CreateJSON(External->fileSystem->libraryScenesPath, std::to_string(mRootNode->UID) + ".yscene");

	editorCameraObject->AddComponent(App->camera->editorCamera);
	cameras.push_back(App->camera->editorCamera);

	gameCameraComponent = new CCamera(gameCameraObject);

	gameCameraComponent->SetPos(0.0f, 2.0f, 20.0f);
	gameCameraComponent->LookAt(float3(0.f, 0.f, 0.f));
	gameCameraComponent->SetAspectRatio(SCREEN_WIDTH / SCREEN_HEIGHT);

	gameCameraObject->AddComponent(gameCameraComponent);
	cameras.push_back(gameCameraComponent);

	currentCamera = App->camera->editorCamera;

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

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {

		currentCamera = App->camera->editorCamera;

	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {

		currentCamera = gameCameraComponent;

	}

	currentCamera->Update();

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	OPTICK_EVENT();

	for (auto& it = cameras.begin(); it != cameras.end(); ++it) {

		(*it)->DrawFrustumBox();

	}

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
