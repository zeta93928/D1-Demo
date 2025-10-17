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
	// Renderer 측으로 Transform 정보 업데이트
	// @TODO: 여기서 Transform 정보를 전달하고 LateUpdate() 에서 Draw call 을 진행하면
	// Renderer 측 리소스가 공유 리소스이기 때문에 Transform 정보가 하나로 갱신되어 각 위치를 표현하지 못한다.
	// 
	// GPU Instancing 쪽 확인
	// RenderStaticMeshRenderData() 에 파라미터로 전달 고려

	TransformRenderData transformData = {};
	transformData.world = Matrix::CreateRotationY(dt) * GetSceneComponent()->GetWorldMatrix();
	RenderProxy::Get().EnqueueTransformData(primitiveRenderData, transformData);







	// Renderer에 Draw call 전달
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

	// Renderer 측으로 Material 정보 업데이트
	void* albedo = m_material->GetAlbedoMap()->GetTextureHandle();
	// void* normal = m_material->GetNormalMap()->GetTextureHandle();
	MaterialRenderData materialData = {};
	materialData.albedo = albedo;
	// materialData.normal = normal;
	RenderProxy::Get().EnqueueMaterialData(primitiveRenderData, materialData);
}
