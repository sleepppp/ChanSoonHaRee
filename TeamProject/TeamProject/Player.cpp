#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"		//총알
#include "Enemy.h"

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
	_name = "player";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;
	this->UpdateRect();		//rc 초기화

	//bullet값
	_bullet = new Bullet;
	_bullet->Init(10, 800);

	_playerBullet.x = 40;		//플레이어가 쏘는 총알의 사이즈
	_playerBullet.y = 40;	
}

void Player::Release()
{
	_bullet->Release();
	SafeDelete(_bullet);
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
	if (_Input->GetKeyDown(VK_SPACE))
	{
		_bullet->Fire(Vector2(_position), Vector2(_playerBullet), Math::PI/2, 400.0f);				
		this->UpdateRect();			
	}

	_bullet->Update();
	this->Collision();
}

void Player::Render()
{
	this->UpdateRect();
	_DXRenderer->FillRectangle(_rc, DefaultBrush::blue, true);	
	
	_bullet->Render();	
}


//플레이어 총알과 에너미 충돌 함수
void Player::Collision()
{
	//_enemy를 찾습니다.
	vector<GameObject*> enemyList = _ObjectManager->FindObjects("enemy");	

	//리턴값이 nullptr이 아닐 경우
	for (UINT i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i] != nullptr)
		{
			//플레이어 총알과 에너미 몸체가 충돌할 경우
			if (_bullet->Intersect(enemyList[i]->GetRect()))
			{
				enemyList[i]->SetIsLive(false);
			}
		}
	}
	
}