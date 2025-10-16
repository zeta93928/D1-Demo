#pragma once

enum class ConstantBufferType : uint8
{
	Global,
	Transform,
	End,
};

enum
{
	MAX_CONSTANT_BUFFER_COUNT = (uint8)ConstantBufferType::End
};

class ConstantBufferPool;

class ConstantBufferManager
{
	// Table Entry
	struct TypeSizeEntry
	{
		ConstantBufferType type;
		uint32 size;
	};
	// Size Table
	TypeSizeEntry TypeSizeTable[MAX_CONSTANT_BUFFER_COUNT] =
	{
		{ConstantBufferType::Global, sizeof(GlobalRenderData)},
		{ConstantBufferType::Transform, sizeof(TransformRenderData)},
	};

public:
	~ConstantBufferManager();
	bool CreatePool(uint32 drawNum);
	void ResetPool();

	ConstantBufferPool* GetConstantBuffer(ConstantBufferType type);

private:
	ConstantBufferPool* m_constantBufferPools[MAX_CONSTANT_BUFFER_COUNT] = {};
};

