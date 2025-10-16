#include "pch.h"
#include "MeshAsset.h"
#include "GeometryHelper.h"

MeshAsset::MeshAsset()
	: AssetBase(AssetType::Mesh)
{
}

MeshAsset::~MeshAsset()
{
	// ����
	m_primitiveRenderData->Release();
}

void MeshAsset::GenerateQuad()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(m_geometry);

	// Renderer �� ���� StaticMeshRenderData �ν��Ͻ� ����
	// ����: ������ �ν��Ͻ��� �Ҹ��ڿ��� Release() ȣ��
	m_primitiveRenderData = GRenderer->CreateStaticMeshRenderData();

	// CPU �� �����͸� Renderer DLL �� �ѱ��.
	// Index Buffer 1���� Size �� uint16 ���� �����̹Ƿ� �Ķ���ͷ� �������� �ʴ´�
	m_primitiveRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateCube()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateCube(m_geometry);

	m_primitiveRenderData = GRenderer->CreateStaticMeshRenderData();

	m_primitiveRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateGrid(int32 sizeX, int32 sizeZ)
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateGrid(m_geometry, sizeX, sizeZ);

	m_primitiveRenderData = GRenderer->CreateStaticMeshRenderData();

	m_primitiveRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateSphere()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateSphere(m_geometry);

	m_primitiveRenderData = GRenderer->CreateStaticMeshRenderData();

	m_primitiveRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}
