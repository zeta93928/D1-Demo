#pragma once

struct IEngine
{
public:
	virtual ~IEngine() {}
	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};