#include "Component.h"
#include "GameObject.h"

Component::Component()
{
	mOwner = nullptr;
	ctype = ComponentType::NONE;

	active = true;
}

Component::Component(GameObject* owner, ComponentType type)
{
	mOwner = owner;
	ctype = type;

	active = true;
}

Component::~Component()
{

}

void Component::Enable()
{

}

void Component::Disable()
{

}

void Component::Update()
{

}

void Component::OnInspector()
{

}
