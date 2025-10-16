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
	// Renderer �� interface
	// Rendderer ���ο��� GPU ���ҽ��� �����ϴ� �ڷᱸ��
	// Release �Լ��� ����� ������ ���� => Smart ������ ��� ����
	IPrimitiveRenderData* m_primitiveRenderData = nullptr;

	// CPU �� ���ҽ��� �����ϴ� �ڷᱸ��
	// Mesh �� 1���� ����
	SharedPtr<Geometry<VertexTextureNormalTangentData>> m_geometry;

	using Super = AssetBase;
};

