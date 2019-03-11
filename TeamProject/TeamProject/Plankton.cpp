#include "stdafx.h"
#include "Plankton.h"
#include "Player.h"
#include "MoveItem.h"


Plankton::Plankton(Vector2 position)
{
	//클래스 이름 (오브젝트 키)
	this->_name = "plankton";

	//프레임 이미지 추가
	this->_plankton = _ImageManager->FindImage("planktonIMG");
	this->_planktonRed = _ImageManager->FindImage("planktonRedIMG");
	this->_planktonWhite = _ImageManager->FindImage("planktonWhiteIMG");

	//포지션
	this->_position = position;
	//데미지
	this->_damage = 15;
	//HP	
	this->_hp = 75;
	//스피드
	this->_speed = 15.0f;
	//사이즈
	this->_size = Vector2(30, 30);
	//피벗
	this->_pivot = Pivot::CENTER;
	//렉트
	this->UpdateRect(_position, _size, _pivot);

	//기본 상태는 따라가기
	this->_planktonState = PlanktonState::Follow;
}


Plankton::~Plankton()
{
}

void Plankton::Init()
{
	//에너미 Init
	Enemy::Init();
}

void Plankton::Release()
{
}

void Plankton::Update()
{


	//플랑크톤 상태 함수
	PlanktonStates();
}

void Plankton::Render()
{
}

void Plankton::PlanktonStates()
{
	switch (_planktonState)
	{
	//상태 : 따라가기 Follow
	case Plankton::PlanktonState::Follow:
		//앵글 값 구하기
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		//구한 앵글 값으로 플레이어한테 이동시키기
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y -= sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//렉터 업데이트
		this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);


		break;
	case Plankton::PlanktonState::Attack:


		break;
	case Plankton::PlanktonState::Attacked:

		break;
	case Plankton::PlanktonState::End:
		break;
	default:
		break;
	}
}
