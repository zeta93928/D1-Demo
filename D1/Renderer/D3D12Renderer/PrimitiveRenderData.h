#pragma once

enum 
{
	T0,
};

class PrimitiveRenderData : public IPrimitiveRenderData
{
public:
	PrimitiveRenderData();
	~PrimitiveRenderData();

	/* Start IStaicMeshRenderData interface */
	virtual void CreateMesh(void* vertices, uint32 vertexTypeSize, uint32 vertexNum, void* indices, uint32 indexNum,
						    uint32 instanceTypeSize) override;
	virtual void Release() override;
	virtual void SetTransformData(TransformRenderData* transformData) override;
	virtual void SetMaterialData(MaterialRenderData* materialData) override;
	/* End IStaicMeshRenderData interface*/

	bool Init();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	void DrawInstance(ID3D12GraphicsCommandList* cmdList, void* instanceData, uint32 instanceCount);

private:
	void CleanUp();

	void CreateInstanceBuufer(uint32 instanceCount);
	void CleanUpInstanceBuffer();

public:
	// [CB(b0): Global  | SRV(t0)]
	static const uint32 DESCRIPTOR_SRV_COUNT = 1;
	static const uint32 DESCRIPTOR_COUNT_FOR_DRAW = DESCRIPTOR_SRV_COUNT;

private:
	// @TODO:
	// 모든 매쉬 관련 랜더 데이터가 공용으로 들고 있을 수 있도록
	// StaticMesh, SkeletalMesh 에서도 쓸수 있도록 구조 변경 필요
	static ID3D12RootSignature* sm_RootSig;
	static ID3D12PipelineState* sm_PSO;
	static DWORD m_refCount;

	// Vertex Data
	ID3D12Resource* m_vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {};

	// Index Data
	ID3D12Resource* m_indexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView = {};
	uint32 m_indexCount = 0;

	// Instance Data
	ID3D12Resource* m_instanceBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW m_instanceBufferView = {};
	uint32 m_maxInstanceCount = 500;
	uint32 m_instanceTypeSize = 0;

	// Material Data
	MaterialRenderData m_materialData = {};

	// Transform Data
	// @TODO:
	// 변경 필요
	// Client 에서 다르게 전달되어야 함 여기서 공용으로 관리 X
	TransformRenderData m_transformData = {};
};

