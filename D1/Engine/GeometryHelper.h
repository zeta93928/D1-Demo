#pragma once

#include "Geometry.h"

class GeometryHelper
{
public:
	static void CreateQuad(SharedPtr<Geometry<VertexColorData>> geometry, Color color);

	static void CreateQuad(SharedPtr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(SharedPtr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(SharedPtr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(SharedPtr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);

	static void CreateQuad(SharedPtr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(SharedPtr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(SharedPtr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ);
	static void CreateSphere(SharedPtr<Geometry<VertexTextureNormalData>> geometry);

	static void CreateQuad(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateCube(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry, int32 sizeX, int32 sizeZ);
	static void CreateSphere(SharedPtr<Geometry<VertexTextureNormalTangentData>> geometry);
};

