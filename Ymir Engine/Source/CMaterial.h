#pragma once

#include "Component.h"

#include "Globals.h"
#include <string>

#include "Shader.h"

class GameObject;

class CMaterial : public Component {
public:

	CMaterial(GameObject* owner);
	virtual ~CMaterial();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

	void DdsDragDropTarget();

public:

	// Shaders

	Shader* meshShader;
	int selectedShader;

	// Textures

	uint ID;
	std::string path;

};
