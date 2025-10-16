#pragma once

#define DEVICE				GRenderer->GetDevice()
#define RESOURCE_MANAGER	GRenderer->GetResourceManager()
#define CONST_MANAGER		GRenderer->GetConstantBufferManager()
#define DESC_POOL			GRenderer->GetDescriptorPool()

#define SRV_DESC_SIZE		GRenderer->GetSRVDescriptorSize()
#define RTV_DESC_SIZE		GRenderer->GetRTVDescriptorSize()
#define DSV_DESC_SIZE		GRenderer->GetDSVDescriptorSize()

#define VIEW_MATRIX			GRenderer->GetGlobalRenderData().view
#define PROJ_MATRIX			GRenderer->GetGlobalRenderData().proj