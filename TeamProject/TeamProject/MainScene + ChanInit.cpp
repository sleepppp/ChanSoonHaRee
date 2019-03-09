#include "stdafx.h"
#include "MainScene.h"
#include "MoveItem.h"
#include "Inventory.h"
#include "UIWeaponAndBag.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_Boss.h"
#include "TestDeadman.h"
#include "ProgressBar.h"
#include "Program.h"
#include "UIMoneyPoket.h"
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ


void Program::LoadResourceChan()
{
}

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
	//UI 프로그래스 바
	//_ImageManager->AddFrameImage("hpBar1", L"../Resouces/UI/hpBar", 1, 6, false);
	//_ImageManager->AddFrameImage("hpBar2", L"../Resouces/UI/hpBar", 1, 6, false);

	//UI 돈 주머니
	_ImageManager->AddImage("moneyPoket", L"../Resources/UI/moneyBag.png", false);

	//UI 하트
	_ImageManager->AddImage("heart", L"../Resources/UI/heart.png", false);


	/**********************
			아이템
	***********************/
	//나뭇가지 이미지
	_ImageManager->AddImage("item_brench", L"../Resources/Item/item_brench.png", false);


	/**********************
	   오브젝트 매니저 등록
	***********************/
	//인벤토리 등록
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
	
	//무브 아이템 등록 및 랜덤한 개수 맵 뿌리기
	for (UINT i = 0; i < 15; ++i) 
	{
		_ObjectManager->AddObject(ObjectType::Object, new MoveItem("brench", Vector2(Math::Random(0, WinSizeX), Math::Random(0, WinSizeY))));
	}
	
	//UI 무기 스왑 / UI 가방
	_ObjectManager->AddObject(ObjectType::UI, new UIWeaponAndBag);

	//UI 프로그래스 바
	_ObjectManager->AddObject(ObjectType::UI, new ProgressBar);

	//UI 돈 주머니
	_ObjectManager->AddObject(ObjectType::UI, new UIMoneyPoket);

	//for (UINT i = 0; i < 10; ++i)
	//{
	//	Vector2 randomPos = Vector2(Math::Random(0,WinSizeX), Math::Random(0,WinSizeY));
	//	Vector2 randomSize= Vector2(Math::Random(50,100), Math::Random(50,100));
	//	_ObjectManager->AddObject(ObjectType::Object, new TestDeadman(randomPos,randomSize));
	//}
}	//


void TownScene::ChanInit()
{	//인벤토리 등록
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);

	//UI 무기 스왑 / UI 가방
	_ObjectManager->AddObject(ObjectType::UI, new UIWeaponAndBag);

	//UI 프로그래스 바
	_ObjectManager->AddObject(ObjectType::UI, new ProgressBar);

	//UI 돈 주머니
	_ObjectManager->AddObject(ObjectType::UI, new UIMoneyPoket);
}

//여기다가 1번 던전것들 올리시면 됩니다유
void Dungeon_Map_01::ChanInit()
{

}
//보스방 던전 여따가 넣을거 넣으심 됨요
void Dungeon_Map_Boss::ChanInit()
{

}