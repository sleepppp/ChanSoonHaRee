#include "stdafx.h"
#include "PlayerTestScene.h"

#include "TestPlayer.h"
#include "TestEnemy.h"
PlayerTestScene::PlayerTestScene()
{
}


PlayerTestScene::~PlayerTestScene()
{
}

void PlayerTestScene::Init()
{

	_ObjectManager->AddObject(ObjectType::Object, new TestEnemy(Vector2(30, 30), Vector2(50, 50), Pivot::CENTER, 100.0f));
	_ObjectManager->AddObject(ObjectType::Object, new TestPlayer);

	_ObjectManager->Init();
}

void PlayerTestScene::Release()
{
	_ObjectManager->Release();
}

void PlayerTestScene::Update()
{
	_ObjectManager->Update();
	if(_Input->GetKeyDown(VK_F1))
		_ObjectManager->AddObject(ObjectType::Object, new TestEnemy(Vector2(30, 30), Vector2(50, 50), Pivot::CENTER, 100.0f));
}

void PlayerTestScene::Render()
{
	_ObjectManager->Render();
}
