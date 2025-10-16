#pragma once

#include "ComponentBase.h"

class CameraComponent : public ComponentBase
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void Update() override;

private:
	void UpdateMatrix();

	friend class EngineBody;
	static void UpdateWindowSize(uint32 width, uint32 height);

public:
	static Matrix sm_viewMat;
	static Matrix sm_projMat;
	static float sm_aspect;

private:
	Matrix m_viewMat = Matrix::Identity;
	Matrix m_projMat = Matrix::Identity;

	float m_near = 1.f;
	float m_far = 1000.f;
	float m_fov = DirectX::XM_PI / 4.f;

	using Super = ComponentBase;
};

