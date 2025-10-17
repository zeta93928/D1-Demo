#include "pch.h"
#include "StaticMeshComponent.h"
#include "Model.h"

StaticMeshComponent::StaticMeshComponent()
	: ComponentBase(ComponentType::StaicMesh)
{
}

StaticMeshComponent::~StaticMeshComponent()
{
}

void StaticMeshComponent::Update()
{
}

void StaticMeshComponent::SetModel(ModelRef model)
{
	m_model = model;

	Vector<MaterialAssetRef> materials =  m_model->GetMaterials();
	for (MaterialAssetRef& material : materials)
	{
		
	}
}
