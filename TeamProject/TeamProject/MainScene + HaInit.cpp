#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_02.h"
#include "Dungeon_Map_Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "Golem.h"
#include "Boss.h"
#include "Weeds.h"
#include "Rock.h"
#include "Program.h"
//#include "BigSlime.h"
void Program::LoadResourceHa()
{
	//------------���� ��ü �̹���-------------//
	//��������
	_ImageManager->AddFrameImage("create", L"../Resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	//�������
	_ImageManager->AddFrameImage("dead1", L"../Resources/Enemy/Boss/deadBoss1.png", 41, 1, true);
	_ImageManager->AddFrameImage("dead2", L"../Resources/Enemy/Boss/deadBoss2.png", 41, 1, true);
	//----------1����ų----------//
	//�ճ����� ó�����
	_ImageManager->AddFrameImage("hand_Shoot_First", L"../Resources/Enemy/Boss/Hand_Shoot_First.png", 20, 1, true);
	//�ճ����� �߰����
	_ImageManager->AddFrameImage("hand_Shoot_second", L"../Resources/Enemy/Boss/Hand_Shoot_Second.png", 30, 1, true);
	//�ճ����� ���������
	_ImageManager->AddFrameImage("hand_Shoot_Last", L"../Resources/Enemy/Boss/Hand_Shoot_Last.png", 11, 1, true);
	//��
	_ImageManager->AddFrameImage("hand", L"../Resources/Enemy/Boss/hand.png", 19, 1, true);
	
	//----------2����ų------------//
	//���� �̹���
	_ImageManager->AddFrameImage("Rock_Shoot", L"../Resources/Enemy/Boss/rockShoot.png", 32, 1, true);
	
	//---------------3�� ��ų----------------//
	//���� �̹���
	_ImageManager->AddFrameImage("FistShoot", L"../Resources/Enemy/Boss/FistShoot.png", 22, 3, true);
	//�������� ���ػ����϶��� �ָ�.
	_ImageManager->AddImage("SlimeTargetFist", L"../Resources/Enemy/Boss/Boss_SlimeTargetHand.png", true);
	//------------�� �̹���-----------------//
	_ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4, true);
	_ImageManager->AddFrameImage("GolemMove_Red", L"../Resources/Enemy/Golem/GolemMove_Red.png", 8, 4,true);
	_ImageManager->AddFrameImage("GolemMove_White", L"../Resources/Enemy/Golem/GolemMove_White.png", 8, 4,true);
	_ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4, true);
	_ImageManager->AddFrameImage("GolemAttack_Red", L"../Resources/Enemy/Golem/GolemAttack_Red.png", 13, 4), true;
	_ImageManager->AddFrameImage("GolemAttack_White", L"../Resources/Enemy/Golem/GolemAttack_White.png", 13, 4, true);

	//------------------����---------------------//
	_ImageManager->AddFrameImage("weeds", L"../Resources/Enemy/Weeds/Weeds.png", 12, 1, true);
	_ImageManager->AddFrameImage("weeds_Red", L"../Resources/Enemy/Weeds/Weeds_Red.png", 12, 1, true);
	_ImageManager->AddFrameImage("weeds_White", L"../Resources/Enemy/weeds/Weeds_White.png", 12, 1, true);

	//--------------�׸���-----------------//
	_ImageManager->AddImage("shadow", L"../Resources/Object/Shadow.png");

	//---------------��--------------------//
	_ImageManager->AddImage("rock", L"../Resources/Enemy/Boss/Boss_Rock0.png", true);
}
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 100)));
	//_ObjectManager->AddObject(ObjectType::Object, new BigSlime(Vector2(100, 500)));
}

void Dungeon_Map_01::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(400, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 400)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(700, 500)));
}

void Dungeon_Map_02::HaInit()
{
}

void Dungeon_Map_Boss::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Boss());
}

void TownScene::HaInit()
{
}

