#include "pch.h"
#include "ComponentBase.h"
#include "Actor.h"

ComponentBase::ComponentBase(ComponentType type)
	: m_type(type)
{
}

ComponentBase::~ComponentBase()
{
}

ActorRef ComponentBase::GetActor()
{
	return m_actor.lock();
}

SceneComponentRef ComponentBase::GetSceneComponent()
{
	return m_actor.lock()->GetSceneComponent();
}
