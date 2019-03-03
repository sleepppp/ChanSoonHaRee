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
		_state = StateType::Attacked;
	}
}

//렉트업데이트를 위한 변수
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

//앵글값에 따라서 무브 타입을 결정.
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
//쫒거나 피격당했을 시 움직이기 위한 함수.
void Enemy::Move()
{
	//쫒을대상 추격을 위한 앵글값계산과 이동을 위한 변수들
	if (_state == StateType::Chasing)
	{
		//쫒기위한 앵글값.
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle)*_speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(_renderRect, _position, _size, Pivot::CENTER);
	}
	//피격시 대상의 반대방향으로 날아가기 위한 변수들.
	if (_state == StateType::Attacked)
	{
		//췽겨져나가는 앵글값
		this->_angle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(_renderRect, _position, _size, Pivot::CENTER);
	}
}