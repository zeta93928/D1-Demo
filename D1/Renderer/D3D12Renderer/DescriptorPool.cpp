#include "pch.h"
#include "DescriptorPool.h"

DescriptorPool::~DescriptorPool()
{
	if (m_heap)
	{
		m_heap->Release();
		m_heap = nullptr;
	}
}

bool DescriptorPool::Create(uint32 maxNum)
{
	m_maxNum = maxNum;
	m_descriptorSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	{
		D3D12_DESCRIPTOR_HEAP_DESC commonHeapDesc = {};
		commonHeapDesc.NumDescriptors = m_maxNum;
		commonHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		commonHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		if (FAILED(DEVICE->CreateDescriptorHeap(&commonHeapDesc, IID_PPV_ARGS(&m_heap))))
		{
			__debugbreak();
		}
	}

	m_cpuHandle = m_heap->GetCPUDescriptorHandleForHeapStart();
	m_gpuHandle = m_heap->GetGPUDescriptorHandleForHeapStart();

    return true;
}

bool DescriptorPool::AllocDescriptorTable(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle, OUT D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, uint32 desireCount)
{
	if (m_useNum + desireCount > m_maxNum)
	{
		return false;
	}

	cpuHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_cpuHandle, m_useNum, m_descriptorSize);
	gpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(m_gpuHandle, m_useNum, m_descriptorSize);

	m_useNum += desireCount;

    return true;
}

void DescriptorPool::Reset()
{
	m_useNum = 0;
}
