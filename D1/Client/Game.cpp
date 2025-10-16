#include "pch.h"
#include "Game.h"

#include "../Engine/MeshAsset.h"
#include "../Engine/MaterialAsset.h"
#include "../Engine/TextureAsset.h"
#include "../Engine/Actor.h"
#include "../Engine/PrimitiveComponent.h"

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
		m_cameraActor->GetOrAddSceneComponent()->SetPosition(Vector3(0.f, 2.f, -10.f));
		m_cameraActor->AddComponent(MakeShared<CameraComponent>());
	}

	int32 test_num = 50;

	// Mesh Actor
	ActorRef meshActor = nullptr;
	{
		MeshAssetRef mesh1 = MakeShared<MeshAsset>();
		mesh1->GenerateCube();

		MaterialAssetRef material1 = MakeShared<MaterialAsset>();
		{
			TextureAssetRef tex1 = MakeShared<TextureAsset>();
			tex1->Load(L"../Assets/Textures/Box.jpg");

			material1->SetAlbedoMap(tex1);
		}

		for (uint32 r = 0; r < test_num; r++)
		{
			for (uint32 c = 0; c < test_num; c++)
			{
				meshActor = MakeShared<Actor>();
				meshActor->GetOrAddSceneComponent()->SetPosition(Vector3(-test_num + (float)c * 2.f, 0.f, 0.f + (float)r * 5.f));
				meshActor->AddComponent(MakeShared<PrimitiveComponent>());
				{
					meshActor->GetPrimitiveComponent()->SetMeshAsset(mesh1);
					meshActor->GetPrimitiveComponent()->SetMaterialAsset(material1);
				}

				m_meshActors.push_back(meshActor);
			}
		}
	}

	return true;
}
 
void Game::Update()
{
	m_cameraActor->Update();
	
	for (auto& actor : m_meshActors)
	{
		actor->Update();
	}
}

void Game::Render()
{
	
}

void Game::Release()
{
	delete this;
}
