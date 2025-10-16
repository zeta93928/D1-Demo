#include "pch.h"
#include "D3D12Renderer.h"
#include "PrimitiveRenderData.h"
#include "DescriptorPool.h"
#include "DescriptorAllocator.h"
#include "ConstantBufferManager.h"

D3D12Renderer* GRenderer = nullptr;

D3D12Renderer::D3D12Renderer()
{
    GRenderer = this;
}

D3D12Renderer::~D3D12Renderer()
{
    CleanUp();
}

bool __stdcall D3D12Renderer::Init(HWND hwnd, bool enableDebugLayer, bool enalbeGBV)
{
	BOOL	bResult = FALSE;

	HRESULT hr = S_OK;
	ID3D12Debug* pDebugController = nullptr;
	IDXGIFactory4* pFactory = nullptr;
	IDXGIAdapter1* pAdapter = nullptr;
	DXGI_ADAPTER_DESC1 AdapterDesc = {};

	DWORD dwCreateFlags = 0;
	DWORD dwCreateFactoryFlags = 0;

	// if use debug Layer...
	if (enableDebugLayer)
	{
		// Enable the D3D12 debug layer.
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController))))
		{
			pDebugController->EnableDebugLayer();
		}
		dwCreateFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
		if (enalbeGBV)
		{
			ID3D12Debug5* pDebugController5 = nullptr;
			if (S_OK == pDebugController->QueryInterface(IID_PPV_ARGS(&pDebugController5)))
			{
				pDebugController5->SetEnableGPUBasedValidation(TRUE);
				pDebugController5->SetEnableAutoName(TRUE);
				pDebugController5->Release();
			}
		}
	}

	// Create DXGIFactory
	CreateDXGIFactory2(dwCreateFactoryFlags, IID_PPV_ARGS(&pFactory));

	D3D_FEATURE_LEVEL	featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	DWORD	FeatureLevelNum = _countof(featureLevels);

	for (DWORD featerLevelIndex = 0; featerLevelIndex < FeatureLevelNum; featerLevelIndex++)
	{
		UINT adapterIndex = 0;
		while (DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &pAdapter))
		{
			pAdapter->GetDesc1(&AdapterDesc);

			if (SUCCEEDED(D3D12CreateDevice(pAdapter, featureLevels[featerLevelIndex], IID_PPV_ARGS(&m_device))))
			{
				goto lb_exit;

			}
			pAdapter->Release();
			pAdapter = nullptr;
			adapterIndex++;
		}
	}
lb_exit:

	if (!m_device)
	{
		__debugbreak();
		goto lb_return;
	}

	m_AdapterDesc = AdapterDesc;
	m_hwnd = hwnd;

	if (pDebugController)
	{
		D3DUtils::SetDebugLayerInfo(m_device);
	}

	// Describe and create the command queue.
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		hr = m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_pCommandQueue));
		if (FAILED(hr))
		{
			__debugbreak();
			goto lb_return;
		}
	}

	CreateDescriptorHeap();

	RECT	rect;
	::GetClientRect(hwnd, &rect);
	DWORD	dwWndWidth = rect.right - rect.left;
	DWORD	dwWndHeight = rect.bottom - rect.top;
	UINT	dwBackBufferWidth = rect.right - rect.left;
	UINT	dwBackBufferHeight = rect.bottom - rect.top;

	// Describe and create the swap chain.
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = dwBackBufferWidth;
		swapChainDesc.Height = dwBackBufferHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//swapChainDesc.BufferDesc.RefreshRate.Numerator = m_uiRefreshRate;
		//swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = SWAP_CHAIN_FRAME_COUNT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		swapChainDesc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
		m_dwSwapChainFlags = swapChainDesc.Flags;


		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		IDXGISwapChain1* pSwapChain1 = nullptr;
		if (FAILED(pFactory->CreateSwapChainForHwnd(m_pCommandQueue, hwnd, &swapChainDesc, &fsSwapChainDesc, nullptr, &pSwapChain1)))
		{
			__debugbreak();
		}
		pSwapChain1->QueryInterface(IID_PPV_ARGS(&m_swapChain));
		pSwapChain1->Release();
		pSwapChain1 = nullptr;
		m_renderTargetIndex = m_swapChain->GetCurrentBackBufferIndex();
	}

	m_viewPort.Width = (float)dwWndWidth;
	m_viewPort.Height = (float)dwWndHeight;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	m_scissorRect.left = 0;
	m_scissorRect.top = 0;
	m_scissorRect.right = dwWndWidth;
	m_scissorRect.bottom = dwWndHeight;

	m_backBufferWidth = dwWndWidth;
	m_backBufferHeight = dwWndHeight;

	// Create frame resources.
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

	// Create a RTV for each frame.
	// Descriptor Table
	// |        0        |        1	       |
	// | Render Target 0 | Render Target 1 |
	for (UINT n = 0; n < SWAP_CHAIN_FRAME_COUNT; n++)
	{
		m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n]));
		m_device->CreateRenderTargetView(m_renderTargets[n], nullptr, rtvHandle);
		rtvHandle.Offset(1, m_rtvDescriptorSize);
	}

	CreateDepthStencil(m_backBufferWidth, m_backBufferHeight);

	// SRV Descriptor Size ���
	m_srvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	CreateCommandList();

	// Create synchronization objects.
	CreateFence();

	// Resource Manager ����
	{
		m_resourceManager = new D3D12ResourceManager;
		m_resourceManager->Init();
	}
	
	// Descriptor Pool ����
	{
		// SkeletalMeshRenderData ���� �� �߰� �۾� �ʿ�
		// @TODO:
		uint32 maxDescriptorNum = MAX_GLOBAL_CONSTANT_BUFFER_COUNT + MAX_DRAW_COUNT_PER_FRAME * PrimitiveRenderData::DESCRIPTOR_COUNT_FOR_DRAW;
		
		m_descriptorPool = new DescriptorPool;
		m_descriptorPool->Create(maxDescriptorNum);
	} 

	// Descriptor Allocator ����
	{
		m_descriptorAllocator = new DescriptorAllocator;
		m_descriptorAllocator->Create(MAX_DESCRIPTOR_COUNT);
	}

	// Constant Buffer Pool ����
	{
		m_constantBufferManager = new ConstantBufferManager;
		m_constantBufferManager->CreatePool(MAX_DRAW_COUNT_PER_FRAME * PrimitiveRenderData::DESCRIPTOR_CB_COUNT);
	}
	
	bResult = TRUE;
lb_return:
	if (pDebugController)
	{
		pDebugController->Release();
		pDebugController = nullptr;
	}
	if (pAdapter)
	{
		pAdapter->Release();
		pAdapter = nullptr;
	}
	if (pFactory)
	{
		pFactory->Release();
		pFactory = nullptr;
	}

	return bResult;
}

void __stdcall D3D12Renderer::Release()
{
	delete this;
}

void __stdcall D3D12Renderer::BeginRender()
{
	if (FAILED(m_cmdAllocator->Reset()))
	{
		__debugbreak();
	}

	if (FAILED(m_cmdList->Reset(m_cmdAllocator, nullptr)))
	{
		__debugbreak();
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_renderTargetIndex, m_rtvDescriptorSize);
	m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_renderTargetIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
	
	const float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	m_cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	m_cmdList->RSSetViewports(1, &m_viewPort);
	m_cmdList->RSSetScissorRects(1, &m_scissorRect);
	m_cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	UpdateGlobalData();
}

void __stdcall D3D12Renderer::EndRender()
{
	m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_renderTargetIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	m_cmdList->Close();

	// cmdList �� ����� command �� GPU�� ����
	ID3D12CommandList* ppCommandLists[] = { m_cmdList };
	m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

void __stdcall D3D12Renderer::Present()
{
	//	uint32 syncInterval = 1;	// VSync On
	uint32 syncInterval = 0;	// VSync Off

	uint32 dirtyValue = syncInterval;
	uint32 presentFlags = 0;

	if (!dirtyValue)
	{
		presentFlags = DXGI_PRESENT_ALLOW_TEARING;
	}

	HRESULT hr = m_swapChain->Present(syncInterval, presentFlags);

	if (DXGI_ERROR_DEVICE_REMOVED == hr)
	{
		__debugbreak();
	}

	// ���� ������ �ε����� ��ü
	m_renderTargetIndex = m_swapChain->GetCurrentBackBufferIndex();

	Fence();

	WaitForFenceValue();

	// Constant Buffer ���� Descriptor Heap �ʱ�ȭ
	// �� ������ ����Ǳ� ����
	m_constantBufferManager->ResetPool();
	m_descriptorPool->Reset();
}

bool __stdcall D3D12Renderer::UpdateWindowSize(uint32 width, uint32 height)
{
	if (!(width * height))
	{
		return false;
	}

	if (m_backBufferWidth == width && m_backBufferHeight == height)
	{
		return false;
	}

	DXGI_SWAP_CHAIN_DESC1	desc;
	HRESULT	hr = m_swapChain->GetDesc1(&desc);
	if (FAILED(hr))
		__debugbreak();

	for (uint32 n = 0; n < SWAP_CHAIN_FRAME_COUNT; n++)
	{
		m_renderTargets[n]->Release();
		m_renderTargets[n] = nullptr;
	}

	CleanUpDepthStencil();

	if (FAILED(m_swapChain->ResizeBuffers(SWAP_CHAIN_FRAME_COUNT, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, m_dwSwapChainFlags)))
	{
		__debugbreak();
	}

	m_renderTargetIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Create frame resources
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

	// Create a RTV for each frame
	for (uint32 n = 0; n < SWAP_CHAIN_FRAME_COUNT; n++)
	{
		m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n]));
		m_device->CreateRenderTargetView(m_renderTargets[n], nullptr, rtvHandle);
		rtvHandle.Offset(1, m_rtvDescriptorSize);
	}

	CreateDepthStencil(width, height);

	m_backBufferWidth = width;
	m_backBufferHeight = height;
	m_viewPort.Width = (float)m_backBufferWidth;
	m_viewPort.Height = (float)m_backBufferHeight;
	m_scissorRect.left = 0;
	m_scissorRect.top = 0;
	m_scissorRect.right = m_backBufferWidth;
	m_scissorRect.bottom = m_backBufferHeight;

	return true;
}

IPrimitiveRenderData* __stdcall D3D12Renderer::CreateStaticMeshRenderData()
{
	PrimitiveRenderData* data = new PrimitiveRenderData;
	assert(data);
	assert(data->Init());

	return data;
}

ISkeletalMeshRenderData* __stdcall D3D12Renderer::CreateSkeletalMeshRenderData()
{
    return nullptr;
}

void __stdcall D3D12Renderer::RenderStaticMeshRenderData(IPrimitiveRenderData* renderData)
{
	if (nullptr == renderData)
	{
		return;
	}

	PrimitiveRenderData* inRenderData = (PrimitiveRenderData*)renderData;

	inRenderData->Draw(m_cmdList);
}

void __stdcall D3D12Renderer::RenderSkeletalMeshRenderData()
{
}

void __stdcall D3D12Renderer::SetGlobalRenderData(GlobalRenderData* renderData)
{
	assert(renderData);
	memcpy(&m_globalRenderData, renderData, sizeof(GlobalRenderData));
}

void* __stdcall D3D12Renderer::AccessTextureHandle(const WCHAR* name, const DirectX::ScratchImage* img)
{
	void* handle = RESOURCE_MANAGER->BindTextureData(name, img);
	assert(handle);
	return handle;
}

void __stdcall D3D12Renderer::ReleaseTextureHandle(const WCHAR* name)
{
	RESOURCE_MANAGER->ReleaseTextureData(name);
}

void D3D12Renderer::CleanUp()
{
	WaitForFenceValue();

	if (m_constantBufferManager)
	{
		delete m_constantBufferManager;
		m_constantBufferManager = nullptr;
	}

	if (m_descriptorAllocator)
	{
		delete m_descriptorAllocator;
		m_descriptorAllocator = nullptr;
	}

	if (m_descriptorPool)
	{
		delete m_descriptorPool;
		m_descriptorPool = nullptr;
	}

	if (m_resourceManager)
	{
		delete m_resourceManager;
		m_resourceManager = nullptr;
	}

	CleanUpDepthStencil();

	for (DWORD i = 0; i < SWAP_CHAIN_FRAME_COUNT; i++)
	{
		if (m_renderTargets[i])
		{
			m_renderTargets[i]->Release();
			m_renderTargets[i] = nullptr;
		}
	}

	CleanUpDescriptorHeap();

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}

	if (m_pCommandQueue)
	{
		m_pCommandQueue->Release();
		m_pCommandQueue = nullptr;
	}

	CleanUpCommandList();

	CleanUpFence();


	if (m_device)
	{
		ULONG ref_count = m_device->Release();
		if (ref_count)
		{
			//resource leak!!!
			IDXGIDebug1* pDebug = nullptr;
			if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
			{
				pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
				pDebug->Release();
			}
			__debugbreak();
		}

		m_device = nullptr;
	}
}

void D3D12Renderer::UpdateGlobalData()
{
	ID3D12DescriptorHeap* heap = DESC_POOL->GetDecriptorHeap();

	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = {};
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};

	if (!DESC_POOL->AllocDescriptorTable(cpuHandle, gpuHandle, MAX_GLOBAL_CONSTANT_BUFFER_COUNT))
	{
		__debugbreak();
	}

	ContantBufferEntry* cbEntry = nullptr;
	{
		ConstantBufferPool* global_CB_Pool = CONST_MANAGER->GetConstantBuffer(ConstantBufferType::Global);
		{
			cbEntry = global_CB_Pool->AllocEntry();
			assert(cbEntry);
			// Constant Buffer �� ������ Write �Ѵ�.
			// Matrix �� Shader �� Matrix ��Ģ�� ���� col major -> row major �� �����Ѵ�.
			// Transpose() ���
			GlobalRenderData* globalCB = (GlobalRenderData*)cbEntry->sysMem;
			globalCB->view = VIEW_MATRIX.Transpose();
			globalCB->proj = PROJ_MATRIX.Transpose();

			// Constant Buffer �� Descriptor �� Shader visible �� Descriptor Heap ���� Copy
			// Root Signature ���� ������ Descriptor Table �� ������ �����ؾ� �Ѵ�.
			CD3DX12_CPU_DESCRIPTOR_HANDLE cbvDest(cpuHandle, 0, SRV_DESC_SIZE);
			DEVICE->CopyDescriptorsSimple(1, cbvDest, cbEntry->cpuHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}
	}

	m_globalCB_GPU = gpuHandle;
}

bool D3D12Renderer::CreateDepthStencil(uint32 width, uint32 height)
{
	{
		// Depth Stencil Resource ����
		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
		depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
		depthOptimizedClearValue.DepthStencil.Stencil = 0;

		CD3DX12_RESOURCE_DESC depthDesc(
			D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			0,
			width,
			height,
			1,
			1,
			DXGI_FORMAT_R32_TYPELESS,
			1,
			0,
			D3D12_TEXTURE_LAYOUT_UNKNOWN,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

		if (FAILED(m_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&depthDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthOptimizedClearValue,
			IID_PPV_ARGS(&m_depthStencil)
		)))
		{
			__debugbreak();
		}

		m_depthStencil->SetName(L"D3D12Renderer::m_depthStencil");

		// ���ҽ� ���� ���ε�
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
		m_device->CreateDepthStencilView(m_depthStencil, &depthStencilDesc, dsvHandle);
	}

	return true;
}

void D3D12Renderer::CleanUpDepthStencil()
{
	if (m_depthStencil)
	{
		m_depthStencil->Release();
		m_depthStencil = nullptr;
	}
}

void D3D12Renderer::CreateFence()
{
	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence))))
	{
		__debugbreak();
	}

	m_ui64FenceValue = 0;

	// Create an event handle to use for frame synchronization.
	m_hFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void D3D12Renderer::CleanUpFence()
{
	if (m_hFenceEvent)
	{
		CloseHandle(m_hFenceEvent);
		m_hFenceEvent = nullptr;
	}
	if (m_pFence)
	{
		m_pFence->Release();
		m_pFence = nullptr;
	}
}

void D3D12Renderer::CreateCommandList()
{
	if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator))))
	{
		__debugbreak();
	}

	// Create the command list.
	if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator, nullptr, IID_PPV_ARGS(&m_cmdList))))
	{
		__debugbreak();
	}

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	m_cmdList->Close();
}

void D3D12Renderer::CleanUpCommandList()
{
	if (m_cmdList)
	{
		m_cmdList->Release();
		m_cmdList = nullptr;
	}
	if (m_cmdAllocator)
	{
		m_cmdAllocator->Release();
		m_cmdAllocator = nullptr;
	}
}

bool D3D12Renderer::CreateDescriptorHeap()
{
	// Render Target �� Descriptor Heap ����
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = SWAP_CHAIN_FRAME_COUNT;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap))))
		{
			__debugbreak();
		}

		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// Depth Stencil �� Descriptor Heap ����
	{
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
		dsvHeapDesc.NumDescriptors = 1;	// Default Depth Buffer
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(m_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap))))
		{
			__debugbreak();
		}

		m_dsvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}

	return true;
}

void D3D12Renderer::CleanUpDescriptorHeap()
{
	if (m_dsvHeap)
	{
		m_dsvHeap->Release();
		m_dsvHeap = nullptr;
	}

	if (m_rtvHeap)
	{
		m_rtvHeap->Release();
		m_rtvHeap = nullptr;
	}
}

UINT64 D3D12Renderer::Fence()
{
	m_ui64FenceValue++;
	m_pCommandQueue->Signal(m_pFence, m_ui64FenceValue);
	return m_ui64FenceValue;
}

void D3D12Renderer::WaitForFenceValue()
{
	const UINT64 ExpectedFenceValue = m_ui64FenceValue;

	// Wait until the previous frame is finished.
	if (m_pFence->GetCompletedValue() < ExpectedFenceValue)
	{
		m_pFence->SetEventOnCompletion(ExpectedFenceValue, m_hFenceEvent);
		WaitForSingleObject(m_hFenceEvent, INFINITE);
	}
}
