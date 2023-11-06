#pragma once

#include "Component.h"

#include "Globals.h"
#include <string>

class GameObject;

class CCamera : public Component {
public:

	CCamera(GameObject* owner);
	virtual ~CCamera();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

public:

	GameObject* owner;

	// TODO: FRUSTRUM

};