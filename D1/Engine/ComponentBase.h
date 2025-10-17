#pragma once

enum class ComponentType : uint8
{
	Scene,
	Primitive,
	StaicMesh,
	SkeletalMesh,
	Camera,
	Animator,
	Script,
	End
};

enum
{
	FIXED_COMPONENT_COUNT = (uint8)ComponentType::End - 1
};

class ComponentBase : public std::enable_shared_from_this<ComponentBase>
{
	friend class Actor;
public:
	ComponentBase(ComponentType type);
	virtual ~ComponentBase();

	virtual void Awake() {};
	virtual void Start() {};
	virtual void EarlyUpdate() {};
	virtual void Update() {};
	virtual void LateUpdate() {};

	ComponentType GetType() { return m_type; }
	ActorRef GetActor();
	SceneComponentRef GetSceneComponent();

private:
	void SetActor(ActorRef actor) { m_actor = actor; }

private:
	ComponentType m_type = ComponentType::End;
	
	// Actor ���� ��ȯ ���� ����Ͽ� WeakPtr �� ����
	WeakPtr<Actor> m_actor;
};

