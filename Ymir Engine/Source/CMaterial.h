#pragma once

#include "Component.h"

#include "Globals.h"
#include <string>
#include <filesystem>

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

	int selectedShader;

	// Textures

	uint ID;
	std::string path;

};
