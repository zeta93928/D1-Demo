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
}

void PrimitiveComponent::Update()
{
	static float dt = 0.f;
	dt += 0.0001f;

	IPrimitiveRenderData* primitiveRenderData =  m_mesh->GetPrimitiveRenderData();

	//
	// Renderer ������ Transform ���� ������Ʈ
	// @TODO: ���⼭ Transform ������ �����ϰ� LateUpdate() ���� Draw call �� �����ϸ�
	// Renderer �� ���ҽ��� ���� ���ҽ��̱� ������ Transform ������ �ϳ��� ���ŵǾ� �� ��ġ�� ǥ������ ���Ѵ�.
	// 
	// GPU Instancing �� Ȯ��
	// RenderStaticMeshRenderData() �� �Ķ���ͷ� ���� ���

	TransformRenderData transformData = {};
	transformData.world = Matrix::CreateRotationY(dt) * GetSceneComponent()->GetWorldMatrix();
	RenderProxy::Get().EnqueueTransformData(primitiveRenderData, transformData);







	// Renderer�� Draw call ����
	GRenderer->RenderStaticMeshRenderData(primitiveRenderData);
}

void PrimitiveComponent::LateUpdate()
{
}

void PrimitiveComponent::SetMaterialAsset(MaterialAssetRef material)
{
	IPrimitiveRenderData* primitiveRenderData = m_mesh->GetPrimitiveRenderData();
	if (!primitiveRenderData)
	{
		return;
	}

	m_material = material;

	// Renderer ������ Material ���� ������Ʈ
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();
	// void* normal = m_material->GetNormalMap()->GetTextureHandle();
	MaterialRenderData materialData = {};
	materialData.albedo = albedo;
	// materialData.normal = normal;
	RenderProxy::Get().EnqueueMaterialData(primitiveRenderData, materialData);
}
