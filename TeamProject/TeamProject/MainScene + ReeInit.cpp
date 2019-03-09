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
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());
}

void TownScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());

	//_ObjectManager->AddObject(ObjectType::Object, new TestHuman(Vector2(627, 220)));
}

//1�� ������ ����ٰ� �ø��ø� �˴ϴ���
void Dungeon_Map_01::ReeInit()
{

}

//������ ������ ���⿡�ٰ� �ø��ø� �˴ϴ���
void Dungeon_Map_Boss::ReeInit()
{

}