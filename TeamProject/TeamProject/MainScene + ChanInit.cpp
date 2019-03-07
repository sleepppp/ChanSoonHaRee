#include "stdafx.h"
#include "MainScene.h"
#include "MoveItem.h"
#include "Inventory.h"
#include "UIWeaponAndBag.h"

#include "TestDeadman.h"
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
void MainScene::ChanInit()
{
	/**********************
			  UI
	***********************/
	//메인 인벤토리 이미지 
	_ImageManager->AddImage("InventoryWindow", L"../Resources/UI/newInventory.png", false);

	//UI 무기 스왑
	_ImageManager->AddFrameImage("UI_WeaponSwap", L"../Resources/UI/UI_WeaponSwap.png", 4, 1, false);
	//UI 가방
	_ImageManager->AddImage("UI_Bag", L"../Resources/UI/UI_Bag.png", false);

	/**********************
			아이템
	***********************/
	//나뭇가지 이미지
	_ImageManager->AddImage("item_brench", L"../Resources/Item/item_brench.png", false);


	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
	for (UINT i = 0; i < 15; ++i) 
	{
		_ObjectManager->AddObject(ObjectType::Object, new MoveItem("brench", Vector2(Math::Random(0, WinSizeX), Math::Random(0, WinSizeY))));
	}
	
	_ObjectManager->AddObject(ObjectType::UI, new UIWeaponAndBag);

	//for (UINT i = 0; i < 10; ++i)
	//{
	//	Vector2 randomPos = Vector2(Math::Random(0,WinSizeX), Math::Random(0,WinSizeY));
	//	Vector2 randomSize= Vector2(Math::Random(50,100), Math::Random(50,100));
	//	_ObjectManager->AddObject(ObjectType::Object, new TestDeadman(randomPos,randomSize));
	//}
}	//