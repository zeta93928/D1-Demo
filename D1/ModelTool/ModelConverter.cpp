#include "pch.h"
#include "ModelConverter.h"
#include <filesystem>

ModelConverter::ModelConverter()
{
	m_importer = MakeShared<Assimp::Importer>();
}

ModelConverter::~ModelConverter()
{
}

void ModelConverter::ReadAssetFromFile(WString file)
{
	WString fileStr = m_oldPath + file;

	auto p = std::filesystem::path(fileStr);
	assert(std::filesystem::exists(p));

	m_scene = m_importer->ReadFile(
		CommonUtils::ToString(fileStr),
		aiProcess_ConvertToLeftHanded |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);

	assert(m_scene);
}

void ModelConverter::ExportModelFile(WString savePath)
{
	WString fullPath = m_modelPath + savePath + L".mesh";
	ReadModelData(m_scene->mRootNode, -1, -1);
	WriteModelFile(fullPath);
}

void ModelConverter::ExportMaterialData(WString savePath)
{
	WString fullPath = m_modelPath + savePath + L".xml";
	ReadMaterialData();
	WriteMaterialData(fullPath);
}

void ModelConverter::ReadModelData(aiNode* node, int32 index, int32 parent)
{
	SharedPtr<AS_Bone> bone = MakeShared<AS_Bone>();
	bone->index = index;
	bone->parent = parent;
	bone->name = node->mName.C_Str();

	Matrix transform(node->mTransformation[0]);
	bone->transform = transform.Transpose();

	// Root Transform
	Matrix matParent = Matrix::Identity;
	if (parent >= 0)
	{
		matParent = m_bones[parent]->transform;
	}

	// Final Transform
	bone->transform = bone->transform * matParent;

	m_bones.push_back(bone);

	// Mesh
	ReadMeshData(node, index);

	// Recursive
	for (uint32 i = 0; i < node->mNumChildren; i++)
	{
		ReadModelData(node->mChildren[i], m_bones.size(), index);
	}
}

void ModelConverter::ReadMeshData(aiNode* node, int32 bone)
{
	if (node->mNumMeshes < 1)
	{
		return;
	}

	SharedPtr<AS_Mesh> mesh = MakeShared<AS_Mesh>();
	mesh->name = node->mName.C_Str();
	mesh->boneIndex = bone;

	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		uint32 index = node->mMeshes[i];
		const aiMesh* srcMesh = m_scene->mMeshes[index];

		const aiMaterial* material = m_scene->mMaterials[srcMesh->mMaterialIndex];
		mesh->materialName = material->GetName().C_Str();

		const uint32 startVertex = mesh->vertices.size();

		// Vertex
		for (uint32 v = 0; v < srcMesh->mNumVertices; v++)
		{
			// Position
			VertexType vertex;
			memcpy(&vertex.pos, &srcMesh->mVertices[v], sizeof(Vector3));

			// Texcoord
			if (srcMesh->HasTextureCoords(0))
			{
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Vector2));
			}

			// Normal
			if (srcMesh->HasNormals())
			{
				memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Vector3));
			}

			mesh->vertices.push_back(vertex);
		}

		// Index
		for (uint32 f = 0; f < srcMesh->mNumFaces; f++)
		{
			aiFace& face = srcMesh->mFaces[f];

			for (uint32 k = 0; k < face.mNumIndices; k++)
			{
				// +Offset
				mesh->indices.push_back(face.mIndices[k] + startVertex);
			}
		}
	}

	m_meshes.push_back(mesh);
}

void ModelConverter::WriteModelFile(WString finalPath)
{
	auto path = filesystem::path(finalPath);
	auto temp = path.parent_path();

	// 폴더가 없으면 만든다.
	filesystem::create_directory(path.parent_path());

	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(finalPath, FileMode::Write);

	// Bone Data
	file->Write<uint32>(m_bones.size());
	for (shared_ptr<AS_Bone>& bone : m_bones)
	{
		file->Write<int32>(bone->index);
		file->Write<string>(bone->name);
		file->Write<int32>(bone->parent);
		file->Write<Matrix>(bone->transform);
	}

	// Mesh Data
	file->Write<uint32>(m_meshes.size());
	for (shared_ptr<AS_Mesh>& meshData : m_meshes)
	{
		file->Write<string>(meshData->name);
		file->Write<int32>(meshData->boneIndex);
		file->Write<string>(meshData->materialName);

		// Vertex Data
		file->Write<uint32>(meshData->vertices.size());
		file->Write(&meshData->vertices[0], sizeof(VertexType) * meshData->vertices.size());

		// Index Data
		file->Write<uint32>(meshData->indices.size());
		file->Write(&meshData->indices[0], sizeof(uint32) * meshData->indices.size());
	}
}

void ModelConverter::ReadMaterialData()
{
}

void ModelConverter::WriteMaterialData(WString finalPath)
{
}

String ModelConverter::WriteTexture(String saveFolder, String file)
{
	return String();
}
