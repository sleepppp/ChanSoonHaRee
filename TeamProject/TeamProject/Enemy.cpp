#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
}

void Enemy::Release()
{

}

void Enemy::Update()
{

}

void Enemy::Render()
{
	
}

//�� ������ �ѱ�� ���� �Լ�.
void Enemy::AttackedDemege(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		this->Destroy();
	}
	else
	{

	}
}

//��Ʈ������Ʈ�� ���� ����
RECT Enemy::UpdateRect(RECT rc, Vector2 position, Vector2 size, Pivot::Enum _pivot)
{
	switch (_pivot)
	{
	case Pivot::LEFT_TOP:
		rc = Figure::RectMake(position, size);
		break;
	case Pivot::CENTER:
		rc = Figure::RectMakeCenter(position, size);
		break;
	case Pivot::BOTTOM:
		rc = Figure::RectMakeBottom(position, size);
		break;
	default:
		break;
	}

	return rc;
}

//�ޱ۰��� ���� ���� Ÿ���� ����.
void Enemy::EnemyMoveType()
{
	if (_angle > Math::PI / 4 && _angle < ((3 * Math::PI) / 4))
	{
		_move = MoveType::Top;
	}
	else if (_angle > ((3 * Math::PI) / 4) && _angle < (Math::PI + (Math::PI / 4)))
	{
		_move = MoveType::Left;
	}
	else if (_angle > (Math::PI + (Math::PI / 4)) && _angle < (Math::PI + ((3 * Math::PI) / 4)))
	{
		_move = MoveType::Bottom;
	}
	else
		_move = MoveType::Right;
}