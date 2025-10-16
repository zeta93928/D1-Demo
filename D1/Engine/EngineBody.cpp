#include "pch.h"
#include "EngineBody.h"

/*-----------------------------------------------------------------------------------
									   Libs
-------------------------------------------------------------------------------------*/
#ifdef _DEBUG
#pragma comment(lib, "E:/D1-Demo/D1/ThirdParty/Libs/DirectXTex/DirectXTex_debug.lib")
#else
#pragma comment(lib, "../ThirdParty/Libs/DriectXTex/DirectXTex.lib")
#endif

/*-----------------------------------------------------------------------------------
								   Nvidia option
-------------------------------------------------------------------------------------*/
extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }


/*-----------------------------------------------------------------------------------
								  D3D12 SDK Agility
-------------------------------------------------------------------------------------*/
extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 618; }

#if defined(_M_ARM64EC)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\arm64\\"; }
#elif defined(_M_ARM64)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\arm64\\"; }
#elif defined(_M_AMD64)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\x64\\"; }
#elif defined(_M_IX86)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\x86\\"; }
#endif

IRenderer* GRenderer = nullptr;


/*-----------------------------------------------------------------------------------
								  Engine Entry Point
-------------------------------------------------------------------------------------*/
WPARAM EngineBody::Run(const GameDesc& desc)
{
	m_gameDesc = desc;
	assert(m_gameDesc.app);

	// 윈도우 정보 등록
	MyRegisterClass();

	// 윈도우 창 생성
	if (!InitInstance(SW_SHOWNORMAL))
	{
		return FALSE;
	}

	// Renderer DLL 경로 지정
	const WCHAR* rendererDLL_Path = nullptr;

#ifdef _DEBUG
#ifdef _M_AMD64
	rendererDLL_Path = L"../DLL/D3D12Renderer_Debug_x64.dll";
#elif _M_IX86
	rendererDLL_Path = L"../DLL/D3D12Renderer_Debug_x86.dll";
#endif
#else
#ifdef _M_AMD64
	rendererDLL_Path = L"../DLL/D3D12Renderer_Release_x64.dll";
#elif _M_IX86
	rendererDLL_Path = L"../DLL/D3D12Renderer_Release_x86.dll";
#endif
#endif

	// Renderer Instance 생성
	HMODULE hRendererDLL = LoadLibrary(rendererDLL_Path);
	assert(hRendererDLL);

	CREATE_INSTANCE_FUNC RendererDLL_CreateInstance = (CREATE_INSTANCE_FUNC)GetProcAddress(hRendererDLL, "DLL_CreateInstance");
	assert(RendererDLL_CreateInstance);

	bool check = RendererDLL_CreateInstance(&GRenderer);
	assert(check);
	assert(GRenderer);

	// Manager 초기화
	assert(InputManager::Get().Init(m_gameDesc.hwnd));
	assert(TimeManager::Get().Init());
	assert(GRenderer->Init(m_gameDesc.hwnd, true, true));
	assert(m_gameDesc.app->Init());

	MSG msg = {};

	// Main message loop:
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Tick();
		}
	}

	CleanUp();

	return msg.wParam;
}

void EngineBody::Tick()
{
	TimeManager::Get().Update();
	InputManager::Get().Update();

	GRenderer->BeginRender();
	{
		m_gameDesc.app->Update();
		{
			UpdateGlobalData();
		}
		m_gameDesc.app->Render();
	}
	GRenderer->EndRender();
	GRenderer->Present();

	// TEMP
	{
		WString fps = std::to_wstring(TimeManager::Get().GetFps()) + L" fps";
		SetWindowText(m_gameDesc.hwnd, fps.c_str());
	}
}

void EngineBody::CleanUp()
{
	m_gameDesc.app->Release();
	m_gameDesc.app = nullptr;

	GRenderer->Release();
	GRenderer = nullptr;
}

ATOM EngineBody::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_gameDesc.hInstance;
	wcex.hIcon = ::LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_gameDesc.appName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

BOOL EngineBody::InitInstance(int cmdShow)
{
	RECT windowRect = { 0, 0, (LONG)m_gameDesc.screenWidth, (LONG)m_gameDesc.screenHeight };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	m_gameDesc.hwnd = CreateWindowW(m_gameDesc.appName.c_str(), m_gameDesc.appName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, m_gameDesc.hInstance, nullptr);

	if (!m_gameDesc.hwnd)
	{
		return FALSE;
	}

	ShowWindow(m_gameDesc.hwnd, cmdShow);
	UpdateWindow(m_gameDesc.hwnd);

	return TRUE;
}

LRESULT EngineBody::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		if(GRenderer) 
		{
			uint32 width = LOWORD(lParam);
			uint32 height = HIWORD(lParam);
			GRenderer->UpdateWindowSize(width, height);
			CameraComponent::UpdateWindowSize(width, height);
		}
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle, message, wParam, lParam);
	}
	return ::DefWindowProc(handle, message, wParam, lParam);
}

void EngineBody::UpdateGlobalData()
{
	// 카메라 정보 Renderer 에 업데이트
	GlobalRenderData globalData = {};
	globalData.view = CameraComponent::sm_viewMat;
	globalData.proj = CameraComponent::sm_projMat;
	globalData.viewInv = CameraComponent::sm_viewMat.Invert();
	globalData.viewProj = globalData.view * globalData.proj;
	RenderProxy::Get().EnqueueGlobalData(globalData);
}
