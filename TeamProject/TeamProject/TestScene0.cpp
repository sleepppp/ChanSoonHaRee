#include "stdafx.h"
#include "TestScene0.h"

#include "TestAnimation.h"

TestScene0::TestScene0()
{
}


TestScene0::~TestScene0()
{
}

void TestScene0::Init()
{
	TestAnimation* animation = new TestAnimation();
	_ObjectManager->AddObject(ObjectType::Object, animation);

	_ObjectManager->Init();
}

void TestScene0::Release()
{
	_ObjectManager->Release();
}

void TestScene0::Update()
{
	_ObjectManager->Update();

	if (_Input->GetKeyDown(VK_SPACE))
	{
		_SceneManager->ChangeScene("Test1");
	}
}

void TestScene0::Render()
{
	_ObjectManager->Render();
}
