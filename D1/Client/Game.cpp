#include "pch.h"
#include "Game.h"

#include "../Engine/MeshAsset.h"
#include "../Engine/Actor.h"
#include "../Engine/StaticMeshComponent.h"

Game::Game()
{
}

Game::~Game()
{
	
}

bool __stdcall Game::Init()
{
	// Mesh Asset »ý¼º
	MeshAssetRef m1 = MakeShared<MeshAsset>();
	m1->GenerateQuad();

	m_actor = MakeShared<Actor>();
	m_actor->AddComponent(MakeShared<StaticMeshComponent>());
	{
		m_actor->GetStaticMeshComponent()->SetMeshAsset(m1);
	}

	return true;
}
 
void __stdcall Game::Update()
{
	m_actor->Update();
}

void __stdcall Game::Render()
{
	
}

void __stdcall Game::Release()
{
	delete this;
}
