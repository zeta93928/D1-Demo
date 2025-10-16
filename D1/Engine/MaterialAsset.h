#pragma once

#include "AssetBase.h"

class MaterialAsset : public AssetBase
{
public:
	MaterialAsset();
	virtual ~MaterialAsset();

	TextureAssetRef GetAlbedoMap() { return m_albedo; }
	TextureAssetRef GetNormalMap() { return m_normal; }

	void SetAlbedoMap(TextureAssetRef albedo) { m_albedo = albedo; }
	void SetNormalMap(TextureAssetRef normal) { m_normal = normal; }

private:
	TextureAssetRef m_albedo;
	TextureAssetRef m_normal;
};

