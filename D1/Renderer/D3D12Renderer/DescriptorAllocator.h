#pragma once

/*
*	������ RenderData �� Descriptor �� �ɰ��� �����ϴ°��� ��ȿ�����̴�.
*	Chunk ������ Ȯ���ϰ� �ش� Ŭ������ ���� �Ҵ�� ������ �Ѵ�.
*	Texture Asset �� ������� ����.
*	Constant Data �� ��� ConstantBufferPool �� ����.
*/

class DescriptorAllocator
{
public:
	~DescriptorAllocator();

	bool Create(uint32 maxNum, D3D12_DESCRIPTOR_HEAP_FLAGS flag = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	
	// Deciptor Chunk ���� �ڵ��� �Ҵ��ϴ� �Լ�
	bool AllocDescriptorHandle(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle);

	// Deciptor Chunk �� �ڵ��� ��ȯ�ϴ� �Լ�
	void FreeDescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle);

	// Validate Handle
	bool CheckHandle(const D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle);

private:
	bool CheckFree();

private:
	ID3D12DescriptorHeap* m_heap = nullptr;
	uint32 m_desciptorSize = 0;
	std::queue<uint32> m_idGenerator = {};
	uint32 m_id = 0;
};

