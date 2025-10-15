#include "pch.h"
#include "ModelExporter.h"
#include "ModelConverter.h"

bool __stdcall ModelExporter::Init()
{
    {
        SharedPtr<ModelConverter> converter = MakeShared<ModelConverter>();
        
        // FBX -> Memory
        converter->ReadAssetFromFile(L"Paladin/Paladin.fbx");

        // Memory -> Custom Data
        converter->ExportModelFile(L"Paladin/Paladin");
    }


    return true;
}

void __stdcall ModelExporter::Update()
{
}

void __stdcall ModelExporter::Render()
{
}

void __stdcall ModelExporter::Release()
{
}
