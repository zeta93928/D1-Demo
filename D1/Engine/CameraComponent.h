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

public:
	static Matrix sm_viewMat;
	static Matrix sm_projMat;

private:
	Matrix m_viewMat = Matrix::Identity;
	Matrix m_projMat = Matrix::Identity;

	float m_near = 1.f;
	float m_far = 1000.f;
	float m_fov = DirectX::XM_PI / 4.f;
	float m_aspect = 1.0f;

	using Super = ComponentBase;
};

