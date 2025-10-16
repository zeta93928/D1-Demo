#include "pch.h"
#include "D3D12ResourceManager.h"

D3D12ResourceManager::D3D12ResourceManager()
{
}

D3D12ResourceManager::~D3D12ResourceManager()
{
	CleanUp();
}

bool D3D12ResourceManager::Init()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	if (FAILED(DEVICE->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_cmdQueue))))
	{
		__debugbreak();	
	}

	CreateCommandList();
	CreateFence();

	return true;
}

HRESULT D3D12ResourceManager::CreateVertexBuffer(UINT SizePerVertex, DWORD dwVertexNum, D3D12_VERTEX_BUFFER_VIEW* pOutVertexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData)
{
	HRESULT hr = S_OK;

	D3D12_VERTEX_BUFFER_VIEW	VertexBufferView = {};
	ID3D12Resource* pVertexBuffer = nullptr;
	ID3D12Resource* pUploadBuffer = nullptr;
	UINT		VertexBufferSize = SizePerVertex * dwVertexNum;

	// create vertexbuffer for rendering
	hr = DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(VertexBufferSize),
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&pVertexBuffer));

	if (FAILED(hr))
	{
		__debugbreak();
		goto lb_return;
	}
	if (pInitData)
	{
		if (FAILED(m_cmdAllocator->Reset()))
			__debugbreak();

		if (FAILED(m_cmdList->Reset(m_cmdAllocator, nullptr)))
			__debugbreak();

		hr = DEVICE->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(VertexBufferSize),
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&pUploadBuffer));

		if (FAILED(hr))
		{
			__debugbreak();
			goto lb_return;
		}

		// Copy the triangle data to the vertex buffer.
		UINT8* pVertexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.

		hr = pUploadBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
		if (FAILED(hr))
		{
			__debugbreak();
			goto lb_return;
		}
		memcpy(pVertexDataBegin, pInitData, VertexBufferSize);
		pUploadBuffer->Unmap(0, nullptr);

		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pVertexBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
		m_cmdList->CopyBufferRegion(pVertexBuffer, 0, pUploadBuffer, 0, VertexBufferSize);
		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pVertexBuffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

		m_cmdList->Close();

		ID3D12CommandList* ppCommandLists[] = { m_cmdList };
		m_cmdQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		Fence();
		WaitForFenceValue();
	}


	// Initialize the vertex buffer view.
	VertexBufferView.BufferLocation = pVertexBuffer->GetGPUVirtualAddress();
	VertexBufferView.StrideInBytes = SizePerVertex;
	VertexBufferView.SizeInBytes = VertexBufferSize;

	*pOutVertexBufferView = VertexBufferView;
	*ppOutBuffer = pVertexBuffer;

lb_return:
	if (pUploadBuffer)
	{
		pUploadBuffer->Release();
		pUploadBuffer = nullptr;
	}
	return hr;
}

HRESULT D3D12ResourceManager::CreateIndexBuffer(DWORD dwIndexNum, D3D12_INDEX_BUFFER_VIEW* pOutIndexBufferView, ID3D12Resource** ppOutBuffer, void* pInitData)
{
	HRESULT hr = S_OK;

	D3D12_INDEX_BUFFER_VIEW	IndexBufferView = {};
	ID3D12Resource* pIndexBuffer = nullptr;
	ID3D12Resource* pUploadBuffer = nullptr;
	UINT		IndexBufferSize = sizeof(uint32) * dwIndexNum;

	// create vertexbuffer for rendering
	hr = DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(IndexBufferSize),
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&pIndexBuffer));

	if (FAILED(hr))
	{
		__debugbreak();
		goto lb_return;
	}
	if (pInitData)
	{
		if (FAILED(m_cmdAllocator->Reset()))
			__debugbreak();

		if (FAILED(m_cmdList->Reset(m_cmdAllocator, nullptr)))
			__debugbreak();

		hr = DEVICE->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(IndexBufferSize),
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&pUploadBuffer));

		if (FAILED(hr))
		{
			__debugbreak();
			goto lb_return;
		}

		// Copy the triangle data to the vertex buffer.
		UINT8* pIndexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.

		hr = pUploadBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
		if (FAILED(hr))
		{
			__debugbreak();
			goto lb_return;
		}
		memcpy(pIndexDataBegin, pInitData, IndexBufferSize);
		pUploadBuffer->Unmap(0, nullptr);

		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIndexBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
		m_cmdList->CopyBufferRegion(pIndexBuffer, 0, pUploadBuffer, 0, IndexBufferSize);
		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIndexBuffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER));

		m_cmdList->Close();

		ID3D12CommandList* ppCommandLists[] = { m_cmdList };
		m_cmdQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		Fence();
		WaitForFenceValue();
	}


	// Initialize the vertex buffer view.
	IndexBufferView.BufferLocation = pIndexBuffer->GetGPUVirtualAddress();
	IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	IndexBufferView.SizeInBytes = IndexBufferSize;

	*pOutIndexBufferView = IndexBufferView;
	*ppOutBuffer = pIndexBuffer;

lb_return:
	if (pUploadBuffer)
	{
		pUploadBuffer->Release();
		pUploadBuffer = nullptr;
	}
	return hr;
}

TextureDesc* D3D12ResourceManager::BindTextureData(const WCHAR* name, const DirectX::ScratchImage* img)
{
	using namespace DirectX;

	auto iter = m_textureCache.find(name);
	if (iter != m_textureCache.end())
	{
		return iter->second;
	}

	assert(img);

	ID3D12Resource* texResource = nullptr;
	ID3D12Resource* uploadBuffer = nullptr;
	TexMetadata md = img->GetMetadata();

	// GPU 리소스로 만들기
	D3D12_RESOURCE_DESC texDesc = {};
	texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texDesc.Width = static_cast<UINT>(md.width);
	texDesc.Height = static_cast<UINT>(md.height);
	texDesc.DepthOrArraySize = static_cast<UINT16>(md.arraySize);
	texDesc.MipLevels = static_cast<UINT16>(md.mipLevels);
	texDesc.Format = md.format;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	texDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
	if (FAILED(DEVICE->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&texDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&texResource))))
	{
		__debugbreak();
	}

	// GPU 로 업로드
	const Image* image = img->GetImage(0, 0, 0);
	uint64 uploadBufferSize = GetRequiredIntermediateSize(texResource, 0, 1);

	CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC uploadBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
	if (FAILED(DEVICE->CreateCommittedResource(
		&uploadHeapProps,
		D3D12_HEAP_FLAG_NONE,
		&uploadBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadBuffer))))
	{
		__debugbreak();
	}

	D3D12_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pData = image->pixels;
	subresourceData.RowPitch = image->rowPitch;
	subresourceData.SlicePitch = image->slicePitch;

	if (FAILED(m_cmdAllocator->Reset()))
		__debugbreak();

	if (FAILED(m_cmdList->Reset(m_cmdAllocator, nullptr)))
		__debugbreak();

	UpdateSubresources(m_cmdList, texResource, uploadBuffer, 0, 0, 1, &subresourceData);
	m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE));

	m_cmdList->Close();

	ID3D12CommandList* ppCommandLists[] = { m_cmdList };
	m_cmdQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	Fence();
	WaitForFenceValue();

	if (uploadBuffer)
	{
		uploadBuffer->Release();
		uploadBuffer = nullptr;
	}

	// SRV 생성: Descriptor Allocator 에서 Descripor Heap 바인딩 핸들 접근
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = {};
	if (DESC_ALLOCATOR->AllocDescriptorHandle(srvHandle))
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = md.format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = static_cast<UINT>(md.mipLevels);

		DEVICE->CreateShaderResourceView(texResource, &srvDesc, srvHandle);

		TextureDesc* td = new TextureDesc;
		ZeroMemory(td, sizeof(TextureDesc));
		td->texResource = texResource;
		td->srvHanlde = srvHandle;
		td->fromFile = true;

		// Cache
		m_textureCache[name] = td;

		return m_textureCache[name];
	}

	return nullptr;
}

void D3D12ResourceManager::ReleaseTextureData(const WCHAR* name)
{
	auto iter = m_textureCache.find(name);
	assert(iter != m_textureCache.end());

	if (iter->second->texResource)
	{
		iter->second->texResource->Release();
		iter->second->texResource = nullptr;
	}

	if (iter->second->uploadBuffer)
	{
		iter->second->uploadBuffer->Release();
		iter->second->uploadBuffer = nullptr;
	}

	m_textureCache.erase(name);
}

void D3D12ResourceManager::CreateFence()
{
	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	if (FAILED(DEVICE->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
	{
		__debugbreak();
	}

	m_fenceValue = 0;

	// Create an event handle to use for frame synchronization.
	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void D3D12ResourceManager::CleanupFence()
{
	if (m_fenceEvent)
	{
		CloseHandle(m_fenceEvent);
		m_fenceEvent = nullptr;
	}
	if (m_fence)
	{
		m_fence->Release();
		m_fence = nullptr;
	}
}

void D3D12ResourceManager::CreateCommandList()
{
	if (FAILED(DEVICE->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator))))
	{
		__debugbreak();
	}

	// Create the command list.
	if (FAILED(DEVICE->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator, nullptr, IID_PPV_ARGS(&m_cmdList))))
	{
		__debugbreak();
	}

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	m_cmdList->Close();
}

void D3D12ResourceManager::CleanupCommandList()
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

UINT64 D3D12ResourceManager::Fence()
{
	m_fenceValue++;
	m_cmdQueue->Signal(m_fence, m_fenceValue);
	return m_fenceValue;
}

void D3D12ResourceManager::WaitForFenceValue()
{
	const UINT64 ExpectedFenceValue = m_fenceValue;

	// Wait until the previous frame is finished.
	if (m_fence->GetCompletedValue() < ExpectedFenceValue)
	{
		m_fence->SetEventOnCompletion(ExpectedFenceValue, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}
}

void D3D12ResourceManager::CleanUp()
{
	WaitForFenceValue();

	assert(Check());

	if (m_cmdQueue)
	{
		m_cmdQueue->Release();
		m_cmdQueue = nullptr;
	}

	CleanupCommandList();

	CleanupFence();
}

bool D3D12ResourceManager::Check()
{
	return m_textureCache.empty();
}
