#pragma once

/*
*	DescriptorAllocator �� ConstantBufferPool �� ���� GPU �� ������ Descitor Heap �� ����������
*	Copy �� �����ϴ� �ڷᱸ��
*/

class DescriptorPool
{
public:
	~DescriptorPool();

	bool Create(uint32 maxNum);

	bool AllocDescriptorTable(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle, OUT D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, uint32 desireCount);
	void Reset();

	ID3D12DescriptorHeap* GetDecriptorHeap() { return m_heap; }

private:
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuHandle = {};
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuHandle = {};
	ID3D12DescriptorHeap* m_heap = nullptr;
	uint32 m_maxNum = 0;
	uint32 m_descriptorSize = 0;
	uint32 m_useNum = 0;
};

