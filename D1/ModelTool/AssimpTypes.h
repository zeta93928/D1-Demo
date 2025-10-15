#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct AS_Bone
{
	String name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct AS_Mesh
{
	String name;
	aiMesh* mesh;
	Vector<VertexType> vertices;
	Vector<uint32> indices;
	int32 boneIndex;
	String materialName;
};

struct AS_Material
{
	String name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	String diffuseFile;
	String specularFile;
	String normalFile;
};

