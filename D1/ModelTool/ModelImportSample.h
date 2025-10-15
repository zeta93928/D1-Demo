#pragma once

class ModelImportSample : public IEngine
{
	virtual ~ModelImportSample() {}
	virtual bool __stdcall Init() override;
	virtual void __stdcall Update() override;
	virtual void __stdcall Render() override;
	virtual void __stdcall Release() override;
};

