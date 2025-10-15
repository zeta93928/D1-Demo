#include "pch.h"
#include "StaticMeshRenderData.h"

ID3D12RootSignature* StaticMeshRenderData::sm_RootSig = nullptr;
ID3D12PipelineState* StaticMeshRenderData::sm_PSO = nullptr;
DWORD StaticMeshRenderData::m_dwInitRefCount = 0;

StaticMeshRenderData::StaticMeshRenderData()
{
}

StaticMeshRenderData::~StaticMeshRenderData()
{
	CleanUp();
}

bool StaticMeshRenderData::Init()
{
	// 이미 StaicMesh 가 instance 화 되어있다면 공유리소스를 재생성하지 않고, 사용 카운트만 올려주고 리턴한다.
	if (m_dwInitRefCount)
	{
		m_dwInitRefCount++;

		return true;
	}


	// @TODO:
	// 해당 구조를 Shader Reflection 을 통해 통합


	// Create Root Signature
	{
		ID3DBlob* signature = nullptr;
		ID3DBlob* error = nullptr;

		CD3DX12_DESCRIPTOR_RANGE ranges[1] = {};
		ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);	// b0 : Constant Buffer View
		// ranges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);	// t0 : Shader Resource View(Tex)

		CD3DX12_ROOT_PARAMETER rootParameters[1] = {};
		rootParameters[0].InitAsDescriptorTable(_countof(ranges), ranges, D3D12_SHADER_VISIBILITY_ALL);

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
		ID3DBlob* pVertexShader = nullptr;
		ID3DBlob* pPixelShader = nullptr;


#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif
		if (FAILED(D3DCompileFromFile(L"../Shaders/Default.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &pVertexShader, nullptr)))
		{
			__debugbreak();
		}
		if (FAILED(D3DCompileFromFile(L"../Shaders/Default.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pPixelShader, nullptr)))
		{
			__debugbreak();
		}


		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};


		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = sm_RootSig;
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		if (FAILED(DEVICE->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&sm_PSO))))
		{
			__debugbreak();
		}

		if (pVertexShader)
		{
			pVertexShader->Release();
			pVertexShader = nullptr;
		}
		if (pPixelShader)
		{
			pPixelShader->Release();
			pPixelShader = nullptr;
		}
	}

	m_dwInitRefCount++;
	
	return true;
}

void __stdcall StaticMeshRenderData::CreateMesh(void* vertices, uint32 typeSize, uint32 vertexNum, void* indices, uint32 indexNum)
{
	if (FAILED(RESOURCE->CreateVertexBuffer(typeSize, vertexNum, &m_vertexBufferView, &m_vertexBuffer, vertices)))
	{
		__debugbreak();
	}

	if (FAILED(RESOURCE->CreateIndexBuffer(indexNum, &m_indexBufferView, &m_indexBuffer, indices)))
	{
		__debugbreak();
	}

	m_indexCount = indexNum;
}

void __stdcall StaticMeshRenderData::Release()
{
	delete this;
}

void StaticMeshRenderData::CleanUp()
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

	
	if (0 == m_dwInitRefCount)
	{
		return;
	}

	uint32 refCount = --m_dwInitRefCount;
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

void StaticMeshRenderData::Draw(ID3D12GraphicsCommandList* pCommandList)
{
	// set RootSignature
	pCommandList->SetGraphicsRootSignature(sm_RootSig);

	pCommandList->SetPipelineState(sm_PSO);
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pCommandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	pCommandList->IASetIndexBuffer(&m_indexBufferView);
	pCommandList->DrawIndexedInstanced(m_indexCount, 1, 0, 0, 0);
}
