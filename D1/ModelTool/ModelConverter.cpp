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
	WString fullPath = m_texturePath + savePath + L".xml";
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
	for (uint32 i = 0; i < m_scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = m_scene->mMaterials[i];

		SharedPtr<AS_Material> material = MakeShared<AS_Material>();
		material->name = srcMaterial->GetName().C_Str();

		aiColor3D color;

		// Ambient
		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->ambient = Color(color.r, color.g, color.b, 1.f);

		// Diffuse
		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->diffuse = Color(color.r, color.g, color.b, 1.f);

		// Specular
		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->specular = Color(color.r, color.g, color.b, 1.f);
		srcMaterial->Get(AI_MATKEY_SHININESS, material->specular.w);

		// Emissive
		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->emissive = Color(color.r, color.g, color.b, 1.0f);

		aiString file;

		// Diffuse Texture
		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->diffuseFile = file.C_Str();

		// Specular Texture
		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->specularFile = file.C_Str();

		// Normal Texture
		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->normalFile = file.C_Str();

		m_materials.push_back(material);
	}
}

void ModelConverter::WriteMaterialData(WString finalPath)
{
	auto path = filesystem::path(finalPath);

	// 폴더가 없으면 만든다.
	filesystem::create_directory(path.parent_path());

	String folder = path.parent_path().string();

	SharedPtr<tinyxml2::XMLDocument> document = MakeShared<tinyxml2::XMLDocument>();

	tinyxml2::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	tinyxml2::XMLElement* root = document->NewElement("Materials");
	document->LinkEndChild(root);

	for (shared_ptr<AS_Material> material : m_materials)
	{
		tinyxml2::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);

		tinyxml2::XMLElement* element = nullptr;

		element = document->NewElement("Name");
		element->SetText(material->name.c_str());
		node->LinkEndChild(element);

		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, material->diffuseFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, material->specularFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, material->normalFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("Ambient");
		element->SetAttribute("R", material->ambient.x);
		element->SetAttribute("G", material->ambient.y);
		element->SetAttribute("B", material->ambient.z);
		element->SetAttribute("A", material->ambient.w);
		node->LinkEndChild(element);

		element = document->NewElement("Diffuse");
		element->SetAttribute("R", material->diffuse.x);
		element->SetAttribute("G", material->diffuse.y);
		element->SetAttribute("B", material->diffuse.z);
		element->SetAttribute("A", material->diffuse.w);
		node->LinkEndChild(element);

		element = document->NewElement("Specular");
		element->SetAttribute("R", material->specular.x);
		element->SetAttribute("G", material->specular.y);
		element->SetAttribute("B", material->specular.z);
		element->SetAttribute("A", material->specular.w);
		node->LinkEndChild(element);

		element = document->NewElement("Emissive");
		element->SetAttribute("R", material->emissive.x);
		element->SetAttribute("G", material->emissive.y);
		element->SetAttribute("B", material->emissive.z);
		element->SetAttribute("A", material->emissive.w);
		node->LinkEndChild(element);
	}

	document->SaveFile(CommonUtils::ToString(finalPath).c_str());
}

String ModelConverter::WriteTexture(String saveFolder, String file)
{
	string fileName = filesystem::path(file).filename().string();
	string folderName = filesystem::path(saveFolder).filename().string();

	const aiTexture* srcTexture = m_scene->GetEmbeddedTexture(file.c_str());
	if (srcTexture)
	{
		string pathStr = saveFolder + fileName;

		if (srcTexture->mHeight == 0)
		{
			shared_ptr<FileUtils> file = make_shared<FileUtils>();
			file->Open(CommonUtils::ToWString(pathStr), FileMode::Write);
			file->Write(srcTexture->pcData, srcTexture->mWidth);
		}
		else
		{
			//D3D11_TEXTURE2D_DESC desc;
			//ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
			//desc.Width = srcTexture->mWidth;
			//desc.Height = srcTexture->mHeight;
			//desc.MipLevels = 1;
			//desc.ArraySize = 1;
			//desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			//desc.SampleDesc.Count = 1;
			//desc.SampleDesc.Quality = 0;
			//desc.Usage = D3D11_USAGE_IMMUTABLE;

			//D3D11_SUBRESOURCE_DATA subResource = { 0 };
			//subResource.pSysMem = srcTexture->pcData;

			//ComPtr<ID3D11Texture2D> texture;
			//HRESULT hr = DEVICE->CreateTexture2D(&desc, &subResource, texture.GetAddressOf());
			//CHECK(hr);

			//DirectX::ScratchImage img;
			//::CaptureTexture(DEVICE.Get(), DC.Get(), texture.Get(), img);

			//// Save To File
			//hr = DirectX::SaveToDDSFile(*img.GetImages(), DirectX::DDS_FLAGS_NONE, CommonUtils::ToWString(fileName).c_str());
			//CHECK(hr);
		}
	}
	else
	{
		string originStr = (filesystem::path(m_oldPath) / folderName / file).string();
		CommonUtils::Replace(originStr, "\\", "/");

		string pathStr = (filesystem::path(saveFolder) / fileName).string();
		CommonUtils::Replace(pathStr, "\\", "/");

		CopyFileA(originStr.c_str(), pathStr.c_str(), false);
	}

	return fileName;
}
