cbuffer GlobalBuffer : register(b0)
{
    matrix view;
    matrix proj;
    matrix viewProj;
    matrix viewInv;
};

Texture2D AlbedoMap : register(t0);
SamplerState PointWrapSS : register(s0);

struct VertexTextureNormalTangent
{
    float4 posModel : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    
    matrix world : WORLD;
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

    output.posProj = mul(input.posModel, input.world);
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
    return AlbedoMap.Sample(PointWrapSS, input.uv);
}