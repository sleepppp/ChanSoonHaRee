#include "stdafx.h"
#include "Player.h"

/*****************************************
전역: 변수: _player , bool값: _isActive
지역: 변수: player, bool값: isActive
변수 외(함수, 클래스): Player
*****************************************/

//플레이어: 움직임, 상호참조...로... 충돌...처리...

Player::Player()
{
	_speed = 0;
	_name = "플레이어";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;

	this->UpdateRect();		//rc 초기화
}

Player::~Player()
{
}


void Player::Init()
{
	
}

void Player::Release()
{
}

void Player::Update()
{
	//이동:좌
	if (_Input->GetKey('A'))
	{
		// 그냥 좌표 변경인거 같으니 물어보자 SetPosition(Vector2(-200.f, 0.f));
		_position.x -= 200.f * _Time->DeltaTime();
		this->UpdateRect();
	}
	//이동:우
	if (_Input->GetKey('D'))
	{
		_position.x += 200.f * _Time->DeltaTime();
		this->UpdateRect();
	}

	//액션:총알발사
	if (_Input->GetKey(VK_SPACE))
	{

		this->UpdateRect();
	}
}

void Player::Render()
{

}


//플레이어 총알 발사
void BulletFire()
{

}

//플레이어 총알 이동
void BulletMove()
{

}

//플레이어와 에너미 총알 충돌할 경우