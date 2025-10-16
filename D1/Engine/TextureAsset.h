#pragma once

#include "AssetBase.h"

class TextureAsset : public AssetBase
{
public:
	TextureAsset();
	virtual ~TextureAsset();

	virtual void Load(const WString& path) override;

	void* GetTextureHandle() { return m_texHandle; }

private:
	DirectX::ScratchImage m_img = {};

	// Renderer DLL ÀÇ texture hanlde pointer
	void* m_texHandle = nullptr;

	WString m_name = L"";
};

