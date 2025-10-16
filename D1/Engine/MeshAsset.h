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

	IStaticMeshRenderData* GetStaicMeshRenderData() { return m_staticMeshRenderData; }

private:
	// Renderer �� interface
	// Rendderer ���ο��� GPU ���ҽ��� �����ϴ� �ڷᱸ��
	// Release �Լ��� ����� ������ ���� => Smart ������ ��� ����
	IStaticMeshRenderData* m_staticMeshRenderData = nullptr;

	// CPU �� ���ҽ��� �����ϴ� �ڷᱸ��
	// Mesh �� 1���� ����
	SharedPtr<Geometry<VertexTextureNormalTangentData>> m_geometry;

	using Super = AssetBase;
};

