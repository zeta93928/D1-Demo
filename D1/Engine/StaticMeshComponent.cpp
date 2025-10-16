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

	// Renderer 측으로 Transform 정보 업데이트
	TransformRenderData transformData = {};
	transformData.world = GetSceneComponent()->GetWorldMatrix() * Matrix::CreateRotationY(dt);
	RenderProxy::Get().EnqueueTransformData(staticMeshRenderData, transformData);

	// Renderer 측으로 Material 정보 업데이트
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();
	// void* normal = m_material->GetNormalMap()->GetTextureHandle();
	MaterialRenderData materialData = {};
	materialData.albedo = albedo;
	// materialData.normal = normal;
	RenderProxy::Get().EnqueueMaterialData(staticMeshRenderData, materialData);

	// Renderer에 Draw call 전달
	GRenderer->RenderStaticMeshRenderData(staticMeshRenderData);
}
