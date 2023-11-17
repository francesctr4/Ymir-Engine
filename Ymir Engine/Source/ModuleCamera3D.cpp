#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "Log.h"

#include "External/MathGeoLib/include/Math/Quat.h"

#include "External/Optick/include/optick.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	Position = float3(0.0f, 2.0f, 8.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);

	// Frustrum

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
/*
update_status ModuleCamera3D::Update(float dt)
{
	OPTICK_EVENT();

	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	float3 newPos(0, 0, 0);
	float speed = 20.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed *= 2;

	// Mouse wheel Zoom In and Zoom Out handling

	if (App->input->GetMouseZ() > 0) newPos -= Z * speed;
	if (App->input->GetMouseZ() < 0) newPos += Z * speed;

	// Mouse wheel pressed while dragging movement handling

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 1.6f * dt;

		float DeltaX = (float)dx * Sensitivity;
		float DeltaY = (float)dy * Sensitivity;

		newPos -= Y * speed * DeltaY;
		newPos += X * speed * DeltaX;

	}

	// Mouse motion ----------------

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_IDLE)
	{
		//if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
		//if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.35f * dt;

		Position -= Reference;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			float3 rotationAxis(0.0f, 1.0f, 0.0f);
			Quat rotationQuat = Quat::RotateAxisAngle(rotationAxis, DeltaX);

			X = rotationQuat * X;
			Y = rotationQuat * Y;
			Z = rotationQuat * Z;
		}
		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Quat rotationQuat = Quat::RotateAxisAngle(X, DeltaY);

			Y = rotationQuat * Y;
			Z = rotationQuat * Z;

			if (Y.y < 0.0f)
			{
				Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = Z.Cross(X);
			}

		}

		Position = Reference + Z * Position.Length();

	}

	Position += newPos;
	Reference += newPos;

	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) && App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_IDLE) {

		// Center camera to 0,0,0 when pressing Left Alt

		Reference = float3(0.0f, 0.0f, 0.0f);
		LookAt(Reference);

	}
	else {

		// Orbital camera FPS when we aren't pressing Left Alt

		Reference = Position;

	}

	// Recalculate matrix -------------
	CalculateViewMatrix();

	editorCamera->DrawFrustumBox();

	return UPDATE_CONTINUE;
}

// Update Camera with Frustrum (In Progress)
*/
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

	return UPDATE_CONTINUE;
}