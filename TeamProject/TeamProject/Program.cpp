#include "stdafx.h"
#include "Program.h"
#include "Enemy.h"
#include "Player.h"

//프로그램 생성자에서 플레이어와 에너미 객체를 생성해서 오브잭트 매니져에
//등록한다. 
Program::Program()
{
	Player* player = new Player;
	_ObjectManager->AddObject(player);

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			Enemy* enemy;
			Vector2 position = Vector2(((WinSizeX / 2) - 200)+ (i * 100), 100 + (j * 100));
			enemy = new Enemy(position);
			_ObjectManager->AddObject(enemy);
		}
	}
	
}


Program::~Program()
{
}


void Program::Init()
{
	//모든 오브젝트 Init()해준다
	_ObjectManager->Init();
}

void Program::Release()
{
	//모든 오브젝트 Relase및 할당해제 해준다. 
	_ObjectManager->Release();
}

void Program::Update()
{
	//모든 오브젝트 업데이트 해준다. 
	_ObjectManager->Update();
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
			//여기서 메인 렌더링 처리
			_ObjectManager->Render();
			//여기까지
		}
	}
	//Direct2D 렌더타겟 언바인딩 
	_DXRenderer->Direct2DEndDraw();
	//GUI 시스템 렌더링 (DirectX11 기반으로 렌더링 됌) 
	ImGui::Render();
	//모든 렌더링이 끝났으면 스왑체인 Present로 백버퍼와 전면 버퍼 교환해서 화면에 출력
	_DXRenderer->PresentSwapChain();
}
