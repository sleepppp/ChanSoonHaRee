#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"

#include "Enemy.h"
#include "Golem.h"
#include "Weeds.h"
//#include "BigSlime.h"

//여기서 필요한 리소스 로드 및 클래스 할당하시면 됩니다. 
//Init은 ㄴㄴ new 하고 ObjectManager에 추가 ㅇㅇ
void MainScene::HaInit()
{
	_ObjectManager->AddObject(ObjectType::Object, new Golem(Vector2(100, 100)));
	_ObjectManager->AddObject(ObjectType::Object, new Weeds(Vector2(300, 100)));
	//_ObjectManager->AddObject(ObjectType::Object, new BigSlime(Vector2(100, 500)));
}

void TownScene::HaInit()
{
}