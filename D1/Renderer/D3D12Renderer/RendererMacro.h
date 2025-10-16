#pragma once

#define DEVICE				GRenderer->GetDevice()
#define RESOURCE_MANAGER	GRenderer->GetResourceManager()
#define CONSTANT_POOL(type) GRenderer->GetConstantBufferPool(type)
#define DESC_POOL			GRenderer->GetDescriptorPool()
#define DESC_ALLOCATOR		GRenderer->GetDescriptorAllocator()		

#define SRV_DESC_SIZE		GRenderer->GetSRVDescriptorSize()
#define RTV_DESC_SIZE		GRenderer->GetRTVDescriptorSize()
#define DSV_DESC_SIZE		GRenderer->GetDSVDescriptorSize()

#define VIEW_MATRIX			GRenderer->GetGlobalRenderData().view
#define PROJ_MATRIX			GRenderer->GetGlobalRenderData().proj