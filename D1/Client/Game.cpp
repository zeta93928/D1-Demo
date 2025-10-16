#include "pch.h"
#include "Game.h"

#include "../Engine/MeshAsset.h"
#include "../Engine/MaterialAsset.h"
#include "../Engine/TextureAsset.h"
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
		MeshAssetRef mesh1 = MakeShared<MeshAsset>();
		mesh1->GenerateCube();

		MaterialAssetRef material1 = MakeShared<MaterialAsset>();
		{
			TextureAssetRef tex1 = MakeShared<TextureAsset>();
			tex1->Load(L"../Assets/Textures/Box.jpg");

			material1->SetAlbedoMap(tex1);
		}

		m_meshActor = MakeShared<Actor>();
		m_meshActor->GetOrAddSceneComponent();
		m_meshActor->AddComponent(MakeShared<StaticMeshComponent>());
		{
			m_meshActor->GetStaticMeshComponent()->SetMeshAsset(mesh1);
			m_meshActor->GetStaticMeshComponent()->SetMaterialAsset(material1);
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
