#include "pch.h"
#include "MeshAsset.h"
#include "../Utils/GeometryHelper.h"

MeshAsset::MeshAsset()
	: AssetBase(AssetType::Mesh)
{
}

MeshAsset::~MeshAsset()
{
	// ����
	m_staticMeshRenderData->Release();
}

void MeshAsset::GenerateQuad()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(m_geometry);

	// Renderer �� ���� StaticMeshRenderData �ν��Ͻ� ����
	m_staticMeshRenderData = GRenderer->CreateStaticMeshRenderData();

	// CPU �� �����͸� Renderer DLL �� �ѱ��.
	// Index Buffer 1���� Size �� uint16 ���� �����̹Ƿ� �Ķ���ͷ� �������� �ʴ´�
	m_staticMeshRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateCube()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateCube(m_geometry);

	m_staticMeshRenderData = GRenderer->CreateStaticMeshRenderData();

	m_staticMeshRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateGrid(int32 sizeX, int32 sizeZ)
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateGrid(m_geometry, sizeX, sizeZ);

	m_staticMeshRenderData = GRenderer->CreateStaticMeshRenderData();

	m_staticMeshRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}

void MeshAsset::GenerateSphere()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateSphere(m_geometry);

	m_staticMeshRenderData = GRenderer->CreateStaticMeshRenderData();

	m_staticMeshRenderData->CreateMesh(m_geometry->GetVertexData(), sizeof(VertexTextureNormalTangentData), m_geometry->GetVertexCount(), m_geometry->GetIndexData(), m_geometry->GetIndexCount());
}
