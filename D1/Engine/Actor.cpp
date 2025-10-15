#include "pch.h"
#include "Actor.h"
#include "SceneComponent.h"
#include "MonoBehaviour.h"
#include "StaticMeshComponent.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Awake()
{
	for (ComponentBaseRef& component : m_components)
	{
		if (component)
		{
			component->Awake();
		}
	}

	for (MonoBehaviourRef& script : m_scripts)
	{
		script->Start();
	}
}

void Actor::Start()
{
	for (ComponentBaseRef& component : m_components)
	{
		if (component)
		{
			component->Start();
		}
	}

	for (MonoBehaviourRef& script : m_scripts)
	{
		script->Start();
	}
}

void Actor::EarlyUpdate()
{
	for (ComponentBaseRef& component : m_components)
	{
		if (component)
		{
			component->EarlyUpdate();
		}
	}

	for (MonoBehaviourRef& script : m_scripts)
	{
		script->EarlyUpdate();
	}
}

void Actor::Update()
{
	for (ComponentBaseRef& component : m_components)
	{
		if (component)
		{
			component->Update();
		}
	}

	for (MonoBehaviourRef& script : m_scripts)
	{
		script->Update();
	}
}

void Actor::LateUpdate()
{
	for (ComponentBaseRef& component : m_components)
	{
		if (component)
		{
			component->LateUpdate();
		}
	}

	for (MonoBehaviourRef& script : m_scripts)
	{
		script->LateUpdate();
	}
}

ComponentBaseRef Actor::GetFixedComponent(ComponentType type)
{
	uint32 id = (uint8)type;
	assert(id < FIXED_COMPONENT_COUNT);

	return m_components[id];
}

SceneComponentRef Actor::GetSceneComponent()
{
	ComponentBaseRef component = GetFixedComponent(ComponentType::Scene);

	return std::static_pointer_cast<SceneComponent>(component);
}

SceneComponentRef Actor::GetOrAddSceneComponent()
{
	if (GetSceneComponent() == nullptr)
	{
		SceneComponentRef sceneComponent = MakeShared<SceneComponent>();
		AddComponent(sceneComponent);
	}

	return GetSceneComponent();
}

StaticMeshComponentRef Actor::GetStaticMeshComponent()
{
	ComponentBaseRef component = GetFixedComponent(ComponentType::StaticMesh);

	return std::static_pointer_cast<StaticMeshComponent>(component);
}

void Actor::AddComponent(ComponentBaseRef component)
{
	component->SetActor(shared_from_this());

	uint8 id = (uint8)component->GetType();
	if (id < FIXED_COMPONENT_COUNT)
	{
		m_components[id] = component;
	}
	else
	{
		m_scripts.push_back(std::static_pointer_cast<MonoBehaviour>(component));
	}
}