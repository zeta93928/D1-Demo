#pragma once

#include "AssetBase.h"
#include "Geometry.h"

class MeshAsset : public AssetBase
{
public:
	MeshAsset();
	virtual ~MeshAsset();

	void GenerateQuad();
	void GenerateCube();
	void GenerateGrid(int32 sizeX, int32 sizeZ);
	void GenerateSphere();

	IPrimitiveRenderData* GetPrimitiveRenderData() { return m_primitiveRenderData; }

private:
	// Renderer 측 interface
	// Rendderer 내부에서 GPU 리소스를 관리하는 자료구조
	// Release 함수를 사용해 접근을 해제 => Smart 포인터 사용 금지
	IPrimitiveRenderData* m_primitiveRenderData = nullptr;

	// CPU 측 리소스를 관리하는 자료구조
	// Mesh 가 1개인 구조
	SharedPtr<Geometry<VertexTextureNormalTangentData>> m_geometry;

	using Super = AssetBase;
};

