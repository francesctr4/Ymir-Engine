#pragma once

#include "Application.h"

class Application;
struct PhysBody3D;

class Module
{
public:

	Module(Application* parent, bool start_enabled = true);
	virtual ~Module();

	virtual bool Init();
	virtual bool Start();

	virtual update_status PreUpdate(float dt);
	virtual update_status Update(float dt);
	virtual update_status PostUpdate(float dt);

	virtual bool CleanUp();

	virtual void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	Application* App;

private:

	bool enabled = false;

};