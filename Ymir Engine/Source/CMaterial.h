#ifndef __COMPONENT_MATERIAL__
#define __COMPONENT_MATERIAL__

#include "Component.h"

#include <string>
#include <filesystem>

#include "Globals.h"

class GameObject;

class CMaterial : public Component {
public:

	// Constructor
	CMaterial(GameObject* owner);

	// Destructor
	virtual ~CMaterial();

	// Inherited functions
	void Enable() override;
	void Disable() override;
	void Update() override;
	void OnInspector() override;

	// Function to activate Drag and Drop of textures on Inspector
	void DdsDragDropTarget();

public:

	// Shaders

	int selectedShader;

	// Textures

	uint ID;
	std::string path;

};

#endif // __COMPONENT_MATERIAL__