#pragma once

enum : uint8 
{
	SWAP_CHAIN_FRAME_COUNT = 2 
};

class D3D12ResourceManager;
class DescriptorPool;
class DescriptorAllocator;
class ConstantBufferPool;

class D3D12Renderer : public IRenderer
{
public:
	D3D12Renderer();
	~D3D12Renderer();

	virtual bool __stdcall Init(HWND hwnd, bool enableDebugLayer, bool enalbeGBV) override;
	virtual void __stdcall Release() override;
	
	virtual void __stdcall BeginRender() override;
	virtual void __stdcall EndRender() override;
	virtual void __stdcall Present() override;

	virtual bool __stdcall UpdateWindowSize(uint32 width, uint32 height) override;

	IStaicMeshRenderData* __stdcall CreateStaticMeshRenderData() override;
	ISkeletalMeshRenderData* __stdcall CreateSkeletalMeshRenderData() override;

	virtual void __stdcall RenderStaticMeshRenderData(IStaicMeshRenderData* renderData) override;
	virtual void __stdcall RenderSkeletalMeshRenderData() override;

	virtual void __stdcall SetGlobalRenderData(GlobalRenderData* renderData) override;

public:
	ID3D12Device5* GetDevice() { return m_device; }
	D3D12ResourceManager* GetResourceManager() { return m_resourceManager; }
	const GlobalRenderData& GetGlobalRenderData() { return m_globalRenderData; }

private:
	void CleanUp();

	bool CreateDepthStencil(uint32 width, uint32 height);

	void CreateFence();
	void CleanupFence();
	void CreateCommandList();
	void CleanupCommandList();
	bool CreateDescriptorHeap();
	void CleanupDescriptorHeap();

	UINT64 Fence();
	void WaitForFenceValue();

private:
	// �� �����ӿ� �׷����� ������Ʈ ��
	// �� ���� �� ������Ʈ ���� �������� Descipror ������ ���Ѵ�
	static const uint32 MAX_DRAW_COUNT_PER_FRAME = 256;

	// Texture ���ҽ��� Heap �� ���ε� �ϱ� ���� DescriptorAllcator �Ҵ� ũ��
	static const uint32 MAX_DESCRIPTOR_COUNT = 4096;

	HWND m_hwnd = nullptr;
	ID3D12Device5* m_device = nullptr;
	ID3D12CommandQueue* m_pCommandQueue = nullptr;
	ID3D12CommandAllocator* m_cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* m_cmdList = nullptr;
	UINT64	m_ui64FenceValue = 0;

	D3D_FEATURE_LEVEL	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_ADAPTER_DESC1	m_AdapterDesc = {};
	IDXGISwapChain3* m_swapChain = nullptr;
	D3D12_VIEWPORT	m_viewPort = {};
	D3D12_RECT		m_scissorRect = {};
	uint32 m_backBufferWidth = 0;
	uint32 m_backBufferHeight = 0;

	ID3D12Resource* m_renderTargets[SWAP_CHAIN_FRAME_COUNT] = {};
	ID3D12Resource* m_depthStencil = nullptr;
	ID3D12DescriptorHeap* m_rtvHeap = nullptr;
	ID3D12DescriptorHeap* m_dsvHeap = nullptr;
	ID3D12DescriptorHeap* m_pSRVHeap = nullptr;
	uint32 m_rtvDescriptorSize = 0;
	uint32 m_dsvDescriptorSize = 0;
	UINT	m_dwSwapChainFlags = 0;
	UINT	m_renderTargetIndex = 0;
	HANDLE	m_hFenceEvent = nullptr;
	ID3D12Fence* m_pFence = nullptr;

	//~Start Renderer �ڿ�(CB, SRV ��...) Manager
	D3D12ResourceManager* m_resourceManager = nullptr;
	DescriptorPool* m_descriptorPool = nullptr;
	DescriptorAllocator* m_descriptorAllocator = nullptr;
	ConstantBufferPool* m_constantBufferPool = nullptr;
	//~End Renderer �ڿ�(CB, SRV ��...) Manager

	GlobalRenderData m_globalRenderData = {};
};

extern D3D12Renderer* GRenderer;

