#include "CCamera.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

CCamera::CCamera(GameObject* owner) : Component(owner, ComponentType::CAMERA)
{
	this->mOwner = owner;

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 1000.0f;

	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.3f);

	drawBoundingBoxes = false;
	enableFrustumCulling = true;

}

CCamera::~CCamera()
{

}

void CCamera::Enable()
{

}

void CCamera::Disable()
{

}

void CCamera::Update()
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*)GetProjectionMatrix().v);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat*)GetViewMatrix().v);
}

void CCamera::OnInspector()
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::CollapsingHeader("Camera", flags))
	{
		ImGui::Indent();

		// Position (Needs to be reworked into Transform)

		ImGui::SeparatorText("POSITION & ROTATION");

		ImGui::Spacing();

		float* cameraPosition = frustum.pos.ptr();

		ImGui::DragFloat3("Position", cameraPosition, 0.1f);

		ImGui::Spacing();

		// Rotation (Needs to be reworked into Transform)

		float3 rotation = { 0, 0, 0 };

		float* cameraRotation = rotation.ptr();

		ImGui::DragFloat3("Rotation", cameraRotation, 0.1f);

		Quat rotationQuaternion = Quat::FromEulerXYZ(DEGTORAD * rotation.x, DEGTORAD * rotation.y, DEGTORAD * rotation.z);

		rotationQuaternion.Normalize();

		float4x4 rotationMatrix = rotationQuaternion.ToFloat4x4();

		frustum.Transform(rotationMatrix);

		ImGui::Spacing();

		ImGui::SeparatorText("VECTORS (Read only)");

		// Right

		ImGui::Spacing();

		float* cameraRight = frustum.WorldRight().ptr();

		ImGui::InputFloat3("Right", cameraRight, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::Spacing();

		// Up

		ImGui::Spacing();

		float* cameraUp = frustum.up.ptr();

		ImGui::InputFloat3("Up", cameraUp, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::Spacing();

		// Front

		ImGui::Spacing();

		float* cameraFront = frustum.front.ptr();

		ImGui::InputFloat3("Front", cameraFront, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::Spacing();

		ImGui::SeparatorText("CONFIGURATION");

		// Set FOV

		ImGui::Spacing();

		float vfov = GetVerticalFOV();

		if (ImGui::SliderFloat("FOV", &vfov, 30, 120, "%0.2f", ImGuiSliderFlags_None)) {

			SetVerticalFOV(vfov);

		}

		ImGui::Spacing();

		// Set Near Plane

		float nearPlane = GetNearPlane();

		if (ImGui::SliderFloat("Near Plane", &nearPlane, 0.1f, 100.0f, "%0.2f", ImGuiSliderFlags_None)) {

			SetNearPlane(nearPlane); 

		}

		ImGui::Spacing();

		// Set Far Plane

		float farPlane = GetFarPlane();

		if (ImGui::SliderFloat("Far Plane", &farPlane, 1.0f, 1000.0f, "%0.2f", ImGuiSliderFlags_None)) {

			SetFarPlane(farPlane); 

		}

		ImGui::Spacing();

		// Enable/Disable Frustum Culling

		ImGui::Checkbox("Frustum Culling", &enableFrustumCulling);

		ImGui::Spacing();

		// Enable/Disable Bounding Boxes

		ImGui::Checkbox("Draw Bounding Boxes", &drawBoundingBoxes);

		ImGui::Spacing();

		ImGui::Unindent();
	}
}

void CCamera::SetPos(float3 xyz)
{
	frustum.pos = xyz;
}

void CCamera::SetPos(float x, float y, float z)
{
	frustum.pos = float3(x, y, z);
}

void CCamera::UpdatePos(float3 newPos)
{
	frustum.pos += newPos;
}

float3 CCamera::GetPos() const
{
	return frustum.pos;
}

void CCamera::SetNearPlane(float distance)
{
	frustum.nearPlaneDistance = distance;
}

float CCamera::GetNearPlane()
{
	return frustum.nearPlaneDistance;
}

void CCamera::SetFarPlane(float distance)
{
	frustum.farPlaneDistance = distance;
}

float CCamera::GetFarPlane()
{
	return frustum.farPlaneDistance;
}

void CCamera::SetFront(float3 front)
{
	frustum.front = front;
}

void CCamera::SetUp(float3 up)
{
	frustum.up = up;
}

float3 CCamera::GetFront()
{
	return frustum.front;
}

float3 CCamera::GetUp()
{
	return frustum.up;
}

float3 CCamera::GetRight()
{
	return frustum.WorldRight();
}

float CCamera::GetHorizontalFOV() const
{
	return frustum.horizontalFov * RADTODEG;
}

float CCamera::GetVerticalFOV() const
{
	return frustum.verticalFov * RADTODEG;
}

void CCamera::SetHorizontalFOV(float hfov)
{
	frustum.horizontalFov = hfov * DEGTORAD;
}

void CCamera::SetVerticalFOV(float vfov)
{
	frustum.verticalFov = vfov * DEGTORAD;
}

void CCamera::SetBothFOV(float fov)
{
	frustum.horizontalFov = fov * DEGTORAD;
	frustum.verticalFov = fov * DEGTORAD;
}

float CCamera::GetAspectRatio() const
{
	return frustum.AspectRatio();
}

void CCamera::SetAspectRatio(float aspectRatio)
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
}

void CCamera::DrawFrustumBox() const
{
	float3 vertices[8];
	frustum.GetCornerPoints(vertices);
	External->renderer3D->DrawBox(vertices, float3(0, 255, 0));
}

float4x4 CCamera::GetProjectionMatrix() const 
{
	return frustum.ProjectionMatrix().Transposed();
}

float4x4 CCamera::GetViewMatrix() const 
{
	float4x4 tempMat4x4 = frustum.ViewMatrix();

	return tempMat4x4.Transposed();
}

void CCamera::MovementHandling(float3& newPos, float speed)
{
	if (External->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos += GetFront() * speed;
	if (External->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos -= GetFront() * speed;

	if (External->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= GetRight() * speed;
	if (External->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += GetRight() * speed;

	//if (External->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos += GetUp() * speed;
	//if (External->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos -= GetUp() * speed;
}

void CCamera::RotationHandling(float speed, float dt)
{
	int dx = -External->input->GetMouseXMotion();
	int dy = -External->input->GetMouseYMotion();

	float Sensitivity = 0.35f * dt;

	if (dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		float3 rotationAxis(0.0f, 1.0f, 0.0f);
		Quat rotationQuat = Quat::RotateAxisAngle(rotationAxis, DeltaX);

		SetUp(rotationQuat * GetUp());
		SetFront(rotationQuat * GetFront());
	}
	if (dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		Quat rotationQuat = Quat::RotateAxisAngle(GetRight(), DeltaY);

		SetUp(rotationQuat * GetUp());
		SetFront(rotationQuat * GetFront());

		if (GetUp().y < 0.0f)
		{
			SetFront(float3(0.0f, GetFront().y > 0.0f ? 1.0f : -1.0f, 0.0f));

			SetUp(GetFront().Cross(GetRight()));
		}

	}
}

void CCamera::ZoomHandling(float3& newPos, float speed)
{
	if (External->input->GetMouseZ() > 0) newPos += GetFront() * speed;
	if (External->input->GetMouseZ() < 0) newPos -= GetFront() * speed;
}

void CCamera::PanHandling(float3& newPos, float speed, float dt)
{
	int dx = -External->input->GetMouseXMotion();
	int dy = -External->input->GetMouseYMotion();

	float Sensitivity = 1.6f * dt;

	float DeltaX = (float)dx * Sensitivity;
	float DeltaY = (float)dy * Sensitivity;

	newPos -= GetUp() * speed * DeltaY;
	newPos += GetRight() * speed * DeltaX;
}

void CCamera::LookAt(float3& Spot)
{
	float3 Z = (Spot - GetPos()).Normalized();
	SetFront(Z);

	float3 X = float3(0, 1, 0).Cross(GetFront()).Normalized();

	float3 Y = GetFront().Cross(X).Normalized();
	SetUp(Y);
}