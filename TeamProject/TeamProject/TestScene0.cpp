#include "stdafx.h"
#include "TestScene0.h"

#include "TestAnimation.h"

TestScene0::TestScene0()
{
}


TestScene0::~TestScene0()
{
}
/***********************************************
## Init ##
¾ÀÀÌ ¹Ù²ğ ¶§¸¶´Ù È£Ãâ
************************************************/
void TestScene0::Init()
{
	TestAnimation* animation = new TestAnimation();
	_ObjectManager->AddObject(ObjectType::Object, animation);

	_ObjectManager->Init();
}
/***********************************************
## Relase ##
¾ÀÀÌ ¹Ù²ğ ¶§¸¶´Ù È£Ãâ
************************************************/
void TestScene0::Release()
{
	_ObjectManager->Release();
}
/***********************************************
## Update ##
************************************************/
void TestScene0::Update()
{
	_ObjectManager->Update();

	if (_Input->GetKeyDown(VK_SPACE))
	{
		_SceneManager->ChangeScene("Test1");
	}
}
/***********************************************
## Render ##
************************************************/
void TestScene0::Render()
{
	_ObjectManager->Render();
}
