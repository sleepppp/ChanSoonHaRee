#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Player.h"

//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());
}

void TownScene::ReeInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Player());
}
