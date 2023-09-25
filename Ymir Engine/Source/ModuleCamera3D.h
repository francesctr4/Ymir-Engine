#pragma once
#include "Module.h"
#include "Globals.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"
#include "External/MathGeoLib/include/Geometry/Frustum.h"

// TODO: REMOVE this before 1st delivery!!
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:

	ModuleCamera3D(Application* app, bool start_enabled = true);

	virtual ~ModuleCamera3D();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

	void Look(const float3 &Position, const float3&Reference, bool RotateAroundReference = false);
	void LookAt(const float3&Spot);
	void Move(const float3&Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	//You won't need this after using Frustum

	float3 X, Y, Z, Position, Reference;

private:

	mat4x4 ViewMatrix;

	Frustum mMainCamera; // To use later

};