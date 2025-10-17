#pragma once

class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();

	virtual void Add(ActorRef actor);
	virtual void Remove(ActorRef actor);

private:
	HashSet<ActorRef> m_actors;

	// Camera Cache
	HashSet<ActorRef> m_cameras;

	// Light Cache
	HashSet<ActorRef> m_lights;
};

