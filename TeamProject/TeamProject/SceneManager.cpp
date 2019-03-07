#include "stdafx.h"
#include "SceneManager.h"
#include "SceneBase.h"
SingletonCpp(SceneManager)
/***************************************************************
## SceneManager ##
***************************************************************/
SceneManager::SceneManager()
	:nowScene(nullptr), loadFunc(nullptr)
{
}
/***************************************************************
## ~SceneManager ##
***************************************************************/
SceneManager::~SceneManager()
{
	SceneIter iter = sceneList.begin();
	for (; iter != sceneList.end(); ++iter)
	{
		iter->second->Release();
		SafeDelete(iter->second);
	}
	sceneList.clear();
}

/***************************************************************
## Update ##
***************************************************************/
void SceneManager::Update()
{
	if (nowScene)
		nowScene->Update();
}
/***************************************************************
## Render ##
***************************************************************/
void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}
void SceneManager::SceneQueue()
{
	if (loadFunc != nullptr)
	{
		loadFunc(loadSceneName, bInit);
		loadFunc = nullptr;
	}
}
/***************************************************************
## AddScene ##
@@ string name : ¾À ÀÌ¸§ 
@@ ¹Ù²Ü ¾À
***************************************************************/
void SceneManager::AddScene(string name, SceneBase * scene)
{
	SceneIter iter = sceneList.find(name);
	if (iter != sceneList.end())
		return;
	this->sceneList.insert(make_pair(name, scene));
}
/***************************************************************
## FindScene ##
@@ string name : Ã£À» ¾ÀÀÌ¸§ 
***************************************************************/
SceneBase * SceneManager::FindScene(string name)
{
	SceneIter iter = sceneList.find(name);
	if (iter != sceneList.end())
		return iter->second;

	return nullptr;
}
/***************************************************************
## LoadScene ##
@@ string name : ¹Ù²Ü ¾ÀÀÌ¸§ 
@@ bool init : ¹Ù²Ü ¾À InitÇÒ ¿©ºÎ
***************************************************************/
void SceneManager::ChangeScene(string name, bool init)
{
	SceneBase* findScene = this->FindScene(name);
	if (findScene != nullptr)
	{
		if (nowScene)
			nowScene->Release();

		nowScene = findScene;

		if (init)
			nowScene->Init();
	}
}

void SceneManager::LoadScene(string name,bool init)
{
	this->loadFunc = bind(&SceneManager::ChangeScene, this, name, init);
	this->loadSceneName = name;
	this->bInit = init;
}
