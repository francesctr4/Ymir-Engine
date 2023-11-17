#pragma once
#include "Module.h"
#include "Globals.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"
#include "External/MathGeoLib/include/Geometry/Frustum.h"

#include "CCamera.h"

class ModuleCamera3D : public Module
{
public:

	ModuleCamera3D(Application* app, bool start_enabled = true);

	virtual ~ModuleCamera3D();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

public:

	CCamera* editorCamera;

};