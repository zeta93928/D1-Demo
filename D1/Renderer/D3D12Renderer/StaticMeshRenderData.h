#pragma once

enum
{
	CB0,
	CB1,
	SRV0
};

class StaticMeshRenderData : public IStaticMeshRenderData
{
public:
	StaticMeshRenderData();
	~StaticMeshRenderData();

	/* Start IStaicMeshRenderData interface */
	virtual void __stdcall CreateMesh(void* vertices, uint32 typeSize, uint32 vertexNum, void* indices, uint32 indexNum) override;
	virtual void __stdcall Release() override;
	virtual void __stdcall SetTransformData(TransformRenderData* transformData) override;
	/* End IStaicMeshRenderData interface*/

	bool Init();
	void Draw(ID3D12GraphicsCommandList* pCommandList);

private:
	void CleanUp();

public:
	// [CB(b0) | CB(b1) | SRV(t0)]
	static const uint32 DESCRIPTOR_COUNT_FOR_DRAW = 1;

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
};

