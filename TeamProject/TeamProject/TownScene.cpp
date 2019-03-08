#include "stdafx.h"
#include "TownScene.h"


TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Init()
{
	this->SoonInit();
	this->ReeInit();
	this->HaInit();
	this->ChanInit();

	_ObjectManager->Init();
	_ObjectManager->ChangeZOrdering(true);

	_townBackgroundImage = _ImageManager->AddImage("TownBackground", PathResources(L"Town/map.bmp"));
	_Camera->SetMapSize(Vector2((float)_townBackgroundImage->GetWidth(),(float) _townBackgroundImage->GetHeight()));
	_Camera->SetTarget(_ObjectManager->FindObject(ObjectType::Object,"Will"));
}

void TownScene::Release()
{
	_ObjectManager->Release();
}

void TownScene::Update()
{
	_ObjectManager->Update();
}

void TownScene::Render()
{
	_townBackgroundImage->Render(0, 0, Pivot::LEFT_TOP, true);

	_ObjectManager->Render();

}

