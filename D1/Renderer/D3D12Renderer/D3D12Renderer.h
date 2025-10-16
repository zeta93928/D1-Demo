#pragma once

enum : uint8 
{
	SWAP_CHAIN_FRAME_COUNT = 2 
};

class D3D12ResourceManager;
class DescriptorPool;
class DescriptorAllocator;
class ConstantBufferManager;

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

	IStaticMeshRenderData* __stdcall CreateStaticMeshRenderData() override;
	ISkeletalMeshRenderData* __stdcall CreateSkeletalMeshRenderData() override;

	virtual void __stdcall RenderStaticMeshRenderData(IStaticMeshRenderData* renderData) override;
	virtual void __stdcall RenderSkeletalMeshRenderData() override;

	virtual void __stdcall SetGlobalRenderData(GlobalRenderData* globalData) override;

public:
	ID3D12Device5* GetDevice() { return m_device; }
	D3D12ResourceManager* GetResourceManager() { return m_resourceManager; }
	DescriptorPool* GetDescriptorPool() { return m_descriptorPool; }
	const GlobalRenderData& GetGlobalRenderData() { return m_globalRenderData; }

	uint32 GetSRVDescriptorSize() { return m_srvDescriptorSize; }
	uint32 GetRTVDescriptorSize() { return m_rtvDescriptorSize; }
	uint32 GetDSVDescriptorSize() { return m_dsvDescriptorSize; }
	
	// 매니저로 관리 필요
	ConstantBufferManager* GetConstantBufferManager() { return m_constantBufferManager; }

private:
	void CleanUp();

	bool CreateDepthStencil(uint32 width, uint32 height);
	void CleanUpDepthStencil();

	void CreateFence();
	void CleanUpFence();
	void CreateCommandList();
	void CleanUpCommandList();
	bool CreateDescriptorHeap();
	void CleanUpDescriptorHeap();

	UINT64 Fence();
	void WaitForFenceValue();

private:
	// 한 프레임에 그려지는 오브젝트 수
	// 이 값에 각 오브젝트 랜더 데이터의 Descipror 갯수를 곱한다
	static const uint32 MAX_DRAW_COUNT_PER_FRAME = 256;

	// Texture 리소스를 Heap 에 바인딩 하기 위한 DescriptorAllcator 할당 크기
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
	uint32 m_srvDescriptorSize = 0;

	UINT	m_dwSwapChainFlags = 0;
	UINT	m_renderTargetIndex = 0;
	HANDLE	m_hFenceEvent = nullptr;
	ID3D12Fence* m_pFence = nullptr;

	//~Start Renderer 자원(CB, SRV 등...) Manager
	D3D12ResourceManager* m_resourceManager = nullptr;
	DescriptorPool* m_descriptorPool = nullptr;
	DescriptorAllocator* m_descriptorAllocator = nullptr;
	ConstantBufferManager* m_constantBufferManager = nullptr;
	//~End Renderer 자원(CB, SRV 등...) Manager

	GlobalRenderData m_globalRenderData = {};
};

extern D3D12Renderer* GRenderer;

