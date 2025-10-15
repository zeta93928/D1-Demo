#include "pch.h"
#include "DescriptorAllocator.h"

bool DescriptorAllocator::Create(uint32 maxNum, D3D12_DESCRIPTOR_HEAP_FLAGS flag)
{
	D3D12_DESCRIPTOR_HEAP_DESC commonHeapDesc = {};
	commonHeapDesc.NumDescriptors = maxNum;
	commonHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	commonHeapDesc.Flags = flag;

	return true;
}

bool DescriptorAllocator::AllocDescriptorHandle(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle)
{
    return true;
}

void DescriptorAllocator::FreeDescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle)
{
}
