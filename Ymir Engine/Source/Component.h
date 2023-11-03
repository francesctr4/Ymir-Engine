#pragma once

class GameObject;

enum ComponentType {

	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA

};

class Component {
public:

	Component(GameObject* owner, ComponentType type);
	virtual ~Component();

	virtual void Enable(); 
	virtual void Disable();

	virtual void Update();
	virtual void OnInspector();

public:

	GameObject* mOwner;

	bool active;
	ComponentType ctype;

};