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

//â1152*721

void Program::LoadResourceRee()
{
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
