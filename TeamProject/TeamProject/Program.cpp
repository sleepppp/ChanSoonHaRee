#include "stdafx.h"
#include "Program.h"

#include "MainScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "TownScene.h"

Program::Program()
{
	
}

Program::~Program()
{
}

void Program::Init()
{
	_SceneManager->AddScene("MainScene", new MainScene);
	_SceneManager->AddScene("TitleScene", new TitleScene);
	_SceneManager->AddScene("TownScene", new TownScene);

	LoadingScene* loadScene = new LoadingScene;
	loadScene->SetNextSceneName("TownScene");
	loadScene->SetLoadingFunc([this]() {_SceneManager->FindScene("TownScene")->Init(); });
	_SceneManager->AddScene("LoadingScene", loadScene);

	_SceneManager->LoadScene("TitleScene");
}

void Program::Release()
{
	
}

void Program::Update()
{
	if (_Input->GetKeyDown(VK_F1))
		_isDebug = !_isDebug;

	_SceneManager->Update();
}

void Program::Render()
{
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	_DXRenderer->Direct2DBeginDraw();
	{
		_SceneManager->Render();
		_TimeManager->Render();
	}
	_DXRenderer->Direct2DEndDraw();
	ImGui::Render();
	_DXRenderer->PresentSwapChain();

}
