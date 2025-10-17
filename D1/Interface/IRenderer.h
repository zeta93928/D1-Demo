#pragma once

#include "../Renderer/D3D12Renderer/RendererStruct.h"

struct IPrimitiveRenderData
{
	virtual void  CreateMesh(void* vertices, uint32 vertexTypeSize, uint32 vertexNum, /* Vertex */
							 void* indices, uint32 indexNum, /* Index */
							 uint32 instanceTypeSize = 0) = 0;
	virtual void  Release() = 0;
	virtual void  SetTransformData(TransformRenderData* transformData) = 0;
	virtual void  SetMaterialData(MaterialRenderData* materialData) = 0;
};

struct IStaticMeshRenderData
{

};

struct ISkeletalMeshRenderData
{

};

struct IRenderer
{
	virtual bool 	Init(HWND hwnd, bool enableDebugLayer, bool enalbeGBV) = 0;
	virtual void 	Release() = 0;

	virtual void 	BeginRender() = 0;
	virtual void 	EndRender() = 0;
	virtual void 	Present() = 0;

	virtual bool 	UpdateWindowSize(uint32 width, uint32 height) = 0;

	virtual IPrimitiveRenderData*	 	CreateStaticMeshRenderData() = 0;
	virtual ISkeletalMeshRenderData* 	CreateSkeletalMeshRenderData() = 0;

	virtual void 	RenderPrimitiveData(IPrimitiveRenderData* renderData, void* instanceData, uint32 instanceCount) = 0;
	virtual void 	RenderSkeletalMeshData() = 0;

	virtual void 	SetGlobalRenderData(GlobalRenderData* globalData) = 0;
	
	virtual void* 	AccessTextureHandle(const WCHAR* name, const DirectX::ScratchImage* img) = 0;
	virtual void    ReleaseTextureHandle(const WCHAR* name) = 0;
};