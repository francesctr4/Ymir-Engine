#include "GameObject.h"

GameObject::GameObject(std::string name, GameObject* parent)
{
	this->name = name;
	mParent = parent;

	active = true;
	selected = false;

	AddComponent(new CTransform(this));
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

void GameObject::SetParent(GameObject* newParent)
{
	mParent = newParent;
}

void GameObject::AddChild(GameObject* child)
{
	mChildren.push_back(child);
}

void GameObject::AddComponent(Component* component)
{
	mComponents.push_back(component);
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
