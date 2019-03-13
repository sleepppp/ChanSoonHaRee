#include "stdafx.h"
#include "MoveItem.h"
#include "UIWeaponAndBag.h"
#include "Inventory.h"
#include "Enemy.h"


//에너미 아이템 뿌리기
void Enemy::SprayItemEnemy()
{
	//플랑크톤 에너미 포인터 다운캐스팅 적용해서 클래스 가져오기
	const vector<GameObject*> pEnemy = _ObjectManager->FindObjects(ObjectType::Object, "plankton");

	//x, y 포지션 
	Vector2 randomPos;

	//랜덤한 방향으로 뿌리기
	//randomPos.x += cosf(Math::Random(1, 360)) * 50.0f * _TimeManager->DeltaTime();
	//randomPos.y -= sinf(Math::Random(1, 360)) * 50.0f * _TimeManager->DeltaTime();


	for (UINT i = 0; i < pEnemy.size(); ++i)
	{
		//랜덤 좌표 X -30 ~ +30
		randomPos.x = Math::Random(pEnemy.at(i)->GetPosition().x - 30.f, pEnemy.at(i)->GetPosition().x + 30.f);
		//랜덤 좌표 Y -30 ~ +30
		randomPos.y = Math::Random(pEnemy.at(i)->GetPosition().y - 30.f, pEnemy.at(i)->GetPosition().y + 30.f);
	}

	//아이템 뿌리기
	_ObjectManager->AddObject(ObjectType::Object, new MoveItem("item_brench", randomPos));
	//_ObjectManager->AddObject(ObjectType::Object, new MoveItem("golemCore", randomPos));
}