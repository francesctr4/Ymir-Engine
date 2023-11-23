#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "Log.h"
#include "GameObject.h"

#include "External/MathGeoLib/include/Math/Quat.h"

#include "External/Optick/include/optick.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	editorCamera = new CCamera(nullptr);

	editorCamera->SetPos(0.0f, 2.0f, 8.0f);
	editorCamera->LookAt(float3(0.f, 0.f, 0.f));
	editorCamera->SetAspectRatio(SCREEN_WIDTH/SCREEN_HEIGHT);

	LOG("Creating ModuleCamera3D");

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	OPTICK_EVENT();

	float3 newPos(0, 0, 0);

	float speed = 20.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) speed *= 2;

	// Mouse wheel Zoom In and Zoom Out handling

	editorCamera->ZoomHandling(newPos, speed);

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

		// Mouse wheel pressed while dragging movement handling

		editorCamera->PanHandling(newPos, speed, dt);

	}

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_IDLE) {

		// WASD Camera Movement Handling

		editorCamera->MovementHandling(newPos, speed);

		// Camera Rotation Handling

		editorCamera->RotationHandling(speed, dt);

	}
	
	editorCamera->UpdatePos(newPos);

	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) && App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_IDLE) {

		// Center camera to 0,0,0 when pressing Left Alt

		editorCamera->LookAt(float3(0.0f, 0.0f, 0.0f));

	}

	CreateMousePickingRay();

	return UPDATE_CONTINUE;
}

void ModuleCamera3D::CreateMousePickingRay()
{
	float2 origin = float2(App->input->GetMouseX(), App->input->GetMouseY());

	origin.Normalize();

	mousePickingRay = editorCamera->frustum.UnProjectLineSegment(origin.x, origin.y);

	bool hit;

	for (auto it = App->renderer3D->models.begin(); it != App->renderer3D->models.end(); ++it) {

		for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

			hit = mousePickingRay.Intersects((*jt).globalAABB); // Ray vs. AABB

			// (*jt).meshGO->selected = hit;

		}

	}

	// bool hit = ray_local_space.Intersects(tri, &distance, &hit_point); // ray vs. triangle

}