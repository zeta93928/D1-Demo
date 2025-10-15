#pragma once

class D3D12ResourceManager
{
public:
	D3D12ResourceManager();
	~D3D12ResourceManager();

	bool Init();
	HRESULT CreateVertexBuffer(UINT SizePerVertex, DWORD dwVertexNum, D3D12_VERTEX_BUFFER_VIEW* pOutVertexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData);
	HRESULT CreateIndexBuffer(DWORD dwIndexNum, D3D12_INDEX_BUFFER_VIEW* pOutIndexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData);

private:
	ID3D12CommandQueue* m_pCommandQueue = nullptr;
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;
	ID3D12GraphicsCommandList* m_pCommandList = nullptr;

	HANDLE	m_hFenceEvent = nullptr;
	ID3D12Fence* m_pFence = nullptr;
	UINT64	m_ui64FenceValue = 0;

	void	CreateFence();
	void	CleanupFence();
	void	CreateCommandList();
	void	CleanupCommandList();


	UINT64	Fence();
	void	WaitForFenceValue();

	void	Cleanup();
};

