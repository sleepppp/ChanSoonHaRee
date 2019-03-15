#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
//#include "Dungeon_Map_02.h"
#include "Player.h"
#include "Program.h"
#include "Dungeon_Map_Boss.h"
#include "Dungeon_Map_02.h"
#include "Npc.h"
#include "Npc_Girl.h"
#include "Npc_Guy.h"
#include "Npc_Lunk.h"

void Program::LoadResourceRee()
{
	_SoundManager->AddSound("will_roll", "../Sounds/will_roll.wav", false, false);						//�Ѹ�
	_SoundManager->AddSound("will_swordAtk", "../Sounds/will_shortSwordAttack.wav", false, false);		//�˰���
	_SoundManager->AddSound("will_bowAtk", "../Sounds/will_bowAttack.wav", false, false);				//Ȱ����
	_SoundManager->AddSound("will_damage", "../Sounds/will_damaged.wav", false, false);					//�������Ծ�����
	_SoundManager->AddSound("will_bowWall", "../Sounds/will_bowWall.wav", false, false);				//ȭ�� ���� ������ �Ҹ�
	_SoundManager->AddSound("will_die", "../Sounds/will_death.wav", false, false);						//���
	//_SoundManager->AddSound("Will_")
}
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, WinSizeY/2)));
}

void TownScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX/2,500)));	
	_ObjectManager->AddObject(ObjectType::Object, new Npc());
	_ObjectManager->AddObject(ObjectType::Object, new Npc_Girl());
	_ObjectManager->AddObject(ObjectType::Object, new Npc_Guy());
	_ObjectManager->AddObject(ObjectType::Object, new Npc_Lunk());
}
void Dungeon_Map_01::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(700, 500)));
}
void Dungeon_Map_02::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, 500)));
}
void  Dungeon_Map_Boss::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, 500)));
}