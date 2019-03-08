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
	_count = 0;
	_attacked = false;
}

//내 뎀지를 넘기기 위한 함수.
void Enemy::AttackedDemege(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		this->Destroy();
	}
	else
	{
		_attacked = true;
		this->_attackedAngle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
	}
}

//렉트업데이트를 위한 변수
RECT Enemy::UpdateRect(Vector2 position, Vector2 size, Pivot::Enum _pivot)
{
	RECT rc;
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

//앵글값에 따라서 무브 타입을 결정.
void Enemy::EnemyMoveType()
{
	if (_angle > Math::PI / 4.f && _angle < ((3 * Math::PI) / 4.f))
	{
		_move = MoveType::Top;
	}
	else if (_angle > ((3.f * Math::PI) / 4.f) && _angle < (Math::PI + (Math::PI / 4.f)))
	{
		_move = MoveType::Left;
	}
	else if (_angle > (Math::PI + (Math::PI / 4.f)) && _angle < (Math::PI + ((3.f * Math::PI) / 4.f)))
	{
		_move = MoveType::Bottom;
	}
	else
	{
		_move = MoveType::Right;
	}
}

bool Enemy::IntersectReaction(RECT * moveRect, RECT * unMoveRect)
{

	RECT rc = { 0 };

	//충돌이 안되었다면 빠져나오라
	if (IntersectRect(&rc, moveRect, unMoveRect) == false)
		return false;

	int x = rc.right - rc.left;
	int y = rc.bottom - rc.top;
	if (x > y)
	{
		if (rc.bottom == unMoveRect->bottom)
		{
			moveRect->bottom = moveRect->bottom + y;
			moveRect->top = moveRect->top + y;
		}
		else if (rc.top == unMoveRect->top)
		{
			moveRect->bottom = moveRect->bottom - y;
			moveRect->top = moveRect->top - y;
		}
	}
	else
	{
		if (rc.left == unMoveRect->left)
		{
			moveRect->left = moveRect->left - x;
			moveRect->right = moveRect->right - x;
		}
		else if (rc.right == unMoveRect->right)
		{
			moveRect->left = moveRect->left + x;
			moveRect->right = moveRect->right + x;
		}
	}
	return true;
}

//직선거리 길이 구하는 공식.
float Enemy::Distance(Vector2 position)
{
	//직선거리를 구하고
	float distance = Math::GetDistance(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return distance;
}

//앵글값구하는 공식.
float Enemy::Angle(Vector2 position)
{
	//앵글값을 구하고
	float angle = Math::GetAngle(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return angle;
}