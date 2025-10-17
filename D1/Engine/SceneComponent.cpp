#include "pch.h"
#include "SceneComponent.h"

SceneComponent::SceneComponent()
	: Super(ComponentType::Scene)
{
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::Awake()
{

}

void SceneComponent::Update()
{

}

// Quaternion to euler angle 
Vector3 ToEulerAngles(Quaternion q)
{
	Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = (float)std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2.f * (float)std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = (float)std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void SceneComponent::UpdateTransform()
{
	// Scale * Roation * Translation
	Matrix matScale = Matrix::CreateScale(m_localScale);
	Matrix matRotation = Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(m_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(m_localPosition);

	m_localMat = matScale * matRotation * matTranslation;

	if (HasParent())
	{
		m_worldMat = m_localMat * m_parent->GetWorldMatrix();
	}
	else
	{
		m_worldMat = m_localMat;
	}

	Quaternion q;
	m_worldMat.Decompose(m_worldScale, q, m_worldPosition);
	m_worldRotation = ToEulerAngles(q);

	// Child ¼øÈ¸
	for (const SceneComponentRef& child : m_child)
	{
		child->UpdateTransform();
	}
}

void SceneComponent::SetScale(const Vector3& scale)
{
	if (HasParent())
	{
		Vector3 parentScale = m_parent->GetScale();
		Vector3 scale = m_worldScale;
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
		SetLocalScale(scale);
	}
	else
	{
		SetLocalScale(m_worldScale);
	}
}

void SceneComponent::SetRotation(const Vector3& rotation)
{
	if (HasParent())
	{
		Matrix inverseMatrix = m_parent->GetWorldMatrix().Invert();

		Vector3 rotation;
		rotation.TransformNormal(rotation, inverseMatrix);

		SetLocalRotation(rotation);
	}
	else
	{
		SetLocalRotation(rotation);
	}
}

void SceneComponent::SetPosition(const Vector3& pos)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = m_parent->GetWorldMatrix().Invert();

		Vector3 position;
		position.Transform(pos, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(pos);
	}
}
