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
	//------------보스 몸체 이미지-------------//
	//생성상태
	_ImageManager->AddFrameImage("create", L"../Resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	//사망상태
	_ImageManager->AddFrameImage("dead1", L"../Resources/Enemy/Boss/deadBoss1.png", 41, 1, true);
	_ImageManager->AddFrameImage("dead2", L"../Resources/Enemy/Boss/deadBoss2.png", 41, 1, true);
	//----------1번스킬----------//
	//손날리는 처음모션
	_ImageManager->AddFrameImage("hand_Shoot_First", L"../Resources/Enemy/Boss/Hand_Shoot_First.png", 20, 1, true);
	//손날리는 중간모션
	_ImageManager->AddFrameImage("hand_Shoot_second", L"../Resources/Enemy/Boss/Hand_Shoot_Second.png", 30, 1, true);
	//손날리는 마지막모션
	_ImageManager->AddFrameImage("hand_Shoot_Last", L"../Resources/Enemy/Boss/Hand_Shoot_Last.png", 11, 1, true);
	//손
	_ImageManager->AddFrameImage("hand", L"../Resources/Enemy/Boss/hand.png", 19, 1, true);
	
	//----------2번스킬------------//
	//보스 이미지
	_ImageManager->AddFrameImage("Rock_Shoot", L"../Resources/Enemy/Boss/rockShoot.png", 32, 1, true);
	
	//---------------3번 스킬----------------//
	//보스 이미지
	_ImageManager->AddFrameImage("FistShoot", L"../Resources/Enemy/Boss/FistShoot.png", 22, 3, true);
	//슬라임의 조준상태일때의 주먹.
	_ImageManager->AddImage("SlimeTargetFist", L"../Resources/Enemy/Boss/Boss_SlimeTargetHand.png", true);
	//------------골렘 이미지-----------------//
	_ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4, true);
	_ImageManager->AddFrameImage("GolemMove_Red", L"../Resources/Enemy/Golem/GolemMove_Red.png", 8, 4,true);
	_ImageManager->AddFrameImage("GolemMove_White", L"../Resources/Enemy/Golem/GolemMove_White.png", 8, 4,true);
	_ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4, true);
	_ImageManager->AddFrameImage("GolemAttack_Red", L"../Resources/Enemy/Golem/GolemAttack_Red.png", 13, 4), true;
	_ImageManager->AddFrameImage("GolemAttack_White", L"../Resources/Enemy/Golem/GolemAttack_White.png", 13, 4, true);

	//------------------잡초---------------------//
	_ImageManager->AddFrameImage("weeds", L"../Resources/Enemy/Weeds/Weeds.png", 12, 1, true);
	_ImageManager->AddFrameImage("weeds_Red", L"../Resources/Enemy/Weeds/Weeds_Red.png", 12, 1, true);
	_ImageManager->AddFrameImage("weeds_White", L"../Resources/Enemy/weeds/Weeds_White.png", 12, 1, true);

	//--------------그림자-----------------//
	_ImageManager->AddImage("shadow", L"../Resources/Object/Shadow.png");

	//---------------돌--------------------//
	_ImageManager->AddImage("rock", L"../Resources/Enemy/Boss/Boss_Rock0.png", true);
}
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
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

