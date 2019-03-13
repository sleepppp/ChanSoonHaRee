#include "stdafx.h"
#include "MoveItem.h"
#include "UIWeaponAndBag.h"
#include "Inventory.h"
#include "Enemy.h"


//���ʹ� ������ �Ѹ���
void Enemy::SprayItemEnemy()
{
	//�ö�ũ�� ���ʹ� ������ �ٿ�ĳ���� �����ؼ� Ŭ���� ��������
	const vector<GameObject*> pEnemy = _ObjectManager->FindObjects(ObjectType::Object, "plankton");

	//x, y ������ 
	Vector2 randomPos;

	//������ �������� �Ѹ���
	//randomPos.x += cosf(Math::Random(1, 360)) * 50.0f * _TimeManager->DeltaTime();
	//randomPos.y -= sinf(Math::Random(1, 360)) * 50.0f * _TimeManager->DeltaTime();


	for (UINT i = 0; i < pEnemy.size(); ++i)
	{
		//���� ��ǥ X -30 ~ +30
		randomPos.x = Math::Random(pEnemy.at(i)->GetPosition().x - 30.f, pEnemy.at(i)->GetPosition().x + 30.f);
		//���� ��ǥ Y -30 ~ +30
		randomPos.y = Math::Random(pEnemy.at(i)->GetPosition().y - 30.f, pEnemy.at(i)->GetPosition().y + 30.f);
	}

	//������ �Ѹ���
	_ObjectManager->AddObject(ObjectType::Object, new MoveItem("item_brench", randomPos));
	//_ObjectManager->AddObject(ObjectType::Object, new MoveItem("golemCore", randomPos));
}