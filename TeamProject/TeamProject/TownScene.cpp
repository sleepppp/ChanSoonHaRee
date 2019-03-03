#include "stdafx.h"
#include "TownScene.h"

#include "TownObject.h"
TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Init()
{
	_ImageManager->AddImage("build_Retaile", PathResources(L"Object/build_Retaile.png"));

	_ObjectManager->AddObject(ObjectType::Object, new TownObject("build_Retaile", Vector2(20, 290)));
	
	_ObjectManager->Init();

	_townBackgroundImage = _ImageManager->AddImage("TownBackground", PathResources(L"Town/map.bmp"));
	_Camera->SetMapSize(Vector2((float)_townBackgroundImage->GetWidth(),(float) _townBackgroundImage->GetHeight()));
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
