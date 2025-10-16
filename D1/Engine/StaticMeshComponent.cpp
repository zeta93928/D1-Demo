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

	// �̺κп��� Renderer ������ Transform ���� ������Ʈ
	TransformRenderData transformData = {};
	transformData.world = GetSceneComponent()->GetWorldMatrix() * Matrix::CreateRotationY(dt);
	RenderProxy::Get().EnqueueTransformData(staticMeshRenderData, transformData);

	// Renderer�� Draw call ����
	GRenderer->RenderStaticMeshRenderData(staticMeshRenderData);
}
