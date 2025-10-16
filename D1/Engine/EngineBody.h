#pragma once

extern IRenderer* GRenderer;

struct IEngine;

struct GameDesc
{
	IEngine* app = nullptr;
	WString appName = L"";
	HINSTANCE hInstance = nullptr;
	HWND hwnd = nullptr;
	float screenWidth = 800.0f;
	float screenHeight = 600.0f;
	bool vsync = false;
	bool windowed = true;
};

class EngineBody
{
	DECLARE_SINGLETON(EngineBody);
public:
	WPARAM Run(const GameDesc& desc);

	const GameDesc& GetGameDesc() { return m_gameDesc; }

private:
	void Tick();
	
	void CleanUp();

	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	void UpdateGlobalData();

private:
	GameDesc m_gameDesc = {};
};