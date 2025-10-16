#include "pch.h"
#include "TextureAsset.h"

TextureAsset::TextureAsset()
	: AssetBase(AssetType::Texture)
{
}

TextureAsset::~TextureAsset()
{
	if (m_texHandle)
	{
		GRenderer->ReleaseTextureHandle(m_name.c_str());
	}
}

void TextureAsset::Load(const WString& path)
{
	using namespace DirectX;

	m_name = path;

	TexMetadata md = {};
	LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, m_img);

	// Renderer ·Î ºÎÅÍ Texture Handle Access
	m_texHandle = GRenderer->AccessTextureHandle(path.c_str(), &m_img);
}
