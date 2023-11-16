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

	drawBoundingBoxes = true;
	frustumCulling = true;
	active = true;
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

	DrawFrustumBox();
}

void CCamera::OnInspector()
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::CollapsingHeader("Camera", flags))
	{
		ImGui::Indent();

		// Set Horizontal FOV

		float hfov = GetHorizontalFOV();

		if (ImGui::SliderFloat("Horizontal FOV", &hfov, 30, 120, "%0.2f", ImGuiSliderFlags_None)) { 

			SetHorizontalFOV(hfov); 

		}

		// Set Vertical FOV

		float vfov = GetVerticalFOV();

		if (ImGui::SliderFloat("Vertical FOV", &vfov, 30, 120, "%0.2f", ImGuiSliderFlags_None)) {

			SetVerticalFOV(vfov);

		}

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

float3 CCamera::GetPos() const
{
	return frustum.pos;
}

void CCamera::SetFront(float3 front)
{
	frustum.front = front;
}

void CCamera::SetUp(float3 up)
{
	frustum.up = up;
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

void CCamera::LookAt(const float3& Spot)
{
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}