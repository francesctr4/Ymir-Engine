#pragma once

#include "Component.h"

#include "Application.h"
#include "ModuleRenderer3D.h"

#include "Globals.h"
#include <string>

#include "External/MathGeoLib/include/MathGeoLib.h"
#include "External/MathGeoLib/include/Geometry/Frustum.h"
#include "External/MathGeoLib/include/Geometry/Plane.h"

class GameObject;

class CCamera : public Component {
public:

	CCamera(GameObject* owner);
	virtual ~CCamera();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

	void SetPos(float x, float y, float z);

	float GetHorizontalFOV() const;
	float GetVerticalFOV() const;

	void SetFOV(float hfov, float vfov);

	float GetAspectRatio() const;

	void GetFrustumPlanes(Plane* planes) const;

	void DrawFrustumPlanes(Plane* planes) const;

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;

public:

	GameObject* owner;

	Frustum frustum;

	bool drawBoundingBoxes;
	bool frustumCulling;
	bool active;

};