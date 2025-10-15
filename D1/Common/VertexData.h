#pragma once

struct VertexData
{
	Vector3 pos = {};
};

struct VertexTextureData
{
	Vector3 pos = {};
	Vector2 uv = {};
};

struct VertexColorData
{
	Vector3 pos = {};
	Vector4 color = {};
};

struct VertexTextureNormalData
{
	Vector3 pos = {};
	Vector2 uv = {};
	Vector3 normal = {};
};

struct VertexTextureNormalTangentData
{
	Vector3 pos = {};
	Vector2 uv = {};
	Vector3 normal = {};
	Vector3 tangent = {};
};

struct VertexTextureNormalTangentBlendData
{
	Vector3 pos = {};
	Vector2 uv = {};
	Vector3 normal = {};
	Vector3 tangent = {};
	Vector4 blendIndices = {};
	Vector4 blendWeights = {};
};