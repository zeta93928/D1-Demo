#pragma once

#include "ComponentBase.h"

class StaticMeshComponent : public ComponentBase
{
public:
	StaticMeshComponent();
	virtual ~StaticMeshComponent();

	virtual void Update() override;

	void SetMeshAsset(MeshAssetRef mesh) { m_mesh = mesh; }

private:
	MeshAssetRef m_mesh;

	using Super = ComponentBase;
};

