#pragma once

enum class AssetType : int8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,
	End,
};

enum
{
	ASSET_TYPEE_COUNT = (int8)(AssetType::End)
};

class AssetBase : public std::enable_shared_from_this<AssetBase>
{
public:
	AssetBase(AssetType type);
	virtual ~AssetBase();

	AssetType GetType() { return m_type; }

	void SetName(const WString& name) { m_name = name; }
	const WString& GetName() { return m_name; }
	uint32 GetID() { return m_id; }

protected:
	virtual void Load(const WString& path) {}
	virtual void Save(const WString& path) {}

protected:
	AssetType m_type = AssetType::None;
	WString m_name;
	WString m_path;
	uint32 m_id = 0;
};

