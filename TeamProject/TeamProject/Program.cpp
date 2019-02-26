#include "stdafx.h"
#include "Program.h"

#include "TestScene0.h"
#include "TestScene1.h"
#include "ChanScene.h"
#include "PlayerTestScene.h"

#include "SaveLoadModule.h"
//���α׷� �����ڿ��� �÷��̾�� ���ʹ� ��ü�� �����ؼ� ������Ʈ �Ŵ�����
//����Ѵ�. 
Program::Program()
{

	
}


Program::~Program()
{
}

void Program::Init()
{
	TestScene0* scene = new TestScene0;
	_SceneManager->AddScene("Test0", scene);
	TestScene1* scene1 = new TestScene1;
	_SceneManager->AddScene("Test1", scene1);

	ChanScene* chanScene = new ChanScene;
	_SceneManager->AddScene("ChanScene", chanScene);

	PlayerTestScene* playerScene = new PlayerTestScene;
	_SceneManager->AddScene("PlayerTestScene", playerScene);

	_SceneManager->ChangeScene("PlayerTestScene");
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
		_Time->Render();
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
