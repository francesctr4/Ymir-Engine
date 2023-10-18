#include "GameObject.h"

GameObject::GameObject()
{
	mParent = nullptr;

	AddComponent(ComponentType::TRANSFORM);
}

GameObject::~GameObject()
{
	mTransform = nullptr;

	for (std::vector<GameObject*>::reverse_iterator it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
	}
}

void GameObject::Update()
{

}

Component* GameObject::AddComponent(ComponentType ctype)
{

	return nullptr;
}
