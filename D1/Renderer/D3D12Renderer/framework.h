#pragma once      

// CRT Debug
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN       

// Windows Header Files
#include <windows.h>
