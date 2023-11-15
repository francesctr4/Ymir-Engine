#include "CCamera.h"

CCamera::CCamera(GameObject* owner) : Component(owner, ComponentType::CAMERA)
{
	frustum.type = PerspectiveFrustum;
	frustum.pos = float3(0,0,0);
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 1000.0f;

	frustum.verticalFov = 1.0f;
	frustum.horizontalFov = 1.0f;

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

}

void CCamera::OnInspector()
{

}

void CCamera::SetPos(float x, float y, float z)
{
	frustum.pos = float3(x, y, z);
}

float CCamera::GetHorizontalFOV() const
{
	return frustum.horizontalFov;
}

float CCamera::GetVerticalFOV() const
{
	return frustum.verticalFov;
}

void CCamera::SetFOV(float hfov, float vfov)
{
	frustum.horizontalFov = hfov * DEGTORAD;
	frustum.verticalFov = vfov * DEGTORAD;
}

float CCamera::GetAspectRatio() const
{
	return frustum.AspectRatio();
}

void CCamera::GetFrustumPlanes(Plane* planes) const
{
	return frustum.GetPlanes(planes);
}

void CCamera::DrawFrustumPlanes(Plane* planes) const 
{
	for (size_t i = 0; i < 6; ++i) {

		External->renderer3D->DrawFrustumPlane(planes[i]);

	}
}

float4x4 CCamera::GetProjectionMatrix() const 
{
	return frustum.ProjectionMatrix();
}

float4x4 CCamera::GetViewMatrix() const 
{
	return frustum.ViewMatrix();
}