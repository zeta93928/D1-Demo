#pragma once

#include "ComponentBase.h"

class MonoBehaviour : public ComponentBase
{
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();

	virtual void Awake() override;
	virtual void Update() override;

private:
	using Super = ComponentBase;
};

