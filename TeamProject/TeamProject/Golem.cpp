#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"
#include "Golem.h"


Golem::Golem()
{
}


Golem::~Golem()
{
}

void Golem::Init()
{

	Enemy::Init();
	this->_name = "Golem";
	this->_position = Vector2(100, 100);
	this->_size = Vector2(100, 100);
	this->_pivot = Pivot::CENTER;
	this->_speed = 90.0f;
	this->_hp = 200;
	this->_demage = 34;
	this->_count = 0;
	this->UpdateRect(_renderRect, _position, _size, Pivot::CENTER);

	this->_move = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.pmg", 8, 4);
	this->_attack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);

	this->_moveCount = 0;
	this->_attackCount = 0;
	this->_attackedCount = 0;

	this->_sizeLeft = Vector2(-100, 20);
	this->_sizeRight = Vector2(100, 20);
	this->_sizeTop = Vector2(20, -100);
	this->_sizeBottom = Vector2(20, 100);
	this->_isAttackTop = false;
	this->_isAttackLeft = false;
	this->_isAttackRight = false;
	this->_isAttackBottom = false;
	this->UpdateRect(_attackLeft, _position, _sizeLeft, Pivot::LEFT_TOP);
	this->UpdateRect(_attackRight, _position, _sizeRight, Pivot::LEFT_TOP);
	this->UpdateRect(_attackTop, _position, _sizeTop, Pivot::LEFT_TOP);
	this->UpdateRect(_attackBottom, _position, _sizeBottom, Pivot::LEFT_TOP);

}
void Golem::Release()
{

}

void Golem::Update()
{
	_count++;
	if (_state == StateType::Chasing)
	{
		this->Move();
	}
}

void Golem::Render()
{
	
}


void Golem::Move()
{
	if (_state == StateType::Chasing)
	{
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle)*_speed * _TimeManager->DeltaTime();
		this->UpdateRect(_renderRect, _position, _size, Pivot::CENTER);
	}
	if (_state == StateType::Attacked && this->_attackedCount < 200)
	{
		this->_angle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
	}
}

void Golem::Attack()
{
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	if (_distance < (_size.x * 1.5f))
	{
		_state = StateType::attack;
	}
	if (_state == StateType::attack)
	{
		_attackCount++;
	}
	if (_distance > 800)
	{
		_attackCount = 0;
		_state = StateType::Chasing;
	}
}

void Golem::AttackPosition()
{
	if (_state == StateType::attack && _attackCount > 700)
	{

	}
}
