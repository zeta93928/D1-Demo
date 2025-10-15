#pragma once

struct ContantBufferEntry
{
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	D3D12_GPU_VIRTUAL_ADDRESS gpuAddress;
	BYTE* sysMem;
};

class ConstantBufferPool
{
public:
	~ConstantBufferPool();
	
	bool Create(uint32 typeSize, uint32 maxNum);
	
	ContantBufferEntry* AllocEntry();
	void Reset();

private:
	ContantBufferEntry* m_cbEntryList = nullptr;
	ID3D12DescriptorHeap* m_heap = nullptr;
	ID3D12Resource* m_resource = nullptr;
	BYTE* m_sysMem = nullptr;
	uint32 m_typeSize = 0;
	uint32 m_maxNum = 0;
	uint32 m_useNum = 0;
};

