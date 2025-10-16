#include "pch.h"
#include "DescriptorAllocator.h"

DescriptorAllocator::~DescriptorAllocator()
{
	assert(CheckFree());
	if (m_heap)
	{
		m_heap->Release();
		m_heap = nullptr;
	}
}

bool DescriptorAllocator::Create(uint32 maxNum, D3D12_DESCRIPTOR_HEAP_FLAGS flag)
{
	m_desciptorSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_DESCRIPTOR_HEAP_DESC commonHeapDesc = {};
	commonHeapDesc.NumDescriptors = maxNum;
	commonHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	commonHeapDesc.Flags = flag;
	if (FAILED(DEVICE->CreateDescriptorHeap(&commonHeapDesc, IID_PPV_ARGS(&m_heap))))
	{
		__debugbreak();
	}

	return true;
}

bool DescriptorAllocator::AllocDescriptorHandle(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle)
{
	if (m_idGenerator.empty())
	{
		m_idGenerator.push(m_id);
	}

	uint32 id = m_idGenerator.front();
	m_idGenerator.pop();
	if (id < 0)
	{
		return false;
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE newCpuHanlde(m_heap->GetCPUDescriptorHandleForHeapStart(), id, m_desciptorSize);
	cpuHandle = newCpuHanlde;

    return true;
}

void DescriptorAllocator::FreeDescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle)
{
	D3D12_CPU_DESCRIPTOR_HANDLE base = m_heap->GetCPUDescriptorHandleForHeapStart();
	assert(base.ptr <= cpuHandle.ptr);

	uint32 id = (uint32)(cpuHandle.ptr - base.ptr) / m_desciptorSize;
	m_idGenerator.push(id);
}

bool DescriptorAllocator::CheckHandle(const D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle)
{
	D3D12_CPU_DESCRIPTOR_HANDLE base = m_heap->GetCPUDescriptorHandleForHeapStart();
	if (base.ptr > cpuHandle.ptr)
	{
		return false;
	}
	return true;
}

bool DescriptorAllocator::CheckFree()
{
	return m_idGenerator.empty();
}
