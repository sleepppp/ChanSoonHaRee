#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"		//총알

/*****************************************
전역: 변수: _player , bool값: _isActive
지역: 변수: player, bool값: isActive
변수 외(함수, 클래스): Player
*****************************************/
//플레이어: 움직임, 상호참조...로... 충돌...처리...

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	_speed = 200.0f;
	_name = "플레이어";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;

	this->UpdateRect();		//rc 초기화
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
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
	//이동:우
	if (_Input->GetKey('D'))
	{
		_position.x += _speed * _Time->DeltaTime();
		this->UpdateRect();
	}

	//액션:총알발사
	if (_Input->GetKey(VK_SPACE))
	{
		this->BulletFire();		//총알 생성 및 발사
		this->UpdateRect();		
	}
}

void Player::Render()
{
	this->UpdateRect();
	_DXRenderer->FillRectangle(_rc, DefaultBrush::blue, true);	
}

//플레이어 총알 발사
void Player::BulletFire()
{
	//불렛클래스를 벡터에 담아서...그려주고 불값 없으면 추가하고
	
	//총알 벡터 10개
	//발사할 경우 bool값으로 false는 continue, true면 진입;
	
	//발사할 경우 bool값 false로 변경
	//rc그리기

	//Vector
}