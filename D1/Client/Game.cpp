#include "pch.h"
#include "Game.h"

#include "../Engine/MeshAsset.h"
#include "../Engine/MaterialAsset.h"
#include "../Engine/TextureAsset.h"
#include "../Engine/Actor.h"
#include "../Engine/PrimitiveComponent.h"


#include "SceneInGame.h"

Game::Game()
{
}

Game::~Game()
{
	SceneManager::Get().CleanUp();
}

bool Game::Init()
{
	SceneInGameRef sceneInGame = MakeShared<SceneInGame>();
	SceneManager::Get().ChangeScene(sceneInGame);

	// Camera Actor
	{
		ActorRef cameraActor = MakeShared<Actor>();
		cameraActor->GetOrAddSceneComponent()->SetPosition(Vector3(0.f, 2.f, -10.f));
		cameraActor->AddComponent(MakeShared<CameraComponent>());

		sceneInGame->Add(cameraActor);
	}

	int32 test_num = 100;

	// Mesh Actor
	{
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

			for (uint32 r = 0; r < (uint32)test_num; r++)
			{
				for (uint32 c = 0; c < (uint32)test_num; c++)
				{
					meshActor = MakeShared<Actor>();
					meshActor->GetOrAddSceneComponent()->SetPosition(Vector3(-test_num + (float)c * 2.f, 0.f, 0.f + (float)r * 5.f));
					meshActor->AddComponent(MakeShared<PrimitiveComponent>());
					{
						meshActor->GetPrimitiveComponent()->SetMeshAsset(mesh1);
						meshActor->GetPrimitiveComponent()->SetMaterialAsset(material1);
					}

					sceneInGame->Add(meshActor);
				}
			}
		}
	}

	return true;
}
 
void Game::Update()
{
	SceneManager::Get().Update();
}

void Game::Render()
{
}

void Game::Release()
{
	delete this;
}
