#include "stdafx.h"
#include "MainScene.h"
#include "GameObject.h"
#include "Inventory.h"

void MainScene::Init()
{
	this->SoonInit();
	this->ReeInit();
	this->ChanInit();
	this->HaInit();

	_ObjectManager->Init();

	_Camera->SetTarget(_ObjectManager->FindObject(ObjectType::Object, "Will"));
	_Camera->SetMapSize(Vector2(3000, 3000));
}

void MainScene::Release()
{
	_ObjectManager->Release();
}

void MainScene::Update()
{
	//if (_Input->GetKeyDown('I')) 
	//{
	//	GameObject* inven = _ObjectManager->FindObject(ObjectType::Object, "Inventory");
	//	if(inven)
	//		inven->SetActive(true);
	//}
	_ObjectManager->Update();
}

void MainScene::Render()
{
	_ObjectManager->Render();
}
