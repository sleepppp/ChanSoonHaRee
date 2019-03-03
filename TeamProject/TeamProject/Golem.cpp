#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"
#include "Golem.h"


Golem::Golem(Vector2 pos)
{
	//에너미의 자시자신 기본 설정.
	this->_name = "Golem";					//내이름은 골램이여
	this->_position = pos;					//100, 100 지점에서 시작하지
	this->_size = Vector2(100, 100);		//크기도 100, 100이야
	this->_pivot = Pivot::CENTER;			//내 기준은 중심에있어
	this->_speed = 90.0f;					//속도는 90.0f
	this->_hp = 200;						//200의 체력
	this->_demage = 34;						//34의 뎀지

	this->_isAttack = false;				//공격은 처음에는 안하고있지
	this->_renderRect = UpdateRect(_renderRect, _position, _size, Pivot::CENTER);

	//내 이미지 찾기!
	this->_golemMove = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4);
	this->_golemAttack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);

	//각종 카운트 초기화
	this->_moveCount = 0;
	this->_attackCount = 0;
	this->_attackedCount = 0;
	this->_countMove = 0.f;
	this->_countAttack = 0.f;
	//공격 렉트를 위한 포지션 초기화
	this->_positionLeft = Vector2(_position.x - 110, _position.y + 10);
	this->_positionRight = Vector2(_position.x + 10, _position.y + 15);
	this->_positionTop = Vector2(_position.x, _position.y - 10);
	this->_positionBottom = Vector2(_position.x, _position.y + 110);
	//공격 렉트를 위한 사이즈 설정 및 초기화
	this->_sizeLeft = Vector2(100, 20);
	this->_sizeRight = Vector2(100, 20);
	this->_sizeTop = Vector2(20, 70);
	this->_sizeBottom = Vector2(20, 80);
	//공격여부확인을 위한 불변수 초기화
	this->_isAttackTop = false;
	this->_isAttackLeft = false;
	this->_isAttackRight = false;
	this->_isAttackBottom = false;
	//공격렉트 초기화
	this->_attackLeft = UpdateRect(_attackLeft, _positionLeft, _sizeLeft, Pivot::LEFT_TOP);
	this->_attackRight = UpdateRect(_attackRight, _positionRight, _sizeRight, Pivot::LEFT_TOP);
	this->_attackTop = UpdateRect(_attackTop, _positionTop, _sizeTop, Pivot::BOTTOM);
	this->_attackBottom = UpdateRect(_attackBottom, _positionBottom, _sizeBottom, Pivot::BOTTOM);
}

Golem::~Golem()
{
}

void Golem::Init()
{
	Enemy::Init();
}

void Golem::Release()
{

}

void Golem::Update()
{
	_countMove +=_TimeManager->DeltaTime();
	if (_countMove >= 1.f /6.0f)
	{
		_countMove = 0;
		_moveCount++;
	}

	this->Move();

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

//프레임 돌리기 위한 함수.
void Golem::ImageCount()
{
	//이미지 프레임돌리기(쫒는상태)
	if (_state == StateType::Chasing)
	{
		if (_moveCount >= 8)
			_moveCount = 0;
	}

	//이미지 프레임 돌리기 (공격상태)
	if (_state == StateType::attack)
	{
		if (_attackCount > 14)
			_attackCount = 0;
	}
}

//공격 사거리를 계산하기 위해서 직선거리계산 및 판정 범위 안일경우 상태 변경
void Golem::Attack()
{
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	if (_distance < (_size.x * 1.2f))
	{
		_state = StateType::attack;
	}
	if (_state == StateType::attack)
	{
		_countAttack +=_TimeManager->DeltaTime();
		if (_countAttack >= 1.f / 8.0f)
		{
			_countAttack = 0;
			_attackCount++;
		}
	}
	if (_attackCount > 12)
	{
		_attackCount = 0;
		_state = StateType::Chasing;
	}
}

void Golem::AttackPosition()
{
	this->_positionLeft = Vector2(_position.x - 110, _position.y + 10);
	this->_positionRight = Vector2(_position.x + 10, _position.y + 15);
	this->_positionTop = Vector2(_position.x, _position.y - 10);
	this->_positionBottom = Vector2(_position.x, _position.y + 110);

	if (_state == StateType::attack)
	{
  		if (_move == MoveType::Left && _attackCount > 9)
		{
			this->_isAttackLeft = true;
			this->_attackLeft = UpdateRect(_attackLeft, _positionLeft, _sizeLeft, Pivot::LEFT_TOP);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 9)
		{
			this->_isAttackRight = true;
			this->_attackRight = UpdateRect(_attackRight, _positionRight, _sizeRight, Pivot::LEFT_TOP);
		}
		else _isAttackRight = false;
		if (_move == MoveType::Top && _attackCount > 9)
		{
			this->_isAttackTop = true;
			this->_attackTop = UpdateRect(_attackTop, _positionTop, _sizeTop, Pivot::BOTTOM);
		}
		else _isAttackTop = false;
		if (_move == MoveType::Bottom && _attackCount > 9)
		{
			this->_isAttackBottom = true;
			this->_attackBottom = UpdateRect(_attackBottom, _positionBottom, _sizeBottom, Pivot::BOTTOM);
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
	//공격에 성공했으면?
	if (_isAttack == true)
	{
		//내 뎀지를 넘겨줘라.
		//_player->AttackedDemege(0);
		_isAttack = false;
	}
}

void Golem::RectRender()
{
	if (_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::gray);
		if (_state == StateType::Chasing)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.2f), DefaultBrush::blue);
		}
		if (_state == StateType::attack)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.2f), DefaultBrush::red);
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