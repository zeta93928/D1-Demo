#pragma once

#include "AssimpTypes.h"

class ModelConverter
{
public:
	ModelConverter();
	~ ModelConverter();

	void ReadAssetFromFile(WString file);
	void ExportModelFile(WString savePath);
	void ExportMaterialData(WString savePath);

private:
	void ReadModelData(aiNode* node, int32 index, int32 parent);
	void ReadMeshData(aiNode* node, int32 bone);
	void WriteModelFile(WString finalPath);

	void ReadMaterialData();
	void WriteMaterialData(WString finalPath);
	String WriteTexture(String saveFolder, String file);

private:
	WString m_oldPath = L"../Assets/Old/";
	WString m_modelPath = L"../Assets/Models/";
	WString m_texturePath = L"../Assets/Textures/";

	SharedPtr<Assimp::Importer> m_importer;
	const aiScene* m_scene = nullptr;

	Vector<SharedPtr<AS_Bone>> m_bones;
	Vector<SharedPtr<AS_Mesh>> m_meshes;
	Vector<SharedPtr<AS_Material>> m_materials;
};

