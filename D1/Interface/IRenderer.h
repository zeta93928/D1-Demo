#pragma once

#include "../Renderer/D3D12Renderer/RendererStruct.h"

struct IPrimitiveRenderData
{
	virtual void  CreateMesh(/* Vertices */ void* vertices, uint32 typeSize, uint32 vertexNum, 
							 /* Indices */ void* indices, uint32 indexNum) = 0;
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

	virtual void 	RenderStaticMeshRenderData(IPrimitiveRenderData* renderData) = 0;
	virtual void 	RenderSkeletalMeshRenderData() = 0;

	virtual void 	SetGlobalRenderData(GlobalRenderData* globalData) = 0;
	
	virtual void* 	AccessTextureHandle(const WCHAR* name, const DirectX::ScratchImage* img) = 0;
	virtual void    ReleaseTextureHandle(const WCHAR* name) = 0;
};