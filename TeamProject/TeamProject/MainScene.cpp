#include "stdafx.h"
#include "MainScene.h"

void MainScene::Init()
{
	this->SoonInit();
	this->ReeInit();
	this->ChanInit();
	this->HaInit();

	_ObjectManager->Init();
}

void MainScene::Release()
{
	_ObjectManager->Release();
}

void MainScene::Update()
{
	_ObjectManager->Update();
}

void MainScene::Render()
{
	_ObjectManager->Render();
}
