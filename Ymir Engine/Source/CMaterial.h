#pragma once

#include "Component.h"

class CMaterial : public Component {
public:

	CMaterial();
	virtual ~CMaterial();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnEditor() override;


public:

};
