#pragma once

#include <vector>
#include <string>

#include "Globals.h"

#include "Model.h"
#include "Component.h"
#include "CTransform.h"
#include "CMesh.h"
#include "CMaterial.h"

class GameObject {
public:

	GameObject(std::string name, GameObject* parent);
	virtual ~GameObject();

	void Update();

	void Enable();
	void Disable();

	void Select();

	void SetParent(GameObject* newParent);
	void AddChild(GameObject* child);

	Component* AddComponent(ComponentType ctype);
	Component* GetComponent(ComponentType ctype);

	void DestroyGameObject();

public:

	std::string name;
	uint UID;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	CTransform* mTransform; 

	bool active;
	bool selected;

};