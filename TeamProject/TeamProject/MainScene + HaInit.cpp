#include "stdafx.h"
#include "MainScene.h"
#include "Enemy.h"
#include "Player.h"
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����

void MainScene::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Enemy());
	_ObjectManager->AddObject(ObjectType::Object, new player());
}