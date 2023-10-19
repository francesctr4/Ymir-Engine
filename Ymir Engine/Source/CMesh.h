#pragma once

#include "Component.h"

class CMesh : public Component {
public:

	CMesh(GameObject* owner);
	virtual ~CMesh();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;


public:

};