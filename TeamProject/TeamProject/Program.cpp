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
			//여기서 메인 렌더링 처리
		}
	}
	_DXRenderer->Direct2DEndDraw();
	ImGui::Render();
	_DXRenderer->PresentSwapChain();
}
