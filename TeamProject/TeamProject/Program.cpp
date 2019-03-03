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
	if (_Input->GetKeyDown(VK_F5))
		_isDebug = !_isDebug;

	_SceneManager->Update();
}

void Program::Render()
{
	//������ ���ۿ� �ռ��� ����ü�� ���۸� �ѹ� Clear���ְ� GPU�� ���ε� 
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	//Direct2D ����Ÿ�ٵ� ���ε� ������� ������ ������ �ص� �ȴ�. 
	_DXRenderer->Direct2DBeginDraw();
	{
		{
			_SceneManager->Render();
		}
		_TimeManager->Render();
	}
	//Direct2D ����Ÿ�� ����ε� 
	_DXRenderer->Direct2DEndDraw();
	//GUI �ý��� ������ (DirectX11 ������� ������ ��) 
	ImGui::Render();
	//��� �������� �������� ����ü�� Present�� ����ۿ� ���� ���� ��ȯ�ؼ� ȭ�鿡 ���
	_DXRenderer->PresentSwapChain();
}
