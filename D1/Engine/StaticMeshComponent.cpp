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
	IStaicMeshRenderData* staticMeshRenderData =  m_mesh->GetStaicMeshRenderData();

	GRenderer->RenderStaticMeshRenderData(staticMeshRenderData);
}
