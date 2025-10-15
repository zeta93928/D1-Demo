#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "Game.h"

#pragma comment(lib, "../Build/Engine_Debug_x64.lib")

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GameDesc gameDesc = {};
	gameDesc.appName = L"D1-Demo";
	gameDesc.hInstance = hInstance;
	gameDesc.vsync = false;
	gameDesc.screenWidth = 800;
	gameDesc.screenHeight = 600;
	gameDesc.app = new Game;

	return (int)EngineBody::Get().Run(gameDesc);
}





