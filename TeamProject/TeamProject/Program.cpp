#include "stdafx.h"
#include "Program.h"

#include "TestScene0.h"
#include "TestScene1.h"
#include "ChanScene.h"
#include "PlayerTestScene.h"

#include "SaveLoadModule.h"
//프로그램 생성자에서 플레이어와 에너미 객체를 생성해서 오브잭트 매니져에
//등록한다. 
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
	//렌더링 시작에 앞서서 스왑체인 버퍼를 한번 Clear해주고 GPU에 바인딩 
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	//Direct2D 렌더타겟도 바인딩 여기까지 왔으면 렌더링 해도 된다. 
	_DXRenderer->Direct2DBeginDraw();
	{
		_Time->Render();
		{
			_SceneManager->Render();
		}
	}
	//Direct2D 렌더타겟 언바인딩 
	_DXRenderer->Direct2DEndDraw();
	//GUI 시스템 렌더링 (DirectX11 기반으로 렌더링 됌) 
	ImGui::Render();
	//모든 렌더링이 끝났으면 스왑체인 Present로 백버퍼와 전면 버퍼 교환해서 화면에 출력
	_DXRenderer->PresentSwapChain();
}
