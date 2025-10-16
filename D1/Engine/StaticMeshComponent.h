#pragma once

#include "ComponentBase.h"

class StaticMeshComponent : public ComponentBase
{
public:
	StaticMeshComponent();
	virtual ~StaticMeshComponent();

	virtual void Update() override;

	void SetMeshAsset(MeshAssetRef mesh) { m_mesh = mesh; }
	void SetMaterialAsset(MaterialAssetRef material) { m_material = material; }

private:
	MeshAssetRef m_mesh;
	MaterialAssetRef m_material;

	using Super = ComponentBase;
};

