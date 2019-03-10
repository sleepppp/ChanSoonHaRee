#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
//#include "Dungeon_Map_02.h"
#include "Player.h"
#include "Program.h"
#include "Dungeon_Map_Boss.h"
#include "Dungeon_Map_02.h"
//#include "TestHuman.h"

//창1152*721

void Program::LoadResourceRee()
{
}
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
void MainScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, WinSizeY/2)));
}

void TownScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX/2,500)));	

	//_ObjectManager->AddObject(ObjectType::Object, new TestHuman(Vector2(627, 220)));
}
void Dungeon_Map_01::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, 500)));
}

//void Dungeon_Map_02::ReeInit()
//{
//	_ObjectManager->AddObject(ObjectType::Object, new Player(Vector2(WinSizeX / 2, 700)));
//}

void  Dungeon_Map_Boss::ReeInit()
{

}void Dungeon_Map_02::ReeInit()
{
}
