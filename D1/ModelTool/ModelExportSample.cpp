#include "pch.h"
#include "ModelExportSample.h"
#include "ModelConverter.h"

bool __stdcall ModelExportSample::Init()
{
    {
        SharedPtr<ModelConverter> converter = MakeShared<ModelConverter>();
        
        // FBX -> Memory
        converter->ReadAssetFromFile(L"Paladin/Paladin.fbx");

        // Memory -> Custom Data
        converter->ExportModelFile(L"Paladin/Paladin");
        converter->ExportMaterialData(L"Paladin/Paladin");
    }

    return true;
}

void __stdcall ModelExportSample::Update()
{
}

void __stdcall ModelExportSample::Render()
{
}

void __stdcall ModelExportSample::Release()
{
}
