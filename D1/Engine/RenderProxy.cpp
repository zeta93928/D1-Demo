#include "pch.h"
#include "RenderProxy.h"

void RenderProxy::EnqueueGlobalData(const GlobalRenderData& data)
{
	GlobalRenderData rd = {};
	memcpy(&rd, &data, sizeof(GlobalRenderData));
	GRenderer->SetGlobalRenderData(&rd);
}

void RenderProxy::EnqueueTransformData(IStaticMeshRenderData* mesh, const TransformRenderData& data)
{
	TransformRenderData rd = {};
	memcpy(&rd, &data, sizeof(TransformRenderData));
	mesh->SetTransformData(&rd);
}

void RenderProxy::EnqueueMaterialData(IStaticMeshRenderData* mesh, const MaterialRenderData& data)
{
	MaterialRenderData rd = {};
	memcpy(&rd, &data, sizeof(MaterialRenderData));
	mesh->SetMaterialData(&rd);
}
