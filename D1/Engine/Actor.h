#pragma once

#include "ComponentBase.h"

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor();
	~Actor();

	void Awake();
	void Start();
	void EarlyUpdate();
	void Update();
	void LateUpdate();

	ComponentBaseRef GetFixedComponent(ComponentType type);
	SceneComponentRef GetSceneComponent();
	SceneComponentRef GetOrAddSceneComponent();
	StaticMeshComponentRef GetStaticMeshComponent();
	void AddComponent(ComponentBaseRef component);

private:
	Array<ComponentBaseRef, FIXED_COMPONENT_COUNT> m_components = {};
	Vector<MonoBehaviourRef> m_scripts = {};
};

