#include "stdafx.h"
#include "Program.h"


Program::Program()
{
}


Program::~Program()
{
}

void Program::Init()
{
}

void Program::Release()
{
}

void Program::Update()
{
}

void Program::Render()
{
	_DXRenderer->BindSwapchainRenderTargetAndClear();
	_DXRenderer->Direct2DBeginDraw();
	{
		_Time->Render();
		{
			//���⼭ ���� ������ ó��
		}
	}
	_DXRenderer->Direct2DEndDraw();
	ImGui::Render();
	_DXRenderer->PresentSwapChain();
}
