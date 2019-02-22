#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(Vector2 position)
{
	this->_position = position;
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	_name = "enemy";
	this->EnemyInit();
	_player =(Player*) _ObjectManager->FindObject("player");
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	_player = (Player*) _ObjectManager->FindObject("player");
	this->_count++;
	this->EnemyMove();
	this->EnemyFire();
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

//에너미의 init을 관리한다.
void Enemy::EnemyInit()
{
	//카운트 초기화
	_count = 0;
	//크기
	this->_size = Vector2(50, 50);
	//좌표기준 렉트 생성 요건
	this->_pivot = Pivot::CENTER;
	//속도
	_speed = 300.0f;
	//좌우확인
	_isLeft = false;
	//앵글값 초기화
	_angle = 0.f;
	//렉트 생성.
	_bullet = new Bullet;
	_bullet->Init(300, 700);
	this->UpdateRect();
}
//에너미의 움직임을 관리한다.
void Enemy::EnemyMove()
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

	if (_isLeft == false)
	{
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
}
//에너미의 총알을 발사하는 여부를 확인하고 플레이어를 타겟으로 총알을 발사한다.
void Enemy::EnemyFire()
{
	if (_count % 100 == 0)
	{
		_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		_bullet->Fire(Vector2(_position.x, _position.y), Vector2(10, 10), _angle, 60.0f);
		this->UpdateRect();
	}
}

