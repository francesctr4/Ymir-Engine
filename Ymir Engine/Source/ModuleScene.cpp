#include "ModuleScene.h"

#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = CreateGameObject("Scene", nullptr);
	gameObjects.push_back(mRootNode);
}

ModuleScene::~ModuleScene()
{
	delete mRootNode;
}

bool ModuleScene::Start()
{
	bool ret = true;

	GameObject* uno = CreateGameObject("Uno", mRootNode);

	GameObject* uno_uno = CreateGameObject("Unouno", uno);

	GameObject* dos = CreateGameObject("Dos", mRootNode);

	GameObject* tres = CreateGameObject("Tres", mRootNode);

	GameObject* tres_tres = CreateGameObject("Trestres", tres);

	GameObject* tres_trestres = CreateGameObject("Trestrestres", tres_tres);

	GameObject* tres_trestrestres = CreateGameObject("Trestrestrestres", tres_trestres);

	GameObject* cuatro = CreateGameObject("Cuatro", mRootNode);

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

void ModuleScene::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}
