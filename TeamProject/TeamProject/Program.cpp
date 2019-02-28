#include "stdafx.h"
#include "Program.h"

#include "MainScene.h"
Program::Program()
{

	
}


Program::~Program()
{
}

void Program::Init()
{
	_SceneManager->AddScene("MainScene", new MainScene);
	_SceneManager->LoadScene("MainScene");
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
	//������ ���ۿ� �ռ��� ����ü�� ���۸� �ѹ� Clear���ְ� GPU�� ���ε� 
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	//Direct2D ����Ÿ�ٵ� ���ε� ������� ������ ������ �ص� �ȴ�. 
	_DXRenderer->Direct2DBeginDraw();
	{
		_TimeManager->Render();
		{
			_SceneManager->Render();
		}
	}
	//Direct2D ����Ÿ�� ����ε� 
	_DXRenderer->Direct2DEndDraw();
	//GUI �ý��� ������ (DirectX11 ������� ������ ��) 
	ImGui::Render();
	//��� �������� �������� ����ü�� Present�� ����ۿ� ���� ���� ��ȯ�ؼ� ȭ�鿡 ���
	_DXRenderer->PresentSwapChain();
}
