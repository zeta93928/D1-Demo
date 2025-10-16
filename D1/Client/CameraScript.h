#pragma once

#include "../Engine/MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
public:
	virtual void Start() override;
	virtual void Update() override;

private:
	float m_speed = 10.f;
};

