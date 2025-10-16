cbuffer GlobalBuffer : register(b0)
{
    matrix view;
    matrix proj;
    matrix viewProj;
    matrix viewInv;
};

cbuffer TransformBuffer : register(b1)
{
    matrix world;
}

struct VertexTextureNormalTangent
{
    float4 posModel : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct MeshOutput
{
    float4 posProj : SV_POSITION;
    float3 posWorld : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

MeshOutput VSMain(VertexTextureNormalTangent input)
{
    MeshOutput output;

    output.posProj = mul(input.posModel, world);
    output.posWorld = output.posProj.xyz;
    
    output.posProj = mul(output.posProj, view);
    output.posProj = mul(output.posProj, proj);
    
    output.uv = input.uv;
    output.normal = input.normal;
    output.tangent = input.tangent;

    return output;
}

float4 PSMain(MeshOutput input) : SV_TARGET
{
    return float4(0, 0, 0, 0);
}