#include "pch.h"
#include "ConstantBufferManager.h"
#include "ConstantBufferPool.h"

ConstantBufferManager::~ConstantBufferManager()
{
	for (uint32 i = 0; i < MAX_CONSTANT_BUFFER_COUNT; i++)
	{
		if (m_constantBufferPools[i])
		{
			delete m_constantBufferPools[i];
			m_constantBufferPools[i] = nullptr;
		}
	}
}

bool ConstantBufferManager::CreatePool(uint32 drawNum)
{
	for (uint32 i = 0; i < MAX_CONSTANT_BUFFER_COUNT; i++)
	{
		if (i == (uint32)ConstantBufferType::Global)
		{
			m_constantBufferPools[i] = new ConstantBufferPool;
			m_constantBufferPools[i]->Create((uint32)D3DUtils::AlignConstantBufferSize(TypeSizeTable[i].size), 1);

			continue;
		}

		m_constantBufferPools[i] = new ConstantBufferPool;
		m_constantBufferPools[i]->Create((uint32)D3DUtils::AlignConstantBufferSize(TypeSizeTable[i].size), drawNum);
	}

	return true;
}

void ConstantBufferManager::ResetPool()
{
	for (uint32 i = 0; i < MAX_CONSTANT_BUFFER_COUNT; i++)
	{
		m_constantBufferPools[i]->Reset();
	}
}

ConstantBufferPool* ConstantBufferManager::GetConstantBuffer(ConstantBufferType type)
{
	assert((uint32)type < MAX_CONSTANT_BUFFER_COUNT);

	return m_constantBufferPools[(uint32)type];
}
