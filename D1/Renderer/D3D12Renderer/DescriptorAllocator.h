#pragma once

/*
*	각각의 RenderData 가 Descriptor 를 쪼개서 생성하는것은 비효율적이다.
*	Chunk 공간을 확보하고 해당 클래스를 통해 할당과 해제를 한다.
*	Texture Asset 을 대상으로 구현.
*	Constant Data 의 경우 ConstantBufferPool 을 참조.
*/

class DescriptorAllocator
{
public:
	~DescriptorAllocator();

	bool Create(uint32 maxNum, D3D12_DESCRIPTOR_HEAP_FLAGS flag = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	
	// Deciptor Chunk 에서 핸들을 할당하는 함수
	bool AllocDescriptorHandle(OUT D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle);

	// Deciptor Chunk 에 핸들을 반환하는 함수
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

