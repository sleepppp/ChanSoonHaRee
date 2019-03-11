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

	_isAttack = false;
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
	//오브젝트 충돌 체크 함수
	this->ObjectCollision();

	//플랑크톤 상태 함수
	PlanktonStates();
}

void Plankton::Render()
{
	//_plankton->SetSize(_)
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

		//플랑크톤 렉트와 플레이어 렉트가 충돌하면 상태를 공격 상태로 변경
		RECT temp;
		if (IntersectRect(&temp, &_renderRect, &_player->GetMainRect())) 
		{
			//공격 상태 변경
			_planktonState = PlanktonState::Attack;
		}
		break;

	//상태 : 공격 Attack
	case Plankton::PlanktonState::Attack:
		//공격 true
		_isAttack = true;
		//공격이 true이면
		if (_isAttack == true) 
		{
			//공격 렉트 생성
			_atkRect = UpdateRect(_position, _size, Pivot::CENTER);
			//공격 렉트와 플레이어 렉트가 충돌하면
			if (IntersectRect(&temp, &_atkRect, &_player->GetMainRect())) 
			{
				//공격 false
				_isAttack = false;
				//피격 상태 변경
				_planktonState = PlanktonState::Attacked;
			}
		}
		else 
		{

		}
		break;

	//상태 : 피격 Attacked
	case Plankton::PlanktonState::Attacked:
		//피격 : 플레이어 데미지 받기
		this->AttackedDemege(_player->GetPlayerDamage());

		//피격 상태인 경우, 밀리기와 컬러 렌더 시간 조절용 함수
		this->AtkedState(_position, this->_attackedAngle, 50.f, 0.3f);
		break;
	case Plankton::PlanktonState::End:
		break;
	default:
		break;
	}
}


//피격 상태인 경우, 밀리기와 컬러 렌더 시간 조절용 함수
void Plankton::AtkedState(Vector2 position, float angle, float speed, float countValue)
{
	//델타 타임
	float deltaTimeCount = 0.f;
	//델타 타임++
	deltaTimeCount += _TimeManager->DeltaTime();
	
	//피격 카운트
	float atkedCount = 0.f;
	//피격 카운트++
	atkedCount += _TimeManager->DeltaTime();

	//델타 타임 0.5초보다 작거나 같아지면
	if (deltaTimeCount <= 0.5f) 
	{
		//포지션과 렉트 조정
		position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
		position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(position, _size, Pivot::CENTER);

		//피격 카운트에 따라 피격 렌더 설정하기
		if (atkedCount <= countValue)
		{
			//피격 렌더 (흰색)
			_isAtkedRender = false;
		}
		else if (atkedCount > countValue)
		{
			//피격 렌더 (빨강색)
			_isAtkedRender = true;

			//피격 카운트 값 초기화
			countValue = 0;
		}
	}
	//델타 타임 0.5초보다 커지면
	else if (deltaTimeCount > 0.5f) 
	{
		//델타 타임 초기화
		deltaTimeCount = 0;
		//상태 : 따라가기 변경
		_planktonState = PlanktonState::Follow;
	}
}
