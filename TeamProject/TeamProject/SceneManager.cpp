#include "stdafx.h"
#include "SceneManager.h"

#include "SceneBase.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager* SceneManager::GetSingleton()
{
	if (_instance == nullptr)
	{
		_instance = new SceneManager;
	}
	return _instance;
}

void SceneManager::DeleteSingleton()
{
	if (_instance)
	{
		SafeDelete(_instance);
	}
}


SceneManager::SceneManager()
	:_nowScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	SceneIter iter = _sceneList.begin();
	for (; iter != _sceneList.end(); ++iter)
	{
		iter->second->Release();
		SafeDelete(iter->second);
	}
	_sceneList.clear();
}



void SceneManager::Update()
{
	if (_nowScene != nullptr)
		_nowScene->Update();

}

void SceneManager::Render()
{
	if (_nowScene != nullptr)
		_nowScene->Render();
}

void SceneManager::AddScene(string name, SceneBase * scene)
{
	this->_sceneList.insert(make_pair(name, scene));
}

void SceneManager::ChangeScene(string name)
{
	SceneIter iter = _sceneList.find(name);
	if (iter != _sceneList.end())
	{
		if (iter->second != nullptr)
			iter->second->Release();

		_nowScene = iter->second;
		_nowScene->Init();
	}
}
