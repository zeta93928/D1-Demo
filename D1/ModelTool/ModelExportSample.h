#pragma once

class ModelExportSample : public IEngine
{
	virtual ~ModelExportSample() {}
	virtual bool __stdcall Init() override;
	virtual void __stdcall Update() override;
	virtual void __stdcall Render() override;
	virtual void __stdcall Release() override;
};


