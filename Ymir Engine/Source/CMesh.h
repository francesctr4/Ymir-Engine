#pragma once

#include "Component.h"

class CMesh : public Component {
public:

	CMesh();
	virtual ~CMesh();

	void Enable() override;
	void Disable() override;

	void Update() override;
	void OnEditor() override;


public:

};