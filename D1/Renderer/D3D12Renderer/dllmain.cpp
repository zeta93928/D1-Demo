// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "D3D12Renderer.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C"
{
    bool __stdcall DLL_CreateInstance(void** instance)
    {
        IRenderer* renderer = new D3D12Renderer;
        if (nullptr == renderer)
        {
            return false;
        }
        
        *instance = renderer;

        return true;
    } 
}
