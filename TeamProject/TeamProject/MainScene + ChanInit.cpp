#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"

#include "MoveItem.h"
#include "Inventory.h"
//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
void MainScene::ChanInit()
{
	_ObjectManager->AddObject(ObjectType::UI, new Inventory);
	_ObjectManager->AddObject(ObjectType::Object, new MoveItem);
}

void TownScene::ChanInit()
{
}
