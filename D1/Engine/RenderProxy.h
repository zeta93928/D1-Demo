#pragma once

class RenderProxy
{
	DECLARE_SINGLETON(RenderProxy);
public:
	void EnqueueGlobalData(const GlobalRenderData& data);
	void EnqueueTransformData(IStaticMeshRenderData* mesh, const TransformRenderData& data);
};

