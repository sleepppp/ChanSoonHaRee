#include "stdafx.h"
#include "MainScene.h"

#include "Inventory.h"
//���⼭ �ʿ��� ���ҽ� �ε� �� Ŭ���� �Ҵ��Ͻø� �˴ϴ�. 
//Init�� ���� new �ϰ� ObjectManager�� �߰� ����
void MainScene::ChanInit()
{
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
}