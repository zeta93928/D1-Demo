#include "pch.h"
#include "SceneBase.h"
#include "Actor.h"

void SceneBase::Start()
{
	for (ActorRef actor : m_actors)
	{
		actor->Start();
	}
} 

void SceneBase::Update()
{
	for (ActorRef actor : m_actors)
	{
		actor->Update();
	}

	// Instancing
	{
		Vector<ActorRef> actors;
		actors.insert(actors.end(), m_actors.begin(), m_actors.end());
		InstancingManager::Get().Render(actors);
	}
} 

void SceneBase::LateUpdate()
{
	for (ActorRef actor : m_actors)
	{
		actor->LateUpdate();
	}
}

void SceneBase::Add(ActorRef actor)
{
	m_actors.insert(actor);
}

void SceneBase::Remove(ActorRef actor)
{
	m_actors.erase(actor);
}
