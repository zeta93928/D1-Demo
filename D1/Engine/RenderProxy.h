#pragma once

class RenderProxy
{
	DECLARE_SINGLETON(RenderProxy);
public:
	void EnqueueGlobalData(const GlobalRenderData& data);
	void EnqueueMaterialData(IPrimitiveRenderData* mesh, const MaterialRenderData& data);
};

