#include "stdafx.h"
#include "TestEnemy.h"
#include "TestPlayer.h"
#include "TestPlayer.h"
TestEnemy::TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed)
{
	this->_name = "Enemy";
	this->_position = position;
	this->_size = size;
	this->_pivot = pivot;
	this->_speed = speed;
	this->_isActive = true;
	this->_isAttacked = false;
	this->UpdateRect();
}

TestEnemy::~TestEnemy()
{
}


void TestEnemy::Init()
{
	this->_player = (TestPlayer*)_ObjectManager->FindObject("TestPlayer");
	//_ImageManager->AddFrameImage("BackMove", L"GolemBackMove.png", 47, 0);

	
}

void TestEnemy::Release()
{

}

void TestEnemy::Update()
{
	EnemyMove();
	EnemyAttack();
}

void TestEnemy::Render()
{
	_DXRenderer->FillRectangle(_rc, DefaultBrush::green);
}

void TestEnemy::EnemyMove()
{
	this->_player = (TestPlayer*) _ObjectManager->FindObject("TestPlayer");
	this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	this->_position.x += cosf(_angle) * _speed * _Time->DeltaTime();
	this->_position.y += -sinf(_angle) * _speed * _Time->DeltaTime();
	this->UpdateRect();

}

void TestEnemy::EnemyAttack()
{

	RECT TestTemp = { 0 };
	if (IntersectRect(&TestTemp, &_rc, &_player->GetRect()))
	{
		_isAttacked = true;
	}
	this->UpdateRect();
}

//에너미 상태별 정리.
void TestEnemy::EnemyMoveType()
{
	if (_move == MoveType::Back)
	{

	}
	else if (_move == MoveType::Front)
	{

	}
	else if (_move == MoveType::Left)
	{

	}
	else if(_move == MoveType::Rigth)
	{

	}
}