#include "pch.h"
#include "ModelExporter.h"

#pragma comment(lib, "../Build/Engine_Debug_x64.lib")
#pragma comment(lib, "../ThirdParty/Libs/Assimp/assimp-vc143-mtd.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc = {};
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.screenWidth = 800;
	desc.screenHeight = 600;
	desc.app = new ModelExporter();

	return (int)EngineBody::Get().Run(desc);
}