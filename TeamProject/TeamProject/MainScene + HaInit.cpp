#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_02.h"
#include "Dungeon_Map_Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "BigSlime.h"
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

	//++++++++++++++++++++++++++++++++++++++++++���� �浹 �� �̹���++++++++++++++++++++++++++++++++++++++++++//
	//��������
	_ImageManager->AddFrameImage("create_Red", L"../Resources/Enemy/Boss/CreateBoss_Red.png", 32, 1, true);
	_ImageManager->AddFrameImage("create_White", L"../Resources/Enemy/Boss/CreateBoss_White.png", 32, 1, true);
	//�������1
	_ImageManager->AddFrameImage("dead1_Red", L"../Resources/Enemy/Boss/deadBoss1.png", 41, 1, true);
	_ImageManager->AddFrameImage("dead1_White", L"../Resources/Enemy/Boss/deadBoss1.png", 41, 1, true);
	//�������2
	_ImageManager->AddFrameImage("dead2_Red", L"../Resources/Enemy/Boss/deadBoss2.png", 41, 1, true);
	_ImageManager->AddFrameImage("dead2_White", L"../Resources/Enemy/Boss/deadBoss2.png", 41, 1, true);
	//�ճ����� ó����� �ǰ�
	_ImageManager->AddFrameImage("hand_Shoot_First_Red", L"../Resources/Enemy/Boss/hand_Shoot_First_Red.png", 20, 1, true);
	_ImageManager->AddFrameImage("hand_Shoot_First_White", L"../Resources/Enemy/Boss/hand_Shoot_First_White.png", 20, 1, true);
	//�ճ����� �߰���� �ǰ�
	_ImageManager->AddFrameImage("hand_Shoot_second_Red", L"../Resources/Enemy/Boss/hand_Shoot_second_Red.png", 30, 1, true);
	_ImageManager->AddFrameImage("hand_Shoot_second_White", L"../Resources/Enemy/Boss/hand_Shoot_second_White.png", 30, 1, true);
	//�ճ����� ��������� �ǰ�
	_ImageManager->AddFrameImage("hand_Shoot_Last_Red", L"../Resources/Enemy/Boss/hand_Shoot_Last_Red.png", 11, 1, true);
	_ImageManager->AddFrameImage("hand_Shoot_Last_White", L"../Resources/Enemy/Boss/hand_Shoot_Last_White.png", 11, 1, true);
	//�� �ǰ�
	_ImageManager->AddFrameImage("hand_Red", L"../Resources/Enemy/Boss/hand_Red.png", 19, 1, true);
	_ImageManager->AddFrameImage("hand_White", L"../Resources/Enemy/Boss/hand_White.png", 19, 1, true);
	//2����ų ���� �̹��� �ǰ�
	_ImageManager->AddFrameImage("Rock_Shoot_Red", L"../Resources/Enemy/Boss/rockShoot_Red.png", 32, 1, true);
	_ImageManager->AddFrameImage("Rock_Shoot_White", L"../Resources/Enemy/Boss/rockShoot_White.png", 32, 1, true);
	//3����ų ���� �̹��� �ǰ�
	_ImageManager->AddFrameImage("FistShoot_Red", L"../Resources/Enemy/Boss/FistShoot_Red.png", 22, 3, true);
	_ImageManager->AddFrameImage("FistShoot_White", L"../Resources/Enemy/Boss/FistShoot_White.png", 22, 3, true);
	//============�� ������ �̹���============//
	//����
	_ImageManager->AddFrameImage("Create", L"../Resources/Enemy/MiddleBoss/CreateSlime.png", 37, 1, true);
	//����
	_ImageManager->AddFrameImage("Move", L"../Resources/Enemy/MiddleBoss/SlimeMove.png", 8, 2, true);
	//����
	_ImageManager->AddFrameImage("Attack", L"../Resources/Enemy/MiddleBoss/SlimeAttack.png", 22, 2, true);
	//���
	_ImageManager->AddFrameImage("Dead", L"../Resources/Enemy/MiddleBoss/SlimeDead.png", 37, 1, true);
	//------------�� �̹���-----------------//
	_ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4, true);
	_ImageManager->AddFrameImage("GolemMove_Red", L"../Resources/Enemy/Golem/GolemMove_Red.png", 8, 4, true);
	_ImageManager->AddFrameImage("GolemMove_White", L"../Resources/Enemy/Golem/GolemMove_White.png", 8, 4, true);
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

	//====================================����=====================================//
	_SoundManager->AddSound("golemHit", "../Sounds/golem_hit.wav", false, false);
	_SoundManager->AddSound("enemyDeath", "../Sounds/enemy_death.wav", false, false);
	_SoundManager->AddSound("Weeds_Hit", "../Sounds/weed_hit.wav", false, false);
	_SoundManager->AddSound("bossDeath", "../Sounds/bossDeath.wav", false, false);
	_SoundManager->AddSound("bossCreate", "../Sounds/GolemKingWakeUp.wav", false, false);
	_SoundManager->AddSound("GolemKingHandCrush", "../Sounds/GolemKingHandCrush.wav", false, false);
	_SoundManager->AddSound("GolemKingRockHitGround", "../Sounds/GolemKingRockHitGround.wav", false, false);
	_SoundManager->AddSound("GolemKingRoom", "../Sounds/GolemKingRoom.mp3", true, true);
	// ���������� �����ִ� ���� ��� ����Ǵ� ����
	_SoundManager->AddSound("dungeon_wanderer_idle", "../Sounds/dungeon_wanderer_idle.wav", false, false);
	// ���������� ���� ����
	_SoundManager->AddSound("dungeon_wanderer_appears", "../Sounds/dungeon_wanderer_appears.wav", false, false);
	// ���� ������ ���� ����
	_SoundManager->AddSound("dungeon_wanderer_attack", "../Sounds/dungeon_wanderer_attack.wav", false, false);
	//�� ���� ����
	_SoundManager->AddSound("golem_dungeon_golem_crash", "../Sounds/golem_dungeon_golem_crash.wav", false, false);

}
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new BigSlime(Vector2(100, 500)));
}

void Dungeon_Map_01::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(900, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(100, 400)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(900, 400)));
}

void Dungeon_Map_02::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new BigSlime(Vector2(300, 300)));
}

void Dungeon_Map_Boss::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Boss());
}

void TownScene::HaInit()
{
}

