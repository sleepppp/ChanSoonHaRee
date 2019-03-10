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
#include "Effect.h"
#include "Dungeon_Map_02.h"
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����


void Program::LoadResourceChan()
{

	/**********************
			   UI
	***********************/
	//���� �κ��丮 �̹��� 
	_ImageManager->AddImage("InventoryWindow", L"../Resources/UI/newInventory.png", false);

	//UI ���� ����
	_ImageManager->AddFrameImage("UI_WeaponSwap", L"../Resources/UI/UI_WeaponSwap.png", 4, 1, false);
	//UI ����
	_ImageManager->AddImage("UI_Bag", L"../Resources/UI/UI_Bag.png", false);

	//UI �� �ָӴ�
	_ImageManager->AddImage("moneyPoket", L"../Resources/UI/moneyBag.png", false);

	//UI ��Ʈ
	_ImageManager->AddImage("heart", L"../Resources/UI/heart.png", false);



	/**********************
			����Ʈ
	***********************/
	_ImageManager->AddFrameImage("swordAtkEffect", L"../Resources/Effect/fx_hit_shortsword.png", 3, 1, false);



	/**********************
			������
	***********************/
	//�������� �̹���
	_ImageManager->AddImage("item_brench", L"../Resources/Item/item_brench.png", false);
}

void MainScene::ChanInit()
{

	//UI ���α׷��� ��
	//_ImageManager->AddFrameImage("hpBar1", L"../Resouces/UI/hpBar", 1, 6, false);
	//_ImageManager->AddFrameImage("hpBar2", L"../Resouces/UI/hpBar", 1, 6, false);

	/**********************
	   ������Ʈ �Ŵ��� ���
	***********************/
	//�κ��丮 ���
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
	
	//���� ������ ��� �� ������ ���� �� �Ѹ���
	for (UINT i = 0; i < 15; ++i) 
	{
		_ObjectManager->AddObject(ObjectType::Object, new MoveItem("brench", Vector2(Math::Random(0, WinSizeX), Math::Random(0, WinSizeY))));
	}
	
	//UI ���� ���� / UI ����
	_ObjectManager->AddObject(ObjectType::UI, new UIWeaponAndBag);

	//UI ���α׷��� ��
	_ObjectManager->AddObject(ObjectType::UI, new ProgressBar);

	//UI �� �ָӴ�
	_ObjectManager->AddObject(ObjectType::UI, new UIMoneyPoket);
	
	//����Ʈ
	for (UINT i = 0; i < 30; ++i) 
	{
		_ObjectManager->AddObject(ObjectType::Effect, new Effect);
	}
	

	//for (UINT i = 0; i < 10; ++i)
	//{
	//	Vector2 randomPos = Vector2(Math::Random(0,WinSizeX), Math::Random(0,WinSizeY));
	//	Vector2 randomSize= Vector2(Math::Random(50,100), Math::Random(50,100));
	//	_ObjectManager->AddObject(ObjectType::Object, new TestDeadman(randomPos,randomSize));
	//}
}	//


void TownScene::ChanInit()
{	//�κ��丮 ���
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);

	//UI ���� ���� / UI ����
	_ObjectManager->AddObject(ObjectType::UI, new UIWeaponAndBag);

	//UI ���α׷��� ��
	_ObjectManager->AddObject(ObjectType::UI, new ProgressBar);

	//UI �� �ָӴ�
	_ObjectManager->AddObject(ObjectType::UI, new UIMoneyPoket);

	//����Ʈ
	for (UINT i = 0; i < 30; ++i)
	{
		_ObjectManager->AddObject(ObjectType::Effect, new Effect);
	}
}

//����ٰ� 1�� �����͵� �ø��ø� �˴ϴ���
void Dungeon_Map_01::ChanInit()
{
	//����Ʈ
	for (UINT i = 0; i < 30; ++i)
	{
		_ObjectManager->AddObject(ObjectType::Effect, new Effect);
	}
}
//������ ���� ������ ������ ������ �ʿ�
void Dungeon_Map_Boss::ChanInit()
{
	//����Ʈ
	for (UINT i = 0; i < 30; ++i)
	{
		_ObjectManager->AddObject(ObjectType::Effect, new Effect);
	}
}

void Dungeon_Map_02::ChanInit()
{
	//����Ʈ
	for (UINT i = 0; i < 30; ++i)
	{
		_ObjectManager->AddObject(ObjectType::Effect, new Effect);
	}
}
