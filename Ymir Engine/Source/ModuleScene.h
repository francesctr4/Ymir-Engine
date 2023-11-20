#pragma once

#include <vector>
#include "Module.h"

#include "External/Assimp/include/cimport.h"
#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/postprocess.h"

#include "JsonFile.h"

class GameObject;

class ModuleScene : public Module
{
public:

	ModuleScene(Application* app, bool start_enabled = true);

	virtual ~ModuleScene();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	GameObject* CreateGameObject(std::string name, GameObject* parent);
	void DestroyGameObject(GameObject* toDestroy);

	void ClearScene();

public:

	GameObject* mRootNode;
	GameObject* editorCamera;

	GameObject* gameCamera;

	std::vector<GameObject*> gameObjects;

	JsonFile ysceneFile;

};