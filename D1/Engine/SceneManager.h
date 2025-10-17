#pragma once

#include "SceneBase.h"

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);
public:
	void CleanUp();
	void Update();

	template<typename T>
	void ChangeScene(SharedPtr<T> scene)
	{
		m_currentScene = scene;
		m_currentScene->Start();
	}

private:
	SceneBaseRef m_currentScene;
};

