#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "Golem.h"
#include "Weeds.h"
#include "Program.h"
//#include "BigSlime.h"
void Program::LoadResourceHa()
{
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
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(500, 500)));
	
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(400, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 400)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(700, 500)));


}

void Dungeon_Map_Boss::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(500, 500)));
}

void TownScene::HaInit()
{
}

