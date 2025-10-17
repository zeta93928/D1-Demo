#include "pch.h"
#include "InstancingManager.h"
#include "Actor.h"
#include "PrimitiveComponent.h"

void InstanceList::Clear()
{
	datas.clear();
}

void InstanceList::AddData(const InstanceData& data)
{
	datas.push_back(data);
}

void InstancingManager::Render(const Vector<ActorRef>& actors)
{
	ClearData();

	RenderPrimitive(actors);
	RenderStaticMesh(actors);
	RenderSkeletalMesh(actors);
}

void InstancingManager::RenderPrimitive(const Vector<ActorRef>& actors)
{
	Map<InstanceID, Vector<ActorRef>> cache;
	
	for (const ActorRef& actor : actors)
	{
		if (actor->GetPrimitiveComponent() == nullptr)
		{
			continue;
		}

		const InstanceID id = actor->GetPrimitiveComponent()->GetInstanceID();
		cache[id].push_back(actor);
	}

	for (auto& ele : cache)
	{
		const Vector<ActorRef>& actorList = ele.second;
		{
			const InstanceID id = ele.first;

			for (int32 i = 0; i < actorList.size(); i++)
			{
				const ActorRef& actor = actorList[i];
				InstanceData data;
				data.world = actor->GetSceneComponent()->GetWorldMatrix().Transpose();

				AddData(id, data);
			}

			InstanceList& instanceList = m_instanceListTable[id];
			actorList[0]->GetPrimitiveComponent()->RenderInstancing(instanceList);
		}
	}
}

void InstancingManager::RenderStaticMesh(const Vector<ActorRef>& actors)
{
}

void InstancingManager::RenderSkeletalMesh(const Vector<ActorRef>& actors)
{
}

void InstancingManager::AddData(InstanceID id, InstanceData data)
{
	m_instanceListTable[id].AddData(data);
}

void InstancingManager::ClearData()
{
	for (auto& ele : m_instanceListTable)
	{
		InstanceList& data = ele.second;
		data.Clear();
	}
}
