#pragma once

#include <cassert>
#include <windows.h>
#include <directxtex/directxtex.h>

// Renderer Type
#include "VertexData.h"

// Interface
#include "IRenderer.h"
#include "IEngine.h"

// Common
#include "Types.h"
#include "Struct.h"
#include "Enum.h"

// Inner
#include "EngineMacro.h"
#include "EngineTypes.h"
#include "EngineBody.h"
#include "SceneComponent.h"
#include "CameraComponent.h"
#include "RenderProxy.h"
#include "InputManager.h"
#include "TimeManager.h"

// Disable Warning
#pragma warning(disable:4244)