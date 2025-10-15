#include "pch.h"
#include "ConstantBufferPool.h"

ConstantBufferPool::~ConstantBufferPool()
{
	if (m_cbEntryList)
	{
		delete[] m_cbEntryList;
		m_cbEntryList = nullptr;
	}
	if (m_resource)
	{
		m_resource->Release();
		m_resource = nullptr;
	}
	if (m_heap)
	{
		m_heap->Release();
		m_heap = nullptr;
	}
}

bool ConstantBufferPool::Create(uint32 typeSize, uint32 maxNum)
{
	m_typeSize = typeSize;
	m_maxNum = maxNum;

	uint32 byteWidth = typeSize * maxNum;

	// Constant Buffer Resource 생성
	{
		if (FAILED(DEVICE->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(byteWidth),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_resource))))
		{
			__debugbreak();
		}
	}
	
	// Constant Buffer Resource Mapping 을 위한 heap 생성
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.NumDescriptors = maxNum;
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_heap))))
		{
			__debugbreak();
		}

		// CPU 에 쓰지 않는 설정을 위한 변수
		CD3DX12_RANGE readRange(0, 0);
		m_resource->Map(0, &readRange, reinterpret_cast<void**>(&m_sysMem));
	}

	// Constant Buffer Entry 생성
	// 해당 자료구조를 통해 Draw 시 DescriptorPool 에 Copy 진행
	m_cbEntryList = new ContantBufferEntry[m_maxNum];

	// Resource 와 Heap Mapping
	{
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_resource->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = m_typeSize;

		BYTE* sysMem = m_sysMem;
		
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(m_heap->GetCPUDescriptorHandleForHeapStart());

		uint32 descriptorSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		for (uint32 i = 0; i < m_maxNum; i++)
		{
			DEVICE->CreateConstantBufferView(&cbvDesc, cpuHandle);

			// Heap cpu handle 값 보관
			m_cbEntryList[i].cpuHandle = cpuHandle;

			// GPU 측 가상 메모리 보관
			m_cbEntryList[i].gpuAddress = cbvDesc.BufferLocation;
		
			// System 메모리 값 저장: Constant Buffer Data 를 저장할때 사용
			m_cbEntryList[i].sysMem = sysMem;

			// +Offset
			cpuHandle.Offset(1, descriptorSize);
			cbvDesc.BufferLocation += m_typeSize;
			sysMem += m_typeSize;
		}
	}

	return true;
}

ContantBufferEntry* ConstantBufferPool::AllocEntry()
{
	ContantBufferEntry* cbEntry = nullptr;
	
	if (m_useNum >= m_maxNum)
	{
		return cbEntry;
	}

	// &m_constantBufferList[m_useNum] 과 동일
	cbEntry = m_cbEntryList + m_useNum;
	m_useNum++;

	return cbEntry;
}

void ConstantBufferPool::Reset()
{
	m_useNum = 0;
}
