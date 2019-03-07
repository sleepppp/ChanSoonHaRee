#include "stdafx.h"
#include "MainScene.h"
#include "GameObject.h"
#include "Inventory.h"
#include "LoadingScene.h"

void MainScene::Init()
{
	this->SoonInit();
	this->ReeInit();
	this->ChanInit();
	this->HaInit();

	_ObjectManager->Init();

	_Camera->SetTarget(_ObjectManager->FindObject(ObjectType::Object, "Will"));
	_Camera->SetMapSize(Vector2(3000, 3000));

}

void MainScene::Release()
{
	_ObjectManager->Release();
}

void MainScene::Update()
{
	_ObjectManager->Update();

	if (_Input->GetKeyDown(VK_RETURN))
	{
		LoadingScene* loadingScene = dynamic_cast<LoadingScene*>(_SceneManager->FindScene("LoadingScene"));
		if (loadingScene != nullptr)
		{
			loadingScene->SetNextSceneName("TownScene");
			loadingScene->SetLoadingFunc([]() {_SceneManager->FindScene("TownScene")->Init(); });
			_SceneManager->LoadScene("LoadingScene");
		}
	}
}

void MainScene::Render()
{
	_ObjectManager->Render();
}
