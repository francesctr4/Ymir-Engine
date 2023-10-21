#include "GameObject.h"

GameObject::GameObject(std::string name, GameObject* parent)
{
	this->name = name;
	mParent = parent;

	AddComponent(ComponentType::TRANSFORM);
}

GameObject::~GameObject()
{
	DestroyGameObject();
}

void GameObject::Update()
{

}

void GameObject::Enable()
{
	if (!active) {
		active = true;
	}
}

void GameObject::Disable()
{
	if (active) {
		active = false;
	}
}

void GameObject::Select()
{
	selected = true;
}

void GameObject::SetParent(GameObject* newParent)
{
	mParent = newParent;
}

void GameObject::AddChild(GameObject* child)
{
	mChildren.push_back(child);
}

Component* GameObject::AddComponent(ComponentType ctype)
{
	Component* tempComponent;

	switch (ctype)
	{
		case TRANSFORM:

			tempComponent = new CTransform(this);
			break;

		case MESH:

			tempComponent = new CMesh(this);
			break;

		case MATERIAL:

			tempComponent = new CMaterial(this);
			break;

	}

	mComponents.push_back(tempComponent);

	return tempComponent;
}

Component* GameObject::GetComponent(ComponentType ctype)
{
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

		if ((*it)->ctype == ctype) {

			return (*it);

		}

	}

	return nullptr;
}

void GameObject::DestroyGameObject()
{
	mTransform = nullptr;

	for (std::vector<GameObject*>::reverse_iterator it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
	}

}
