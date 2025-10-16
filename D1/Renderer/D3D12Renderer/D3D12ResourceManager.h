#pragma once

struct TextureDesc
{
	ID3D12Resource* texResource;
	ID3D12Resource* uploadBuffer;
	bool updated;
	bool fromFile;
	uint32 refCount;

	D3D12_CPU_DESCRIPTOR_HANDLE srvHanlde;
};

class D3D12ResourceManager
{
public:
	D3D12ResourceManager();
	~D3D12ResourceManager();

	bool Init();

	// Vertex and Index
	HRESULT CreateVertexBuffer(UINT SizePerVertex, DWORD dwVertexNum, D3D12_VERTEX_BUFFER_VIEW* pOutVertexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData);
	HRESULT CreateIndexBuffer(DWORD dwIndexNum, D3D12_INDEX_BUFFER_VIEW* pOutIndexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData);
	
	// Texture
	TextureDesc* BindTextureData(const WCHAR* name, const DirectX::ScratchImage* img);
	void ReleaseTextureData(const WCHAR* name);

private:
	void CreateFence();
	void CleanupFence();
	void CreateCommandList();
	void CleanupCommandList();


	UINT64 Fence();
	void WaitForFenceValue();

	void CleanUp();

	bool Check();

private:
	ID3D12CommandQueue* m_cmdQueue = nullptr;
	ID3D12CommandAllocator* m_cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* m_cmdList = nullptr;

	HANDLE m_fenceEvent = nullptr;
	ID3D12Fence* m_fence = nullptr;
	UINT64 m_fenceValue = 0;

	std::unordered_map<std::wstring, TextureDesc*> m_textureCache;
};

