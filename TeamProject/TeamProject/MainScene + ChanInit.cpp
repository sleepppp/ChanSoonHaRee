#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"

#include "MoveItem.h"
#include "Inventory.h"
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::ChanInit()
{
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
	_ObjectManager->AddObject(ObjectType::Object, new MoveItem);
}

void TownScene::ChanInit()
{
}
