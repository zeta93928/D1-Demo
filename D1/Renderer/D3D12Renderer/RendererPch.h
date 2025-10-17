#pragma once

// Add headers that you want to pre-compile here
#include "framework.h"

// D3D
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dx12.h>
#include <dxgidebug.h>
#include <d3dcompiler.h>
#include <directxtex/directxtex.h>

// STL
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <stack>

// Common
#include "Types.h"

// Inner
#include "RendererEnum.h"
#include "RendererMacro.h"
#include "IRenderer.h"
#include "VertexData.h"
#include "D3D12Renderer.h"
#include "D3D12ResourceManager.h"
#include "ConstantBufferManager.h"
#include "DescriptorPool.h"
#include "DescriptorAllocator.h"
#include "ConstantBufferPool.h"

