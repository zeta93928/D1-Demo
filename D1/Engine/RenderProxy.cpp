#include "pch.h"
#include "RenderProxy.h"

void RenderProxy::EnqueueGlobalData(const GlobalRenderData& data)
{
	GlobalRenderData rd = {};
	memcpy(&rd, &data, sizeof(GlobalRenderData));
	GRenderer->SetGlobalRenderData(&rd);
}

void RenderProxy::EnqueueTransformData(IPrimitiveRenderData* mesh, const TransformRenderData& data)
{
	TransformRenderData rd = {};
	memcpy(&rd, &data, sizeof(TransformRenderData));
	mesh->SetTransformData(&rd);
}

void RenderProxy::EnqueueMaterialData(IPrimitiveRenderData* mesh, const MaterialRenderData& data)
{
	MaterialRenderData rd = {};
	memcpy(&rd, &data, sizeof(MaterialRenderData));
	mesh->SetMaterialData(&rd);
}
