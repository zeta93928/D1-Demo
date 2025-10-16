#include "pch.h"
#include "StaticMeshComponent.h"
#include "MeshAsset.h"

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

	// 이부분에서 Renderer 측으로 Transform 정보 업데이트
	TransformRenderData transformData = {};
	transformData.world = GetSceneComponent()->GetWorldMatrix() * Matrix::CreateRotationY(dt);
	RenderProxy::Get().EnqueueTransformData(staticMeshRenderData, transformData);

	// Renderer에 Draw call 전달
	GRenderer->RenderStaticMeshRenderData(staticMeshRenderData);
}
