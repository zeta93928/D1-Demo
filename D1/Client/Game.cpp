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

bool Game::Init()
{
	// Camera Actor
	{
		m_cameraActor = MakeShared<Actor>();
		m_cameraActor->GetOrAddSceneComponent()->SetPosition(Vector3(0.f, 0.f, -10.f));
		m_cameraActor->AddComponent(MakeShared<CameraComponent>());
	}

	// Mesh Actor
	{
		MeshAssetRef m1 = MakeShared<MeshAsset>();
		m1->GenerateCube();

		m_meshActor = MakeShared<Actor>();
		m_meshActor->GetOrAddSceneComponent();
		m_meshActor->AddComponent(MakeShared<StaticMeshComponent>());
		{
			m_meshActor->GetStaticMeshComponent()->SetMeshAsset(m1);
		}
	}

	return true;
}
 
void Game::Update()
{
	m_cameraActor->Update();
	m_meshActor->Update();
}

void Game::Render()
{
	
}

void Game::Release()
{
	delete this;
}
