#pragma once

enum 
{
	B1,
	T0,
};

class PrimitiveRenderData : public IPrimitiveRenderData
{
public:
	PrimitiveRenderData();
	~PrimitiveRenderData();

	/* Start IStaicMeshRenderData interface */
	virtual void __stdcall CreateMesh(void* vertices, uint32 typeSize, uint32 vertexNum, void* indices, uint32 indexNum) override;
	virtual void __stdcall Release() override;
	virtual void __stdcall SetTransformData(TransformRenderData* transformData) override;
	virtual void __stdcall SetMaterialData(MaterialRenderData* materialData) override;
	/* End IStaicMeshRenderData interface*/

	bool Init();
	void Draw(ID3D12GraphicsCommandList* pCommandList);

private:
	void CleanUp();

public:
	// [CB(b0): Global | CB(b1) | SRV(t0)]
	static const uint32 DESCRIPTOR_CB_COUNT = 1;
	static const uint32 DESCRIPTOR_SRV_COUNT = 1;
	static const uint32 DESCRIPTOR_COUNT_FOR_DRAW = DESCRIPTOR_CB_COUNT + DESCRIPTOR_SRV_COUNT;

private:
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

	// Transform Data
	TransformRenderData m_transformData = {};

	// Material Data
	MaterialRenderData m_materialData = {};
};

