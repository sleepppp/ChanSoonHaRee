#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"

#include "Enemy.h"
#include "Golem.h"
#include "Weeds.h"
//#include "BigSlime.h"

//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 100)));
	//_ObjectManager->AddObject(ObjectType::Object, new BigSlime(Vector2(100, 500)));
}

void TownScene::HaInit()
{
}