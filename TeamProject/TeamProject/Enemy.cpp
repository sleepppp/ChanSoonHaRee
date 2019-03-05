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
		_state = StateType::Attacked;
	}
}

//��Ʈ������Ʈ�� ���� ����
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

//�ޱ۰��� ���� ���� Ÿ���� ����.
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
//�i�ų� �ǰݴ����� �� �����̱� ���� �Լ�.
//���Ŀ� �Ⱦ�� ����������
void Enemy::Move()
{
	//�i����� �߰��� ���� �ޱ۰����� �̵��� ���� ������
	if (_state == StateType::Chasing)
	{
		//�i������ �ޱ۰�.
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle)*_speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);
	}
	//�ǰݽ� ����� �ݴ�������� ���ư��� ���� ������.
	if (_state == StateType::Attacked)
	{
		//ƨ���������� �ޱ۰�
		this->_angle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);
	}
}