#include "pch.h"
#include "PrimitiveRenderData.h"

ID3D12RootSignature* PrimitiveRenderData::sm_RootSig = nullptr;
ID3D12PipelineState* PrimitiveRenderData::sm_PSO = nullptr;
DWORD PrimitiveRenderData::m_refCount = 0;

PrimitiveRenderData::PrimitiveRenderData()
{
}

PrimitiveRenderData::~PrimitiveRenderData()
{
	CleanUp();
}

bool PrimitiveRenderData::Init()
{
	// 이미 StaicMesh 가 instance 화 되어있다면 공유리소스를 재생성하지 않고, 사용 카운트만 올려주고 리턴한다.
	if (m_refCount)
	{
		m_refCount++;

		return true;
	}


	// @TODO:
	// 해당 구조를 Shader Reflection 을 통해 통합


	// Create Root Signature
	{
		ID3DBlob* signature = nullptr;
		ID3DBlob* error = nullptr;

		CD3DX12_DESCRIPTOR_RANGE rangesGlobal[1] = {};
		rangesGlobal[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0); // b0: Global

		CD3DX12_DESCRIPTOR_RANGE rangesPerObj[2] = {};
		rangesPerObj[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1); // b1: transform
		rangesPerObj[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0: texture
		
		CD3DX12_ROOT_PARAMETER rootParameters[2] = {};
		rootParameters[0].InitAsDescriptorTable(_countof(rangesGlobal), rangesGlobal, D3D12_SHADER_VISIBILITY_ALL);
		rootParameters[1].InitAsDescriptorTable(_countof(rangesPerObj), rangesPerObj, D3D12_SHADER_VISIBILITY_ALL);

		// default sampler
		D3D12_STATIC_SAMPLER_DESC sampler = {};
		D3DUtils::SetDefaultSamplerDesc(&sampler, 0);
		sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;

		// Allow input layout and deny uneccessary access to certain pipeline stages.
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(_countof(rootParameters), rootParameters, 1, &sampler, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error)))
		{
			__debugbreak();
		}

		if (FAILED(DEVICE->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&sm_RootSig))))
		{
			__debugbreak();
		}

		if (signature)
		{
			signature->Release();
			signature = nullptr;
		}
		if (error)
		{
			error->Release();
			error = nullptr;
		}
	}





	// Create PSO
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;


#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		uint32 compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		uint32 compileFlags = 0;
#endif
		if (FAILED(D3DCompileFromFile(L"../Shaders/Default.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vs, nullptr)))
		{
			__debugbreak();
		}
		if (FAILED(D3DCompileFromFile(L"../Shaders/Default.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &ps, nullptr)))
		{
			__debugbreak();
		}


		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};


		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = sm_RootSig;
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vs->GetBufferPointer(), vs->GetBufferSize());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(ps->GetBufferPointer(), ps->GetBufferSize());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = false;
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;
		if (FAILED(DEVICE->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&sm_PSO))))
		{
			__debugbreak();
		}

		if (vs)
		{
			vs->Release();
			vs = nullptr;
		}
		if (ps)
		{
			ps->Release();
			ps = nullptr;
		}
	}

	m_refCount++;

	return true;
}

void __stdcall PrimitiveRenderData::CreateMesh(void* vertices, uint32 typeSize, uint32 vertexNum, void* indices, uint32 indexNum)
{
	if (FAILED(RESOURCE_MANAGER->CreateVertexBuffer(typeSize, vertexNum, &m_vertexBufferView, &m_vertexBuffer, vertices)))
	{
		__debugbreak();
	}

	if (FAILED(RESOURCE_MANAGER->CreateIndexBuffer(indexNum, &m_indexBufferView, &m_indexBuffer, indices)))
	{
		__debugbreak();
	}

	m_indexCount = indexNum;
}

void __stdcall PrimitiveRenderData::Release()
{
	delete this;
}

void __stdcall PrimitiveRenderData::SetTransformData(TransformRenderData* transformData)
{
	assert(transformData);
	memcpy(&m_transformData, transformData, sizeof(TransformRenderData));
}

void __stdcall PrimitiveRenderData::SetMaterialData(MaterialRenderData* materialData)
{
	assert(materialData);
	memcpy(&m_materialData, materialData, sizeof(MaterialRenderData));
}

void PrimitiveRenderData::CleanUp()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	if (0 == m_refCount)
	{
		return;
	}

	uint32 refCount = --m_refCount;
	if (0 == refCount)
	{
		if (sm_RootSig)
		{
			sm_RootSig->Release();
			sm_RootSig = nullptr;
		}
		if (sm_PSO)
		{
			sm_PSO->Release();
			sm_PSO = nullptr;
		}
	}
}

void PrimitiveRenderData::Draw(ID3D12GraphicsCommandList* cmdList)
{
	// Descriptor Table (Shader visible) 용 
	// Descriptor Allocator 와 Constant Buffer Pool 로 부터 할당받은 descriptor heap 을 해당 Pool 에 Copy 한다.
	ID3D12DescriptorHeap* heap = DESC_POOL->GetDecriptorHeap();

	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = {};
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};

	if (!DESC_POOL->AllocDescriptorTable(cpuHandle, gpuHandle, DESCRIPTOR_COUNT_FOR_DRAW))
	{
		__debugbreak();
	}

	ContantBufferEntry* cbEntry = nullptr;
	{
		// Transform Constant Buffer Data
		ConstantBufferPool* transform_CB_Pool = CONST_MANAGER->GetConstantBuffer(ConstantBufferType::Transform);
		{
			cbEntry = transform_CB_Pool->AllocEntry();
			assert(cbEntry);

			TransformRenderData* transformCB = (TransformRenderData*)cbEntry->sysMem;
			transformCB->world = m_transformData.world.Transpose();

			CD3DX12_CPU_DESCRIPTOR_HANDLE cbvDest(cpuHandle, B1, SRV_DESC_SIZE);
			DEVICE->CopyDescriptorsSimple(1, cbvDest, cbEntry->cpuHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}
	}

	// SRV
	{
		TextureDesc* albedo = (TextureDesc*)m_materialData.albedo;
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvDest(cpuHandle, T0, SRV_DESC_SIZE);
		DEVICE->CopyDescriptorsSimple(1, cbvDest, albedo->srvHanlde, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	// RootSignature 설정
	cmdList->SetGraphicsRootSignature(sm_RootSig);

	// DescriptorHeap 설정
	cmdList->SetDescriptorHeaps(1, &heap);

	// PSO 설정
	cmdList->SetPipelineState(sm_PSO);

	///////////////////////////////////////////////////////////////////////////
	//	Descriptor Table Bind GPU
	///////////////////////////////////////////////////////////////////////////
	{
		cmdList->SetGraphicsRootDescriptorTable(0, GRenderer->m_globalCB_GPU);
		cmdList->SetGraphicsRootDescriptorTable(1, gpuHandle);
	}

	// Input Assemble and Draw call
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	cmdList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	cmdList->IASetIndexBuffer(&m_indexBufferView);
	cmdList->DrawIndexedInstanced(m_indexCount, 1, 0, 0, 0);
}
