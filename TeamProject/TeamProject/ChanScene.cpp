#include "stdafx.h"
#include "ChanScene.h"


ChanScene::ChanScene()
{
}


ChanScene::~ChanScene()
{
}

void ChanScene::Init()
{


	_ObjectManager->Init();
}

void ChanScene::Release()
{
	_ObjectManager->Release();
}

void ChanScene::Update()
{
	_ObjectManager->Update();
}

void ChanScene::Render()
{
	_ObjectManager->Render();
}
