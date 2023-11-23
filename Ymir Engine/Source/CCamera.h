#pragma once

#include "Component.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"
#include "FrameBuffer.h"

#include "Globals.h"
#include <string>

#include "External/MathGeoLib/include/MathGeoLib.h"
#include "External/MathGeoLib/include/Geometry/Frustum.h"

class GameObject;

class CCamera : public Component {
public:

	CCamera(GameObject* owner);
	virtual ~CCamera();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

	void SetPos(float3 xyz);
	void SetPos(float x, float y, float z);

	void UpdatePos(float3 newPos);

	float3 GetPos() const;

	void SetFront(float3 front);
	void SetUp(float3 up);

	float3 GetFront();
	float3 GetUp();
	float3 GetRight();

	float GetHorizontalFOV() const;
	float GetVerticalFOV() const;

	void SetHorizontalFOV(float hfov);
	void SetVerticalFOV(float vfov);
	void SetBothFOV(float fov);

	float GetAspectRatio() const;
	void SetAspectRatio(float aspectRatio);

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;

	// --------------------------------------------------

	void MovementHandling(float3& newPos, float speed);
	void RotationHandling(float speed, float dt);
	void ZoomHandling(float3& newPos, float speed);
	void PanHandling(float3& newPos, float speed, float dt);

	void LookAt(float3& Spot);

	void DrawFrustumBox() const;

public:

	Frustum frustum;

	bool drawBoundingBoxes;
	bool enableFrustumCulling;

	FrameBuffer framebuffer;

};