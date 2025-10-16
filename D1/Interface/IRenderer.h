#pragma once

#include "../Common/Struct.h"

struct IPrimitiveRenderData
{
	virtual void __stdcall CreateMesh(/* Vertices */ void* vertices, uint32 typeSize, uint32 vertexNum, 
									  /* Indices */ void* indices, uint32 indexNum) = 0;
	virtual void __stdcall Release() = 0;
	virtual void __stdcall SetTransformData(TransformRenderData* transformData) = 0;
	virtual void __stdcall SetMaterialData(MaterialRenderData* materialData) = 0;
};

struct IStaticMeshRenderData
{

};

struct ISkeletalMeshRenderData
{

};

struct IRenderer
{
	virtual bool __stdcall	Init(HWND hwnd, bool enableDebugLayer, bool enalbeGBV) = 0;
	virtual void __stdcall	Release() = 0;

	virtual void __stdcall	BeginRender() = 0;
	virtual void __stdcall	EndRender() = 0;
	virtual void __stdcall	Present() = 0;

	virtual bool __stdcall	UpdateWindowSize(uint32 width, uint32 height) = 0;

	virtual IPrimitiveRenderData*	 __stdcall	CreateStaticMeshRenderData() = 0;
	virtual ISkeletalMeshRenderData* __stdcall	CreateSkeletalMeshRenderData() = 0;

	virtual void __stdcall	RenderStaticMeshRenderData(IPrimitiveRenderData* renderData) = 0;
	virtual void __stdcall	RenderSkeletalMeshRenderData() = 0;

	virtual void __stdcall	SetGlobalRenderData(GlobalRenderData* globalData) = 0;
	
	virtual void* __stdcall	AccessTextureHandle(const WCHAR* name, const DirectX::ScratchImage* img) = 0;
	virtual void __stdcall  ReleaseTextureHandle(const WCHAR* name) = 0;
};