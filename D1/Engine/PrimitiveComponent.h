#pragma once

#include "ComponentBase.h"

struct InstanceList;

class PrimitiveComponent : public ComponentBase
{
public:
	PrimitiveComponent();
	virtual ~PrimitiveComponent();

	void SetMeshAsset(MeshAssetRef mesh) { m_mesh = mesh; }
	void SetMaterialAsset(MaterialAssetRef material);

	void RenderInstancing(InstanceList& instanceList);

	InstanceID GetInstanceID();

private:
	MeshAssetRef m_mesh;
	MaterialAssetRef m_material;

	using Super = ComponentBase;
};

