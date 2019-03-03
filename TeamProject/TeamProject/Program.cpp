#include "stdafx.h"
#include "Program.h"

#include "MainScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
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
	
	LoadingScene* loadScene = new LoadingScene;
	loadScene->SetNextSceneName("MainScene");
	loadScene->SetLoadingFunc([this]() {_SceneManager->FindScene("MainScene")->Init(); });
	_SceneManager->AddScene("LoadingScene", loadScene);

	_SceneManager->LoadScene("TitleScene");
}

void Program::Release()
{
	
}

void Program::Update()
{
	_SceneManager->Update();
}

void Program::Render()
{
	//렌더링 시작에 앞서서 스왑체인 버퍼를 한번 Clear해주고 GPU에 바인딩 
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	//Direct2D 렌더타겟도 바인딩 여기까지 왔으면 렌더링 해도 된다. 
	_DXRenderer->Direct2DBeginDraw();
	{
		{
			_SceneManager->Render();
		}
		_TimeManager->Render();
	}
	//Direct2D 렌더타겟 언바인딩 
	_DXRenderer->Direct2DEndDraw();
	//GUI 시스템 렌더링 (DirectX11 기반으로 렌더링 됌) 
	ImGui::Render();
	//모든 렌더링이 끝났으면 스왑체인 Present로 백버퍼와 전면 버퍼 교환해서 화면에 출력
	_DXRenderer->PresentSwapChain();
}
