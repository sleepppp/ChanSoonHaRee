#include "stdafx.h"
#include "SceneManager.h"
#include "SceneBase.h"
SingletonCpp(SceneManager)
/***************************************************************
## SceneManager ##
***************************************************************/
SceneManager::SceneManager()
	:nowScene(nullptr)
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
/***************************************************************
## AddScene ##
@@ string name : �� �̸� 
@@ �ٲ� ��
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
@@ string name : ã�� ���̸� 
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
@@ string name : �ٲ� ���̸� 
@@ bool init : �ٲ� �� Init�� ����
***************************************************************/
void SceneManager::LoadScene(string name,bool init)
{
	SceneBase* findScene = this->FindScene(name);
	if (findScene != nullptr)
	{
		if (nowScene)
			nowScene->Release();
		
		nowScene = findScene;
		
		if(init)
			nowScene->Init();
	}
}
