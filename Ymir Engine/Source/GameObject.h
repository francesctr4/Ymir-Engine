#pragma once

#include <vector>
#include <string>

#include "Globals.h"

#include "Component.h"
#include "CTransform.h"

class GameObject {
public:

	GameObject();
	virtual ~GameObject();

	void Update();

	Component* AddComponent(ComponentType ctype);

public:

	std::string name;
	uint UID;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	CTransform* mTransform; // Meterlo dentro de components.

};