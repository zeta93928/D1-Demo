#include "pch.h"
#include "MeshAsset.h"
#include "GeometryHelper.h"

MeshAsset::MeshAsset()
	: AssetBase(AssetType::Mesh)
{
}

MeshAsset::~MeshAsset()
{
	// 주의
	m_primitiveRenderData->Release();
}

void MeshAsset::GenerateQuad()
{
	m_geometry = MakeShared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(m_geometry);

	// Renderer 로 부터 StaticMeshRenderData 인스턴스 생성
	// 주의: 생성한 인스턴스는 소멸자에서 Release() 호출
	m_primitiveRenderData = GRenderer->CreateStaticMeshRenderData();

	// CPU 측 데이터를 Renderer DLL 로 넘긴다.
	// Index Buffer 1개의 Size 는 uint16 으로 고정이므로 파라미터로 전달하지 않는다
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
