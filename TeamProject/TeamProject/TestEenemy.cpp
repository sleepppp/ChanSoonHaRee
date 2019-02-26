#include "stdafx.h"
#include "TestEenemy.h"


TestEenemy::TestEenemy(Vector2 pos,Vector2 size)
{
	this->_name = "TestEnemy";
	this->_position = pos;
	this->_pivot = Pivot::CENTER;
	this->_size = size; 
	this->UpdateRect();
	_state = State::Chasing;
	_hp = 3;
	_attackedSpeed  = 0.f;
}


TestEenemy::~TestEenemy()
{
}

void TestEenemy::Init()
{
}

void TestEenemy::Release()
{
}

void TestEenemy::Update()
{
	if (_state == State::Chasing)
	{
		GameObject* object = _ObjectManager->FindObject(ObjectType::Object, "TestPlayer");
		if (object)
		{
			float angle = Math::GetAngle(_position.x, _position.y, object->GetPosition().x, object->GetPosition().y);
			float speed = 200.0f;
			float distance = Math::GetDistance(_position.x, _position.y, object->GetPosition().x, object->GetPosition().y);
			if (distance > 50.0f)
			{
				this->_position.x += cosf(angle) * speed * _Time->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _Time->DeltaTime();
				this->UpdateRect();
			}
		}
	}
	else if (_state == State::Attacked)
	{
		_attackedSpeed -= 200.0f  * _Time->DeltaTime();
		if (_attackedSpeed <= 0.f)
		{
			_attackedSpeed = 0.f;
			_state = State::Chasing;
		}

		GameObject* object = _ObjectManager->FindObject(ObjectType::Object, "TestPlayer");
		if (object)
		{
			float angle = Math::GetAngle(_position.x, _position.y, object->GetPosition().x, object->GetPosition().y);
			angle -= Math::PI;
			if (angle < 0.f)
			{
				angle = Math::PI * 2.0f - angle;
			}
			this->_position.x += cosf(angle) * _attackedSpeed * _Time->DeltaTime();
			this->_position.y -= sinf(angle) * _attackedSpeed * _Time->DeltaTime();
			this->UpdateRect();
		}
	}
}

void TestEenemy::Render()
{
	_DXRenderer->FillRectangle(_rc, DefaultBrush::red, false);
}

void TestEenemy::Damage(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		_isLive = false;
	}
	else
	{
		_state = State::Attacked;
		_attackedSpeed = 200.0f;
	}
}
