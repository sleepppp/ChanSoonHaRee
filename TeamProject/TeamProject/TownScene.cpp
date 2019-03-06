#include "stdafx.h"
#include "TownScene.h"

#include "StaticObject.h"
#include "TestPlayer.h"
#include "DebugCollider.h"
#include "FrameObject.h"
#include "Tree.h"

TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Init()
{
	_ImageManager->AddImage("Shadow", PathResources(L"Object/Shadow.png"));
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
	_ImageManager->AddFrameImage("tree", PathResources(L"Object/tree.png"),4,1);

	StaticObject* tempObject = nullptr;
	tempObject = new StaticObject("build_Retaile", Vector2(20, 290));
	tempObject->SetCollisionRect({314,312,650,676});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Enchant", Vector2(50, 1298));
	tempObject->SetCollisionRect({ 85,1580,641,2050});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_fountain", Vector2(413, 842));
	tempObject->SetCollisionRect({410,872,521,965});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Top1", Vector2(1092, 236));
	tempObject->SetCollisionRect({ 1100,306,1417,622 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Shop", Vector2(1620, 194));
	tempObject->SetCollisionRect({1619,303,2148,626});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Board", Vector2(1574, 1078));
	tempObject->SetCollisionRect({1599,1100,1759,1214});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom1", Vector2(762, 1652));
	tempObject->SetCollisionRect({909,1678,1229,1981});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom2", Vector2(1725, 1545));
	tempObject->SetCollisionRect({1737,1619,2057,1927});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Forge", Vector2(2298, 786));
	tempObject->SetCollisionRect({2328,876,2934,1270});
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom3", Vector2(2369, 1405));
	_ObjectManager->AddObject(ObjectType::Object, tempObject);
	
	Tree* tempFrameObject = nullptr;

	tempFrameObject = new Tree(Vector2(912,306));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(912, 606));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(442, 306));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(990, 1000));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);
	
	tempFrameObject = new Tree(Vector2(990, 1460));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);
	//2014,1000
	tempFrameObject = new Tree(Vector2(2014, 1000));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(2014, 1460));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);
	//2368 556
	tempFrameObject = new Tree(Vector2(2368, 556));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);
	//2201,1868
	tempFrameObject = new Tree(Vector2(2201, 1868));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	//_ObjectManager->AddObject(ObjectType::UI, new DebugCollider);

	//TestPlayer* player = new TestPlayer;
	//_ObjectManager->AddObject(ObjectType::Object, player);

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

