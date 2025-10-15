#include "pch.h"
#include "CameraComponent.h"
#include "SceneComponent.h"

Matrix CameraComponent::sm_viewMat = Matrix::Identity;
Matrix CameraComponent::sm_projMat = Matrix::Identity;

CameraComponent::CameraComponent()
	: Super(ComponentType::Camera)
{
	float width = EngineBody::Get().GetGameDesc().screenWidth;
	float height = EngineBody::Get().GetGameDesc().screenHeight;

	m_aspect = width / height;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	UpdateMatrix();
}

void CameraComponent::UpdateMatrix()
{
	using namespace DirectX;

	Vector3 eyePos = GetSceneComponent()->GetPosition();
	Vector3 focusPos = eyePos + GetSceneComponent()->GetLook();
	Vector3 upDir = GetSceneComponent()->GetUp();

	// View Matrix 계산
	sm_viewMat = XMMatrixLookAtLH(eyePos, focusPos, upDir);

	// Proj Matrix 계산
	sm_projMat = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);
}
