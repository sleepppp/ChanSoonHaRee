#include "stdafx.h"
#include "Program.h"

#include "Player.h"
#include "Enemy.h"

//���α׷� �����ڿ��� �÷��̾�� ���ʹ� ��ü�� �����ؼ� ������Ʈ �Ŵ�����
//����Ѵ�. 
Program::Program()
{
	Player* player = new Player;
	_ObjectManager->AddObject(player);
	Enemy* enemy = new Enemy;
	_ObjectManager->AddObject(enemy);
}


Program::~Program()
{
}


void Program::Init()
{
	//��� ������Ʈ Init()���ش�
	_ObjectManager->Init();
}

void Program::Release()
{
	//��� ������Ʈ Relase�� �Ҵ����� ���ش�. 
	_ObjectManager->Release();
}

void Program::Update()
{
	//��� ������Ʈ ������Ʈ ���ش�. 
	_ObjectManager->Update();
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
			//���⼭ ���� ������ ó��
			_ObjectManager->Render();
			//�������
		}
	}
	//Direct2D ����Ÿ�� ����ε� 
	_DXRenderer->Direct2DEndDraw();
	//GUI �ý��� ������ (DirectX11 ������� ������ ��) 
	ImGui::Render();
	//��� �������� �������� ����ü�� Present�� ����ۿ� ���� ���� ��ȯ�ؼ� ȭ�鿡 ���
	_DXRenderer->PresentSwapChain();
}
