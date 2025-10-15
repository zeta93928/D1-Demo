#pragma once

struct IEngine
{
public:
	virtual ~IEngine() {}
	virtual bool __stdcall Init() = 0;
	virtual void __stdcall Update() = 0;
	virtual void __stdcall Render() = 0;
	virtual void __stdcall Release() = 0;
};