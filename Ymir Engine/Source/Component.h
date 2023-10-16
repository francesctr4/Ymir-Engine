#pragma once

class GameObject;

enum ComponentType {

	TRANSFORM,
	MESH,
	MATERIAL

};

class Component {
public:

	Component();
	virtual ~Component();

	virtual void Enable(); 
	virtual void Disable();

	virtual void Update();
	virtual void OnEditor();

public:

	GameObject* mOwner;

	bool active;
	ComponentType ctype;

};