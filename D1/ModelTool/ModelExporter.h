#pragma once

class ModelExporter : public IEngine
{
	virtual ~ModelExporter() {}
	virtual bool __stdcall Init() override;
	virtual void __stdcall Update() override;
	virtual void __stdcall Render() override;
	virtual void __stdcall Release() override;
};


