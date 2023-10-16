#include "ModuleScene.h"

#include "GameObject.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mRootNode = new GameObject();
	gameObjects.push_back(mRootNode);
}

ModuleScene::~ModuleScene()
{
	delete mRootNode;
}

bool ModuleScene::Start()
{
	bool ret = true;

	const aiScene* aiscene;

	//Start from aiScene::mRootNode then go recursive from there
	//Then loop aiNode::mNumChildren
	//then deal with each aiNode::mChildren[n]

	//mRootNode->mChildren[];

	//ProcessNode(aiscene->mRootNode, aiscene);

	return ret;
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

void ModuleScene::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}
