#pragma once

#include "../Common/Types.h"
#include "../../Common/VertexData.h"

#include <vector>
#include <string>

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

struct ModelMeshDesc
{
	std::wstring meshName;
	std::vector<ModelVertexType> vertices;
	std::vector<uint32> indices;
	std::wstring materialName;
	MaterialRenderData* material;
};


