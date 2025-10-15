#pragma once

#include "ComponentBase.h"

class SceneComponent : public ComponentBase
{
public:
	SceneComponent();
	virtual ~SceneComponent();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	Vector3 GetLocalScale() { return m_localScale; }
	void SetLocalScale(const Vector3& localScale) { m_localScale = localScale; UpdateTransform(); }
	Vector3 GetLocalRotation() { return m_localRotation; }
	void SetLocalRotation(const Vector3& localRotation) { m_localRotation = localRotation; UpdateTransform(); }
	Vector3 GetLocalPosition() { return m_localPosition; }
	void SetLocalPosition(const Vector3& localPosition) { m_localPosition = localPosition; UpdateTransform(); }

	// World
	Vector3 GetScale() { return m_worldScale; }
	void SetScale(const Vector3& scale);
	Vector3 GetRotation() { return m_worldRotation; }
	void SetRotation(const Vector3& rotation);
	Vector3 GetPosition() { return m_worldPosition; }
	void SetPosition(const Vector3& pos);

	// Direction
	Vector3 GetRight() { return m_worldMat.Right(); }
	Vector3 GetUp() { return m_worldMat.Up(); }
	Vector3 GetLook() { return m_worldMat.Backward(); }

	bool HasParent() { return m_parent != nullptr; }
	SceneComponentRef GetParent() { return m_parent; }
	const Vector<SceneComponentRef>& GetChild() { return m_child; }
	void AddChild(SceneComponentRef child) { m_child.push_back(child); }

	Matrix GetWorldMatrix() { return m_worldMat; }

private:
	Vector3 m_localScale = Vector3(1.0f);
	Vector3 m_localRotation = {};
	Vector3 m_localPosition = {};

	Matrix m_localMat = Matrix::Identity;
	Matrix m_worldMat = Matrix::Identity;

	Vector3 m_worldScale = Vector3(1.0f);
	Vector3 m_worldRotation = {};
	Vector3 m_worldPosition = {};
	
	SceneComponentRef m_parent;
	Vector<SceneComponentRef> m_child = {};

	using Super = ComponentBase;
};

