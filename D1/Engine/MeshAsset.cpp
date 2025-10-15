#include "pch.h"
#include "MeshAsset.h"
#include "../Utils/GeometryHelper.h"

MeshAsset::MeshAsset()
	: AssetBase(AssetType::Mesh)
{
}

MeshAsset::~MeshAsset()
{
	// 주의
	m_staticMeshRenderData->Release();
}

void MeshAsset::GenerateQuad()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(m_geometry);

	// Renderer 로 부터 StaticMeshRenderData 인스턴스 생성
	m_staticMeshRenderData = GRenderer->CreateStaticMeshRenderData();

	// CPU 측 데이터를 Renderer DLL 로 넘긴다.
	// Index Buffer 1개의 Size 는 uint16 으로 고정이므로 파라미터로 전달하지 않는다
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
