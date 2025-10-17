#include "pch.h"
#include "SceneManager.h"

void SceneManager::Update()
{
	if (m_currentScene == nullptr)
	{
		return;
	}

	m_currentScene->Update();
	m_currentScene->LateUpdate();
}

void SceneManager::CleanUp()
{
	m_currentScene = nullptr;
}