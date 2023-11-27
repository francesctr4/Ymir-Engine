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
	// UID regenerated = duplication (This will be fixed with scene serialization)

	mRootNode = CreateGameObject("Scene", nullptr);
	mRootNode->UID = Random::Generate();

	gameCameraObject = CreateGameObject("Main Camera", mRootNode);
	gameCameraObject->UID = Random::Generate();

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

	cameras.push_back(App->camera->editorCamera);

	gameCameraComponent = new CCamera(gameCameraObject);

	gameCameraComponent->SetPos(-40.0f, 29.0f, 54.0f);
	gameCameraComponent->LookAt(float3(0.f, 0.f, 0.f));
	gameCameraComponent->SetAspectRatio(SCREEN_WIDTH / SCREEN_HEIGHT);

	gameCameraObject->AddComponent(gameCameraComponent);
	cameras.push_back(gameCameraComponent);

	// yscene file creation

	ysceneFile.SetFloat3("Editor Camera Position", App->camera->editorCamera->GetPos());
	ysceneFile.SetFloat3("Editor Camera Right (X)", App->camera->editorCamera->GetRight());
	ysceneFile.SetFloat3("Editor Camera Up (Y)", App->camera->editorCamera->GetUp());
	ysceneFile.SetFloat3("Editor Camera Front (Z)", App->camera->editorCamera->GetFront());
	ysceneFile.SetHierarchy("Hierarchy", gameObjects);

	ysceneFile.CreateJSON(External->fileSystem->libraryScenesPath, std::to_string(mRootNode->UID) + ".yscene");

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

		for (auto jt = (*it)->mComponents.begin(); jt != (*it)->mComponents.end(); ++jt) {

			(*jt)->Update();

		}

	}

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {

		ClearScene();

	}

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		SaveScene();

	}

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {

		LoadScene();

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
	if (toDestroy) {

		toDestroy->DestroyGameObject();

	}

}

void ModuleScene::ClearScene()
{
	//JsonFile::DeleteJSON(External->fileSystem->libraryScenesPath + std::to_string(mRootNode->UID) + ".yscene");

	App->editor->DestroyHierarchyTree(mRootNode);
	delete mRootNode;
	mRootNode = nullptr;

	gameObjects.clear();

	App->renderer3D->models.clear();
	mRootNode = CreateGameObject("Scene", nullptr); // Recreate scene
}

void ModuleScene::SaveScene()
{
	ysceneFile.SetFloat3("Editor Camera Position", App->camera->editorCamera->GetPos());
	ysceneFile.SetFloat3("Editor Camera Right (X)", App->camera->editorCamera->GetRight());
	ysceneFile.SetFloat3("Editor Camera Up (Y)", App->camera->editorCamera->GetUp());
	ysceneFile.SetFloat3("Editor Camera Front (Z)", App->camera->editorCamera->GetFront());
	ysceneFile.SetHierarchy("Hierarchy", gameObjects);

	ysceneFile.CreateJSON(External->fileSystem->libraryScenesPath, std::to_string(mRootNode->UID) + ".yscene");
}

void ModuleScene::LoadScene()
{
	JsonFile* sceneToLoad = JsonFile::GetJSON(External->fileSystem->libraryScenesPath + std::to_string(mRootNode->UID) + ".yscene");

	App->camera->editorCamera->SetPos(sceneToLoad->GetFloat3("Editor Camera Position"));
	App->camera->editorCamera->SetUp(sceneToLoad->GetFloat3("Editor Camera Up (Y)"));
	App->camera->editorCamera->SetFront(sceneToLoad->GetFloat3("Editor Camera Front (Z)"));

	ClearScene();

	gameObjects = sceneToLoad->GetHierarchy("Hierarchy");

	delete sceneToLoad;
}

void ModuleScene::HandleGameObjectSelection(const LineSegment& ray)
{
	//std::map<float, Mesh*> mesh_candidates;

	//for (auto it = App->renderer3D->models.begin(); it != App->renderer3D->models.end(); ++it) {
	//	for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {
	//		Mesh* mesh_to_test = &(*jt);  // Assuming meshes are stored by value, adjust if needed

	//		float closest, furthest;
	//		if (ray.Intersects(mesh_to_test->globalAABB, closest, furthest)) {
	//			mesh_candidates[closest] = mesh_to_test;
	//		}
	//	}
	//}

	//std::vector<Mesh*> meshes_sorted;

	//for (auto& candidate : mesh_candidates) {
	//	meshes_sorted.push_back(candidate.second);
	//}

	//// Set all meshes to unselected initially
	//for (Mesh* mesh : meshes_sorted) {
	//	if (mesh != nullptr && mesh->meshGO != nullptr) {
	//		mesh->meshGO->selected = false;
	//	}
	//}

	//for (Mesh* mesh : meshes_sorted) {
	//	if (mesh != nullptr) {
	//		LineSegment local_ray = ray;

	//		// Transform the ray using the mesh's transform
	//		local_ray.Transform(mesh->meshShader.model);

	//		// Iterate over triangles in the mesh
	//		for (uint j = 0; j < mesh->indices.size(); j += 3) {
	//			uint triangle_indices[3] = { mesh->indices[j], mesh->indices[j + 1], mesh->indices[j + 2] };

	//			// Access vertices without multiplying index by 3
	//			float3 point_a(mesh->vertices[triangle_indices[0]].position);
	//			float3 point_b(mesh->vertices[triangle_indices[1]].position);
	//			float3 point_c(mesh->vertices[triangle_indices[2]].position);

	//			Triangle triangle(point_a, point_b, point_c);

	//			if (local_ray.Intersects(triangle, nullptr, nullptr)) {
	//				// Intersection found, set the selected object
	//				if (mesh->meshGO != nullptr) {
	//					mesh->meshGO->selected = true;
	//				}
	//				return;
	//			}
	//		}
	//	}
	//}

	//// No intersection found, clear the selection for all meshes
	//for (Mesh* mesh : meshes_sorted) {
	//	if (mesh != nullptr && mesh->meshGO != nullptr) {
	//		mesh->meshGO->selected = false;
	//	}
	//}
}
