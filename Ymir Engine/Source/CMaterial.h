#pragma once

#include "Component.h"

class CMaterial : public Component {
public:

	CMaterial(GameObject* owner);
	virtual ~CMaterial();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnInspector() override;

public:

};
