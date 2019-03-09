#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_Boss.h"
#include "Player.h"
#include "Program.h"
//#include "TestHuman.h"


void Program::LoadResourceRee()
{
}
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
void MainScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());
}

void TownScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());

	//_ObjectManager->AddObject(ObjectType::Object, new TestHuman(Vector2(627, 220)));
}

//1범 던전맵 여기다가 올리시면 됩니다유
void Dungeon_Map_01::ReeInit()
{

}

//보스방 던전맵 여기에다가 올리시면 됩니다유
void Dungeon_Map_Boss::ReeInit()
{

}