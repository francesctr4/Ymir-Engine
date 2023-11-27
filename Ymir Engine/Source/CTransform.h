#pragma once

#include "Component.h"

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/Quat.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

class CTransform : public Component {
public:

	CTransform(GameObject* owner);
	virtual ~CTransform();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

	void SetPosition();
	void SetRotation();
	void SetScale();

public:

	float3 translation;
	float3 rotation;
	float3 scale;

	float3* translationPtr;
	float3* rotationPtr;
	float3* scalePtr;

	float4x4 mGlobalMatrix;
	float4x4 mLocalMatrix;

	bool resetPressed;

};