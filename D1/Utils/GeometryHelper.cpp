#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(SharedPtr<Geometry<VertexColorData>> geometry, Color color)
{
	Vector<VertexColorData> vtx;
	vtx.resize(4);

	vtx[0].pos = Vector3(-0.5f, -0.5f, 0.f);
	vtx[0].color = color;
	vtx[1].pos = Vector3(-0.5f, 0.5f, 0.f);
	vtx[1].color = color;
	vtx[2].pos = Vector3(0.5f, -0.5f, 0.f);
	vtx[2].color = color;
	vtx[3].pos = Vector3(0.5f, 0.5f, 0.f);
	vtx[3].color = color;
	geometry->SetVertices(vtx);

	Vector<uint32> idx = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateQuad(SharedPtr<Geometry<VertexTextureData>> geometry)
{
	Vector<VertexTextureData> vtx;
	vtx.resize(4);

	vtx[0].pos = Vector3(-0.5f, -0.5f, 0.f);
	vtx[0].uv = Vector2(0.f, 1.f);
	vtx[1].pos = Vector3(-0.5f, 0.5f, 0.f);
	vtx[1].uv = Vector2(0.f, 0.f);
	vtx[2].pos = Vector3(0.5f, -0.5f, 0.f);
	vtx[2].uv = Vector2(1.f, 1.f);
	vtx[3].pos = Vector3(0.5f, 0.5f, 0.f);
	vtx[3].uv = Vector2(1.f, 0.f);
	geometry->SetVertices(vtx);

	Vector<uint32> idx = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateCube(SharedPtr<Geometry<VertexTextureData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	Vector<VertexTextureData> vtx(24);

	vtx[0] = VertexTextureData{ Vector3(-w2, -h2, -d2), Vector2(0.0f, 1.0f) };
	vtx[1] = VertexTextureData{ Vector3(-w2, +h2, -d2), Vector2(0.0f, 0.0f) };
	vtx[2] = VertexTextureData{ Vector3(+w2, +h2, -d2), Vector2(1.0f, 0.0f) };
	vtx[3] = VertexTextureData{ Vector3(+w2, -h2, -d2), Vector2(1.0f, 1.0f) };
	vtx[4] = VertexTextureData{ Vector3(-w2, -h2, +d2), Vector2(1.0f, 1.0f) };
	vtx[5] = VertexTextureData{ Vector3(+w2, -h2, +d2), Vector2(0.0f, 1.0f) };
	vtx[6] = VertexTextureData{ Vector3(+w2, +h2, +d2), Vector2(0.0f, 0.0f) };
	vtx[7] = VertexTextureData{ Vector3(-w2, +h2, +d2), Vector2(1.0f, 0.0f) };
	vtx[8] = VertexTextureData{ Vector3(-w2, +h2, -d2), Vector2(0.0f, 1.0f) };
	vtx[9] = VertexTextureData{ Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f) };
	vtx[10] = VertexTextureData{ Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f) };
	vtx[11] = VertexTextureData{ Vector3(+w2, +h2, -d2), Vector2(1.0f, 1.0f) };
	vtx[12] = VertexTextureData{ Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f) };
	vtx[13] = VertexTextureData{ Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f) };
	vtx[14] = VertexTextureData{ Vector3(+w2, -h2, +d2), Vector2(0.0f, 0.0f) };
	vtx[15] = VertexTextureData{ Vector3(-w2, -h2, +d2), Vector2(1.0f, 0.0f) };
	vtx[16] = VertexTextureData{ Vector3(-w2, -h2, +d2), Vector2(0.0f, 1.0f) };
	vtx[17] = VertexTextureData{ Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f) };
	vtx[18] = VertexTextureData{ Vector3(-w2, +h2, -d2), Vector2(1.0f, 0.0f) };
	vtx[19] = VertexTextureData{ Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f) };
	vtx[20] = VertexTextureData{ Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f) };
	vtx[21] = VertexTextureData{ Vector3(+w2, +h2, -d2), Vector2(0.0f, 0.0f) };
	vtx[22] = VertexTextureData{ Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f) };
	vtx[23] = VertexTextureData{ Vector3(+w2, -h2, +d2), Vector2(1.0f, 1.0f) };

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(SharedPtr<Geometry<VertexTextureData>> geometry)
{
	using namespace DirectX;

	float radius = 0.5f; // ±¸ÀÇ ¹ÝÁö¸§
	uint32 stackCount = 20; // °¡·Î ºÐÇÒ
	uint32 sliceCount = 20; // ¼¼·Î ºÐÇÒ

	Vector<VertexTextureData> vtx;

	VertexTextureData v;

	v.pos = Vector3(0.0f, radius, 0.0f);
	v.uv = Vector2(0.5f, 0.0f);
	vtx.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.pos.x = radius * sinf(phi) * cosf(theta);
			v.pos.y = radius * cosf(phi);
			v.pos.z = radius * sinf(phi) * sinf(theta);

			v.uv = Vector2(deltaU * x, deltaV * y);

			vtx.push_back(v);
		}
	}

	v.pos = Vector3(0.0f, -radius, 0.0f);
	v.uv = Vector2(0.5f, 1.0f);
	vtx.push_back(v);

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		idx.push_back(0);
		idx.push_back(i + 2);
		idx.push_back(i + 1);
	}

	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			idx.push_back(1 + (y)*ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));

			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	uint32 bottomIndex = static_cast<uint32>(vtx.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 0; i < sliceCount; ++i)
	{
		idx.push_back(bottomIndex);
		idx.push_back(lastRingStartIndex + i);
		idx.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(SharedPtr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ)
{
	Vector<VertexTextureData> vtx;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureData v;
			v.pos = Vector3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = Vector2(static_cast<float>(x), static_cast<float>(z));

			vtx.push_back(v);
		}
	}

	geometry->SetVertices(vtx);

	Vector<uint32> idx;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z)+(x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateQuad(SharedPtr<Geometry<VertexTextureNormalData>> geometry)
{
	Vector<VertexTextureNormalData> vtx;
	vtx.resize(4);

	vtx[0].pos = Vector3(-0.5f, -0.5f, 0.f);
	vtx[0].uv = Vector2(0.f, 1.f);
	vtx[0].normal = Vector3(0.f, 0.f, -1.f);
	vtx[1].pos = Vector3(-0.5f, 0.5f, 0.f);
	vtx[1].uv = Vector2(0.f, 0.f);
	vtx[1].normal = Vector3(0.f, 0.f, -1.f);
	vtx[2].pos = Vector3(0.5f, -0.5f, 0.f);
	vtx[2].uv = Vector2(1.f, 1.f);
	vtx[2].normal = Vector3(0.f, 0.f, -1.f);
	vtx[3].pos = Vector3(0.5f, 0.5f, 0.f);
	vtx[3].uv = Vector2(1.f, 0.f);
	vtx[2].normal = Vector3(0.f, 0.f, -1.f);
	geometry->SetVertices(vtx);

	Vector<uint32> idx = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateCube(SharedPtr<Geometry<VertexTextureNormalData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	Vector<VertexTextureNormalData> vtx(24);

	vtx[0] = VertexTextureNormalData{ Vector3(-w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) };
	vtx[1] = VertexTextureNormalData{ Vector3(-w2, +h2, -d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) };
	vtx[2] = VertexTextureNormalData{ Vector3(+w2, +h2, -d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) };
	vtx[3] = VertexTextureNormalData{ Vector3(+w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) };
	vtx[4] = VertexTextureNormalData{ Vector3(-w2, -h2, +d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f) };
	vtx[5] = VertexTextureNormalData{ Vector3(+w2, -h2, +d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f) };
	vtx[6] = VertexTextureNormalData{ Vector3(+w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f) };
	vtx[7] = VertexTextureNormalData{ Vector3(-w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f) };
	vtx[8] = VertexTextureNormalData{ Vector3(-w2, +h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f) };
	vtx[9] = VertexTextureNormalData{ Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f) };
	vtx[10] = VertexTextureNormalData{ Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f) };
	vtx[11] = VertexTextureNormalData{ Vector3(+w2, +h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f) };
	vtx[12] = VertexTextureNormalData{ Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f) };
	vtx[13] = VertexTextureNormalData{ Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f) };
	vtx[14] = VertexTextureNormalData{ Vector3(+w2, -h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f) };
	vtx[15] = VertexTextureNormalData{ Vector3(-w2, -h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f) };
	vtx[16] = VertexTextureNormalData{ Vector3(-w2, -h2, +d2), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f) };
	vtx[17] = VertexTextureNormalData{ Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f) };
	vtx[18] = VertexTextureNormalData{ Vector3(-w2, +h2, -d2), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f) };
	vtx[19] = VertexTextureNormalData{ Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f) };
	vtx[20] = VertexTextureNormalData{ Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) };
	vtx[21] = VertexTextureNormalData{ Vector3(+w2, +h2, -d2), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) };
	vtx[22] = VertexTextureNormalData{ Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) };
	vtx[23] = VertexTextureNormalData{ Vector3(+w2, -h2, +d2), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) };

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(SharedPtr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ)
{
	Vector<VertexTextureNormalData> vtx;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalData v;
			v.pos = Vector3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = Vector2(static_cast<float>(x), static_cast<float>(sizeZ - z));
			v.normal = Vector3(0.f, 1.f, 0.f);

			vtx.push_back(v);
		}
	}

	geometry->SetVertices(vtx);

	Vector<uint32> idx;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z)+(x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(SharedPtr<Geometry<VertexTextureNormalData>> geometry)
{
	using namespace DirectX;

	float radius = 0.5f;
	uint32 stackCount = 20;
	uint32 sliceCount = 20;

	Vector<VertexTextureNormalData> vtx;

	VertexTextureNormalData v;

	v.pos = Vector3(0.0f, radius, 0.0f);
	v.uv = Vector2(0.5f, 0.0f);
	v.normal = v.pos;
	v.normal.Normalize();
	vtx.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.pos.x = radius * sinf(phi) * cosf(theta);
			v.pos.y = radius * cosf(phi);
			v.pos.z = radius * sinf(phi) * sinf(theta);

			v.uv = Vector2(deltaU * x, deltaV * y);

			v.normal = v.pos;
			v.normal.Normalize();

			vtx.push_back(v);
		}
	}

	v.pos = Vector3(0.0f, -radius, 0.0f);
	v.uv = Vector2(0.5f, 1.0f);
	v.normal = v.pos;
	v.normal.Normalize();
	vtx.push_back(v);

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	// ºÏ±Ø ÀÎµ¦½º
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		//  [0]
		//   |  \
			//  [i+1]-[i+2]
		idx.push_back(0);
		idx.push_back(i + 2);
		idx.push_back(i + 1);
	}

	// ¸öÅë ÀÎµ¦½º
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			idx.push_back(1 + (y)*ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// ³²±Ø ÀÎµ¦½º
	uint32 bottomIndex = static_cast<uint32>(vtx.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 0; i < sliceCount; ++i)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		idx.push_back(bottomIndex);
		idx.push_back(lastRingStartIndex + i);
		idx.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateQuad(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	Vector<VertexTextureNormalTangentData> vtx;
	vtx.resize(4);

	vtx[0].pos = Vector3(-0.5f, -0.5f, 0.f);
	vtx[0].uv = Vector2(0.f, 1.f);
	vtx[0].normal = Vector3(0.f, 0.f, -1.f);
	vtx[0].tangent = Vector3(1.0f, 0.0f, 0.0f);
	vtx[1].pos = Vector3(-0.5f, 0.5f, 0.f);
	vtx[1].uv = Vector2(0.f, 0.f);
	vtx[1].normal = Vector3(0.f, 0.f, -1.f);
	vtx[1].tangent = Vector3(1.0f, 0.0f, 0.0f);
	vtx[2].pos = Vector3(0.5f, -0.5f, 0.f);
	vtx[2].uv = Vector2(1.f, 1.f);
	vtx[2].normal = Vector3(0.f, 0.f, -1.f);
	vtx[2].tangent = Vector3(1.0f, 0.0f, 0.0f);
	vtx[3].pos = Vector3(0.5f, 0.5f, 0.f);
	vtx[3].uv = Vector2(1.f, 0.f);
	vtx[3].normal = Vector3(0.f, 0.f, -1.f);
	vtx[3].tangent = Vector3(1.0f, 0.0f, 0.0f);
	geometry->SetVertices(vtx);

	Vector<uint32> idx = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateCube(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	Vector<VertexTextureNormalTangentData> vtx(24);

	vtx[0] = VertexTextureNormalTangentData{Vector3(-w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[1] = VertexTextureNormalTangentData{Vector3(-w2, +h2, -d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[2] = VertexTextureNormalTangentData{Vector3(+w2, +h2, -d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[3] = VertexTextureNormalTangentData{Vector3(+w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[4] = VertexTextureNormalTangentData{Vector3(-w2, -h2, +d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[5] = VertexTextureNormalTangentData{Vector3(+w2, -h2, +d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[6] = VertexTextureNormalTangentData{Vector3(+w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[7] = VertexTextureNormalTangentData{Vector3(-w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[8] = VertexTextureNormalTangentData{Vector3(-w2, +h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[9] = VertexTextureNormalTangentData{Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[10] = VertexTextureNormalTangentData{Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[11] = VertexTextureNormalTangentData{Vector3(+w2, +h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)};
	vtx[12] = VertexTextureNormalTangentData{Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[13] = VertexTextureNormalTangentData{Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[14] = VertexTextureNormalTangentData{Vector3(+w2, -h2, +d2), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[15] = VertexTextureNormalTangentData{Vector3(-w2, -h2, +d2), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)};
	vtx[16] = VertexTextureNormalTangentData{Vector3(-w2, -h2, +d2), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)};
	vtx[17] = VertexTextureNormalTangentData{Vector3(-w2, +h2, +d2), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)};
	vtx[18] = VertexTextureNormalTangentData{Vector3(-w2, +h2, -d2), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)};
	vtx[19] = VertexTextureNormalTangentData{Vector3(-w2, -h2, -d2), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)};
	vtx[20] = VertexTextureNormalTangentData{Vector3(+w2, -h2, -d2), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)};
	vtx[21] = VertexTextureNormalTangentData{Vector3(+w2, +h2, -d2), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)};
	vtx[22] = VertexTextureNormalTangentData{Vector3(+w2, +h2, +d2), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)};
	vtx[23] = VertexTextureNormalTangentData{Vector3(+w2, -h2, +d2), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)};

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry, int32 sizeX, int32 sizeZ)
{
	Vector<VertexTextureNormalTangentData> vtx;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalTangentData v;
			v.pos = Vector3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = Vector2(static_cast<float>(x), static_cast<float>(sizeZ - z));
			v.normal = Vector3(0.f, 1.f, 0.f);
			v.tangent = Vector3(1.f, 0.f, 0.f);

			vtx.push_back(v);
		}
	}

	geometry->SetVertices(vtx);

	Vector<uint32> idx;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z)+(x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	using namespace DirectX;

	float radius = 0.5f;
	uint32 stackCount = 20;
	uint32 sliceCount = 20;

	Vector<VertexTextureNormalTangentData> vtx;

	VertexTextureNormalTangentData v;

	v.pos = Vector3(0.0f, radius, 0.0f);
	v.uv = Vector2(0.5f, 0.0f);
	v.normal = v.pos;
	v.normal.Normalize();
	v.tangent = Vector3(1.0f, 0.0f, 0.0f);
	v.tangent.Normalize();
	vtx.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.pos.x = radius * sinf(phi) * cosf(theta);
			v.pos.y = radius * cosf(phi);
			v.pos.z = radius * sinf(phi) * sinf(theta);

			v.uv = Vector2(deltaU * x, deltaV * y);

			v.normal = v.pos;
			v.normal.Normalize();

			v.tangent.x = -radius * sinf(phi) * sinf(theta);
			v.tangent.y = 0.0f;
			v.tangent.z = radius * sinf(phi) * cosf(theta);
			v.tangent.Normalize();

			vtx.push_back(v);
		}
	}

	v.pos = Vector3(0.0f, -radius, 0.0f);
	v.uv = Vector2(0.5f, 1.0f);
	v.normal = v.pos;
	v.normal.Normalize();
	v.tangent = Vector3(1.0f, 0.0f, 0.0f);
	v.tangent.Normalize();
	vtx.push_back(v);

	geometry->SetVertices(vtx);

	Vector<uint32> idx(36);

	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		idx.push_back(0);
		idx.push_back(i + 2);
		idx.push_back(i + 1);
	}

	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			idx.push_back(1 + (y)*ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	uint32 bottomIndex = static_cast<uint32>(vtx.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 0; i < sliceCount; ++i)
	{
		idx.push_back(bottomIndex);
		idx.push_back(lastRingStartIndex + i);
		idx.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(idx);
}
