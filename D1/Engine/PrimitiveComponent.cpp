#include "pch.h"
#include "PrimitiveComponent.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "TextureAsset.h"

PrimitiveComponent::PrimitiveComponent()
	: Super(ComponentType::StaticMesh)
{
}

PrimitiveComponent::~PrimitiveComponent()
{
}

void PrimitiveComponent::Update()
{
	static float dt = 0.f;
	dt += 0.00001f;

	IPrimitiveRenderData* primitiveRenderData =  m_mesh->GetPrimitiveRenderData();

	// Renderer ������ Transform ���� ������Ʈ
	TransformRenderData transformData = {};
	transformData.world = Matrix::CreateRotationY(dt) * GetSceneComponent()->GetWorldMatrix();
	RenderProxy::Get().EnqueueTransformData(primitiveRenderData, transformData);

	// Renderer ������ Material ���� ������Ʈ
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();
	// void* normal = m_material->GetNormalMap()->GetTextureHandle();
	MaterialRenderData materialData = {};
	materialData.albedo = albedo;
	// materialData.normal = normal;
	RenderProxy::Get().EnqueueMaterialData(primitiveRenderData, materialData);

	// Renderer�� Draw call ����
	GRenderer->RenderStaticMeshRenderData(primitiveRenderData);
}
