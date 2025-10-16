#include "pch.h"
#include "StaticMeshComponent.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "TextureAsset.h"

StaticMeshComponent::StaticMeshComponent()
	: Super(ComponentType::StaticMesh)
{
}

StaticMeshComponent::~StaticMeshComponent()
{
}

void StaticMeshComponent::Update()
{
	static float dt = 0.f;
	dt += 0.0001f;

	IStaticMeshRenderData* staticMeshRenderData =  m_mesh->GetStaicMeshRenderData();

	// Renderer ������ Transform ���� ������Ʈ
	TransformRenderData transformData = {};
	transformData.world = GetSceneComponent()->GetWorldMatrix() * Matrix::CreateRotationY(dt);
	RenderProxy::Get().EnqueueTransformData(staticMeshRenderData, transformData);

	// Renderer ������ Material ���� ������Ʈ
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();
	// void* normal = m_material->GetNormalMap()->GetTextureHandle();
	MaterialRenderData materialData = {};
	materialData.albedo = albedo;
	// materialData.normal = normal;
	RenderProxy::Get().EnqueueMaterialData(staticMeshRenderData, materialData);

	// Renderer�� Draw call ����
	GRenderer->RenderStaticMeshRenderData(staticMeshRenderData);
}
