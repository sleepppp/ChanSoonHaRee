#include "stdafx.h"
#include "TestScene1.h"

TestScene1::TestScene1()
{
}


TestScene1::~TestScene1()
{
}

void TestScene1::Init()
{
	_ObjectManager->Init();
}

void TestScene1::Release()
{
	_ObjectManager->Release();
}

void TestScene1::Update()
{
	_ObjectManager->Update();

	if (_Input->GetKeyDown(VK_SPACE))
	{
		_SceneManager->ChangeScene("Test0");
	}
}

void TestScene1::Render()
{
	_ObjectManager->Render();

	RECT rc = { WinSizeX / 2,WinSizeY / 2,WinSizeX / 2 + 100,WinSizeY / 2 + 100 };
	_DXRenderer->DrawRectangle(rc, DefaultBrush::black, false, 5.0f);
}
