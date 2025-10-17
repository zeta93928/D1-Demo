#pragma once

struct InstanceList
{
	void Clear();
	void AddData(const InstanceData& data);

	Vector<InstanceData> datas;
};

class InstancingManager
{
	DECLARE_SINGLETON(InstancingManager);
public:
	void Render(const Vector<ActorRef>& actors);
private:
	void RenderPrimitive(const Vector<ActorRef>& actors);
	void RenderStaticMesh(const Vector<ActorRef>& actors);
	void RenderSkeletalMesh(const Vector<ActorRef>& actors);

	void AddData(InstanceID id, InstanceData data);
	void ClearData();

private:
	Map<InstanceID, InstanceList> m_instanceListTable;
};

