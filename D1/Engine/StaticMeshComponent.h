#pragma once

#include "ComponentBase.h"

class StaticMeshComponent : public ComponentBase
{
public:
	StaticMeshComponent();
	virtual ~StaticMeshComponent();

	virtual void Update() override;

	void SetModel(ModelRef model);

private:
	ModelRef m_model;
};

