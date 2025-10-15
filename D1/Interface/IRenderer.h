#pragma once

#include "../Common/Types.h"

struct IStaicMeshRenderData
{
	virtual void __stdcall CreateMesh(/* Vertices */ void* vertices, uint32 typeSize, uint32 vertexNum, 
									  /* Indices */ void* indices, uint32 indexNum) = 0;
	virtual void __stdcall Release() = 0;
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

	virtual IStaicMeshRenderData*	 __stdcall	CreateStaticMeshRenderData() = 0;
	virtual ISkeletalMeshRenderData* __stdcall	CreateSkeletalMeshRenderData() = 0;

	virtual void __stdcall	RenderStaticMeshRenderData(IStaicMeshRenderData* renderData) = 0;
	virtual void __stdcall	RenderSkeletalMeshRenderData() = 0;

	virtual void __stdcall	SetGlobalRenderData(GlobalRenderData* renderData) = 0;
};