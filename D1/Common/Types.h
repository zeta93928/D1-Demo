#pragma once

#include "SimpleMath.h"

// Type
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using Color = DirectX::SimpleMath::Vector4;
using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

using CREATE_INSTANCE_FUNC = bool(__stdcall*)(void*);

// Struct
struct TransformRenderData
{
	Matrix world;
};

struct GlobalRenderData
{
	Matrix view;
	Matrix proj;
	Matrix viewProj;
	Matrix viewInv;
};

struct MaterialRenderData
{
	void* albedo;
	void* normal;
};


