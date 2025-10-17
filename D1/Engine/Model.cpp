#include "pch.h"
#include "Model.h"
#include "../Utils/CommonUtils.h"
#include "../Utils/FileUtils.h"
#include "MaterialAsset.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::ReadModel(const WString& fileName)
{
	wstring fullPath = m_modelPath + fileName + L".mesh";

	SharedPtr<FileUtils> file = make_shared<FileUtils>();
	file->Open(fullPath, FileMode::Read);

	// Bones
	{
		const uint32 count = file->Read<uint32>();

		for (uint32 i = 0; i < count; i++)
		{
			SharedPtr<ModelBone> bone = make_shared<ModelBone>();
			bone->index = file->Read<int32>();
			bone->name = CommonUtils::ToWString(file->Read<string>());
			bone->parentIndex = file->Read<int32>();
			bone->transform = file->Read<Matrix>();

			m_bones.push_back(bone);
		}
	}

	// Mesh
	{
		const uint32 count = file->Read<uint32>();

		for (uint32 i = 0; i < count; i++)
		{
			SharedPtr<ModelMesh> mesh = make_shared<ModelMesh>();

			mesh->meshName = CommonUtils::ToWString(file->Read<string>());
			mesh->boneIndex = file->Read<int32>();

			// Material
			mesh->materialName = CommonUtils::ToWString(file->Read<string>());

			//VertexData
			{
				const uint32 count = file->Read<uint32>();
				vector<ModelVertexType> vertices;
				vertices.resize(count);

				void* data = vertices.data();
				file->Read(&data, sizeof(ModelVertexType) * count);
				mesh->geometry->AddVertices(vertices);
			}

			//IndexData
			{
				const uint32 count = file->Read<uint32>();

				vector<uint32> indices;
				indices.resize(count);

				void* data = indices.data();
				file->Read(&data, sizeof(uint32) * count);
				mesh->geometry->AddIndices(indices);
			}

			m_meshes.push_back(mesh);
		}
	}
}

void Model::ReadMaterial(const WString& fileName)
{
}

void Model::BindCacheInfo()
{
	// Mesh에 Material 캐싱
	for (const auto& mesh : m_meshes)
	{
		// 이미 찾았으면 스킵
		if (mesh->material != nullptr)
		{
			continue;
		}

		mesh->material = GetMaterialByName(mesh->materialName);
	}

	// Mesh에 Bone 캐싱
	for (const auto& mesh : m_meshes)
	{
		// 이미 찾았으면 스킵
		if (mesh->bone != nullptr)
		{
			continue;
		}

		mesh->bone = GetBoneByIndex(mesh->boneIndex);
	}

	// Bone 계층 정보 채우기
	if (m_root == nullptr && m_bones.size() > 0)
	{
		m_root = m_bones[0];

		for (const auto& bone : m_bones)
		{
			if (bone->parentIndex >= 0)
			{
				bone->parent = m_bones[bone->parentIndex];
				bone->parent->children.push_back(bone);
			}
			else
			{
				bone->parent = nullptr;
			}
		}
	}
}

MaterialAssetRef Model::GetMaterialByName(const WString& name)
{
	for (auto& material : m_materials)
	{
		if (material->GetName() == name)
		{
			return material;
		}
	}

	return nullptr;
}

SharedPtr<ModelMesh> Model::GetMeshByName(const WString& name)
{
	for (auto& mesh : m_meshes)
	{
		if (mesh->meshName == name)
		{
			return mesh;
		}
	}

	return nullptr;
}

SharedPtr<ModelBone> Model::GetBoneByName(const WString& name)
{
	for (auto& bone : m_bones)
	{
		if (bone->name == name)
		{
			return bone;
		}
	}

	return nullptr;
}
