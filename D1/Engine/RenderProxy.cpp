#include "pch.h"
#include "RenderProxy.h"

void RenderProxy::EnqueueGlobalData(const GlobalRenderData& data)
{
	GlobalRenderData rd = {};
	memcpy(&rd, &data, sizeof(GlobalRenderData));
	GRenderer->SetGlobalRenderData(&rd);
}

void RenderProxy::EnqueueMaterialData(IPrimitiveRenderData* mesh, const MaterialRenderData& data)
{
	MaterialRenderData rd = {};
	memcpy(&rd, &data, sizeof(MaterialRenderData));
	mesh->SetMaterialData(&rd);
}
