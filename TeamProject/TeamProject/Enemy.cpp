#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(Vector2 position)
{
	this->_position = position;
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//크기
	this->_size = Vector2(50, 50);
	//좌표기준 렉트 생성 요건
	this->_pivot = Pivot::CENTER;
	//속도
	_speed = 300.0f;
	//좌우확인
	_isLeft = false;
	//렉트 생성.

	this->UpdateRect();
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (_rc.right > WinSizeX)
	{
		_isLeft = false;
	}
	
	if (_rc.left < 0)
	{
		_isLeft = true;
	}
	
	if (_isLeft == true)
	{
		_position.x += _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
	
	if(_isLeft == false)
	{
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
}

void Enemy::Render()
{
	_DXRenderer->DrawRectangle(_rc, DefaultBrush::green);
	//창 생성(이름은 EnemySpeed)
	//ImGui::Begin("EnemySpeed");
	//{
	//	//슬라이더 플롯을 만든다 
	//	//@@ 이름 ,바꿀 float주소,최소값,최대값
	//	ImGui::SliderFloat("Speed", &_speed, 0.f, 300.0f);
	//}
	////창은 여기까지 
	//ImGui::End();
}

