#include "stdafx.h"
#include "TownScene.h"

#include "StaticObject.h"
#include "TestPlayer.h"
TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Init()
{
	_ImageManager->AddImage("build_Retaile", PathResources(L"Object/build_Retaile.png"));
	_ImageManager->AddImage("build_Enchant", PathResources(L"Object/build_Enchant.png"));
	_ImageManager->AddImage("build_fountain", PathResources(L"Object/build_fountain.png"));
	_ImageManager->AddImage("build_Top1", PathResources(L"Object/build_Top1.png"));
	_ImageManager->AddImage("build_Shop", PathResources(L"Object/build_Shop.png"));
	_ImageManager->AddImage("build_Board", PathResources(L"Object/build_Board.png"));
	_ImageManager->AddImage("build_Bottom1", PathResources(L"Object/build_Bottom1.png"));
	_ImageManager->AddImage("build_Bottom2", PathResources(L"Object/build_Bottom2.png"));
	_ImageManager->AddImage("build_Forge", PathResources(L"object/build_Forge.png"));
	_ImageManager->AddImage("build_Bottom3", PathResources(L"Object/build_Bottom3.png"));

	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Retaile", Vector2(20, 290)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Enchant", Vector2(50, 1298)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_fountain", Vector2(413, 842)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Top1", Vector2(1092, 236)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Shop", Vector2(1488, 194)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Board", Vector2(1574, 1078)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Bottom1", Vector2(762, 1652)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Bottom2", Vector2(1725, 1545)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Forge", Vector2(2298, 786)));
	_ObjectManager->AddObject(ObjectType::Object, new StaticObject("build_Bottom3", Vector2(2369, 1405)));

	_ObjectManager->AddObject(ObjectType::Object, new TestPlayer);

	_ObjectManager->Init();
	_ObjectManager->ChangeZOrdering(true);

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
