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
	this->_isAttack = false;
	this->UpdateRect(_renderRect, _position, _size, Pivot::CENTER);

	this->_golemMove = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.pmg", 8, 4);
	this->_golemAttack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);

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
	this->Attack();
	this->EnemyMoveType();
	this->ImageCount();
	this->AttackPosition();
	this->Collision();
}

void Golem::Render()
{
	this->RectRender();
	this->ImageRender();
}

void Golem::ImageCount()
{
	if (_state == StateType::Chasing)
	{
		if (_move == MoveType::Left)
		{
			if (_count % 60 == 0)
			{
				_attackCount++;
				if (_attackCount >= 8)
					_attackCount = 0;
			}
		}
		if (_move == MoveType::Right)
		{
			if (_count % 60 == 0)
			{
				_attackCount++;
				if (_attackCount >= 8)
					_attackCount = 0;
			}
		}
		if (_move == MoveType::Top)
		{
			if (_count % 60 == 0)
			{
				_attackCount++;
				if (_attackCount >= 8)
					_attackCount = 0;
			}
		}
		if (_move == MoveType::Bottom)
		{
			if (_count % 60 == 0)
			{
				_attackCount++;
				if (_attackCount >= 8)
					_attackCount = 0;
			}
		}
	}

	if (_state == StateType::attack)
	{
		if (_move == MoveType::Left)
		{
			if (_count % 60 == 0)
			{
				_attackCount++;
				if (_attackCount >= 13)
					_attackCount = 0;
			}
		}
		if (_move == MoveType::Right)
		{
			if (_count % 60 == 0)
			{
				_moveCount++;
				if (_moveCount >= 13)
					_moveCount = 0;
			}
		}
		if (_move == MoveType::Top)
		{
			if (_count % 60 == 0)
			{
				_moveCount++;
				if (_moveCount >= 13)
					_moveCount = 0;
			}
		}
		if (_move == MoveType::Bottom)
		{
			if (_count % 60 == 0)
			{
				_moveCount++;
				if (_moveCount >= 13)
					_moveCount = 0;
			}
		}
	}
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
		this->UpdateRect(_renderRect, _position, _size, Pivot::CENTER);
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
		if (_move == MoveType::Left)
		{
			this->_isAttackLeft = true;
			this->UpdateRect(_attackLeft, _position, _sizeLeft, Pivot::LEFT_TOP);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right)
		{
			this->_isAttackRight = true;
			this->UpdateRect(_attackLeft, _position, _sizeRight, Pivot::LEFT_TOP);
		}
		else _isAttackRight = false;

		if (_move == MoveType::Top)
		{
			this->_isAttackTop = true;
			this->UpdateRect(_attackTop, _position, _sizeTop, Pivot::LEFT_TOP);
		}
		else _isAttackTop = false;

		if (_move == MoveType::Bottom)
		{
			this->_isAttackBottom = true;
			this->UpdateRect(_attackBottom, _position, _sizeBottom, Pivot::LEFT_TOP);
		}
		else _isAttackBottom = false;
	}
}

void Golem::AttackRender()
{
	if (_state == StateType::attack)
	{
		if (this->_isAttackLeft == true)
		{
			_DXRenderer->DrawRectangle(_attackLeft, DefaultBrush::yello);
		}
		if (this->_isAttackRight == true)
		{
			_DXRenderer->DrawRectangle(_attackRight, DefaultBrush::yello);
		}
		if (this->_isAttackTop == true)
		{
			_DXRenderer->DrawRectangle(_attackTop, DefaultBrush::yello);
		}
		if (this->_isAttackBottom == true)
		{
			_DXRenderer->DrawRectangle(_attackBottom, DefaultBrush::yello);
		}
	}
}

void Golem::Collision()
{
	RECT CollisionRc = { 0 };
	if (IntersectRect(&CollisionRc, &_attackLeft, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&CollisionRc, &_attackRight, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&CollisionRc, &_attackTop, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&CollisionRc, &_attackBottom, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
}

void Golem::RectRender()
{
	if (_Input->IsToggleKey('1'))
	{
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::gray);
		if (_state == StateType::Chasing)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.5f), DefaultBrush::blue);
		}
		if (_state == StateType::attack)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.5f), DefaultBrush::red);
		}
		this->AttackRender();
	}
}

void Golem::ImageRender()
{
	if (_state == StateType::Chasing)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		if (_move == MoveType::Left)
		{
			_golemMove->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
		}
		if (_move == MoveType::Right)
		{
			_golemMove->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
		}
		if (_move == MoveType::Top)
		{
			_golemMove->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
		}
		if (_move == MoveType::Bottom)
		{
			_golemMove->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
		}
	}

	if (_state == StateType::attack)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		if (_move == MoveType::Left)
		{
			_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 0, Pivot::CENTER, true);
		}
		if (_move == MoveType::Right)
		{
			_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 1, Pivot::CENTER, true);
		}
		if (_move == MoveType::Top)
		{
			_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 2, Pivot::CENTER, true);
		}
		if (_move == MoveType::Bottom)
		{
			_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 3, Pivot::CENTER, true);
		}
	}
}