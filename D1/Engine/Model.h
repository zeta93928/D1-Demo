#pragma once

#include "Geometry.h"

struct ModelBone
{
	WString name;
	int32 index;
	int32 parentIndex;
	SharedPtr<ModelBone> parent; 

	Matrix transform;
	Vector<SharedPtr<ModelBone>> children;
};

struct ModelMesh
{
	// Mesh
	WString meshName;
	SharedPtr<Geometry<ModelVertexType>> geometry = MakeShared<Geometry<ModelVertexType>>();

	// Material
	WString materialName = L"";
	MaterialAssetRef material;

	// Bones
	int32 boneIndex;
	SharedPtr<ModelBone> bone;
};

class Model : public std::enable_shared_from_this<Model>
{
public:
	Model();
	~Model();

	void ReadModel(const WString& fileName);
	void ReadMaterial(const WString& fileName);

	uint32 GetMaterialCount() { return static_cast<uint32>(m_materials.size()); }
	Vector<MaterialAssetRef>& GetMaterials() { return m_materials; }
	MaterialAssetRef GetMaterialByIndex(uint32 index) { return m_materials[index]; }
	MaterialAssetRef GetMaterialByName(const WString& name);

	uint32 GetMeshCount() { return static_cast<uint32>(m_meshes.size()); }
	Vector<SharedPtr<ModelMesh>>& GetMeshes() { return m_meshes; }
	SharedPtr<ModelMesh> GetMeshByIndex(uint32 index) { return m_meshes[index]; }
	SharedPtr<ModelMesh> GetMeshByName(const WString& name);
	
	uint32 GetBoneCount() { return static_cast<uint32>(m_bones.size()); }
	Vector<SharedPtr<ModelBone>>& GetBones() { return m_bones; }
	SharedPtr<ModelBone> GetBoneByIndex(uint32 index) { return (index < 0 || index >= m_bones.size() ? nullptr : m_bones[index]); }
	SharedPtr<ModelBone> GetBoneByName(const WString& name);

private:
	void BindCacheInfo();

private:
	WString m_modelPath = L"../Resources/Models/";
	WString m_texturePath = L"../Resources/Textures/";

	SharedPtr<ModelBone> m_root;
	Vector<SharedPtr<ModelMesh>> m_meshes = {};
	Vector<SharedPtr<ModelBone>> m_bones = {};
	Vector<MaterialAssetRef> m_materials = {};
};

