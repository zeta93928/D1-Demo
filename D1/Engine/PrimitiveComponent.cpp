#include "pch.h"
#include "PrimitiveComponent.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "TextureAsset.h"

PrimitiveComponent::PrimitiveComponent()
	: Super(ComponentType::Primitive)
{
}

PrimitiveComponent::~PrimitiveComponent()
{
	int a = 3;
}

void PrimitiveComponent::SetMaterialAsset(MaterialAssetRef material)
{
	IPrimitiveRenderData* primitiveRenderData = m_mesh->GetPrimitiveRenderData();
	if (!primitiveRenderData)
	{
		return;
	}

	m_material = material;

	// Renderer 측으로 Material 정보 업데이트
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();

	MaterialRenderData materialData = {};
	materialData.albedo = albedo;

	RenderProxy::Get().EnqueueMaterialData(primitiveRenderData, materialData);
}

void PrimitiveComponent::RenderInstancing(InstanceList& instanceList)
{
	IPrimitiveRenderData* primitiveRenderData = m_mesh->GetPrimitiveRenderData();

	GRenderer->RenderPrimitiveData(primitiveRenderData, instanceList.datas.data(), (uint32)instanceList.datas.size());
}

InstanceID PrimitiveComponent::GetInstanceID()
{
	return std::make_pair((uint64)m_mesh.get(), (uint64)m_material.get());
}
