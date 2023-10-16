#pragma once

#include "Component.h"

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/Quat.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

class CTransform : public Component {
public:

	CTransform();
	virtual ~CTransform();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnEditor() override;

	void SetPosition();
	void SetRotation();
	void SetScale();

public:

	float3 position;
	float3 scale;
	Quat rotation;

	float4x4 mGlobalMatrix;
	float4x4 mLocalMatrix;

};