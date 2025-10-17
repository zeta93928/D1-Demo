#pragma once

#include "ComponentBase.h"

class PrimitiveComponent : public ComponentBase
{
public:
	PrimitiveComponent();
	virtual ~PrimitiveComponent();

	virtual void Update() override;
	virtual void LateUpdate() override;

	void SetMeshAsset(MeshAssetRef mesh) { m_mesh = mesh; }
	void SetMaterialAsset(MaterialAssetRef material);

private:
	MeshAssetRef m_mesh;
	MaterialAssetRef m_material;

	using Super = ComponentBase;
};

