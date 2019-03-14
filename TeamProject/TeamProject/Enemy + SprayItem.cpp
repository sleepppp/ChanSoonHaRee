#include "stdafx.h"
#include "MoveItem.h"
#include "UIWeaponAndBag.h"
#include "Inventory.h"
#include "Enemy.h"


//���ʹ� ������ �Ѹ���
void Enemy::SprayItemEnemy()
{
	//x, y ������ 
	Vector2 randomPos;

	//���� ��ǥ X -30 ~ +30
	randomPos.x = Math::Random(this->_position.x - 30.f, this->_position.x + 30.f);
	//���� ��ǥ Y -30 ~ +30
	randomPos.y = Math::Random(this->_position.y - 30.f, this->_position.y + 30.f);

	//������ �Ѹ���
	_ObjectManager->AddObject(ObjectType::Object, new MoveItem("item_brench", randomPos));
}