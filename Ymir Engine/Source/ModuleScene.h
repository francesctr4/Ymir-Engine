#pragma once

#include <vector>
#include <map>

#include "Module.h"

#include "External/Assimp/include/cimport.h"
#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/postprocess.h"

#include "External/MathGeoLib/include/Geometry/LineSegment.h"

#include "JsonFile.h"

class GameObject;
class CCamera;

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

	void SaveScene();
	void LoadScene();

	// Function to handle GameObject selection by Mouse Picking
	void HandleGameObjectSelection(const LineSegment& ray);

	// Function to test if picking inside an AABB
	bool IsInsideAABB(const float3& point, const AABB& aabb);

public:

	GameObject* mRootNode;

	GameObject* gameCameraObject;
	CCamera* gameCameraComponent;

	//CCamera* currentCamera;
	std::vector<CCamera*> cameras;

	std::vector<GameObject*> gameObjects;

	JsonFile ysceneFile;

};