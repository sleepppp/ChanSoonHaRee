#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
	EnemyInit();
	GolemImageInit();
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

}

void Enemy::Release()
{

}

void Enemy::Update()
{
	_count++;
	//난 공격상태가 아니라면 움직일 수 있어
	if (_state == StateType::Chasing)
	{
		this->Move();
	}
	//하지만 공격상태라면 재자리에서 공격하지
	this->Attack();

	this->CardinalPointsAttack();
	//내가 바라보는 방향을 계산한 거지요!
	this->MoveType();
	//골램 이미지를 돌리기 위한 함수.
	this->GolemImageCount();
}

void Enemy::Render()
{
	//에너미 렉트 보여주기
	if (_Input->IsToggleKey('1'))
	{
		//나는 초록색깔의 생김새를 가지고있어
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::green);
		//공격이 아니라면 내 공격의 사거리가 파란색으로 보여요
		if (_state == StateType::Chasing)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::blue);
		}
		//공격시작중이라면 내 사거리가 빨간색으로 변해요
		if (_state == StateType::attack)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::red);
		}
		AttackRender();
	}
	//레프트 라이트 탑 바텀 순.
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 2, Pivot::CENTER, true);
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 1, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 3, Pivot::CENTER, true);
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 2, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 1, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 3, Pivot::CENTER, true);
	}

}

//에너미의 초기화상황
void Enemy::EnemyInit()
{
	this->_name = "Enemy";						//내 이름은 Enemy야
	this->_position = Vector2(100, 100);		//100, 100지점에서 출몰하지
	this->_size = Vector2(100, 100);				//크기는 50, 50 정도?
	this->_pivot = Pivot::CENTER;				//중심은 중앙이지!
	this->_speed = 90.0f;						//90.0f의 속도로 움직인다구!
	this->_isAttack = false;					//아직 널 공격하고 있지 않아
	this->_attackCount = 0;						//공격모션의 속도? 쯤될거야
	this->_hp = 100;
	this->_demege = 34;
	this->_isAttackedCount = 0;
	//공격 판정 여부와 공격 범위, 그를위한 렉트 생성! 
	this->_sizeLeft = Vector2(-100, 20);
	this->_sizeRight = Vector2(100, 20);
	this->_sizeTop = Vector2(20, -100);
	this->_sizeBottom = Vector2(20, 100);
	this->_isAttackTop = false;
	this->_isAttackLeft = false;
	this->_isAttackRight = false;
	this->_isAttackBottom = false;
	this->_attackLeft = Figure::RectMakeCenter(_position, _sizeLeft);
	this->_attackRight = Figure::RectMakeCenter(_position, _sizeRight);
	this->_attackTop = Figure::RectMakeCenter(_position, _sizeTop);
	this->_attackBottom = Figure::RectMakeCenter(_position, _sizeBottom);

	this->UpdateMainRect();						//나를 그려주고있지
}
//에너미 이미지 초기화 및 초기생성
void Enemy::GolemImageInit()
{
	//레프트 라이트 탑 바텀 순.
	this->_golemMove = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4);
	this->_golemAttack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);
	this->_golemMoveCount = 0;
	this->_golemAttackCount = 0;

	this->_state = StateType::Chasing;
	this->_move = MoveType::Left;

}
//에너미 이미지 카운트를 위한 함수.
void Enemy::GolemImageCount()
{
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}
}
//무브 상황
void Enemy::Move()
{
	// 난 항상 플레이어를 중심으로 움직일 거야
	if (_state == StateType::Chasing)
	{
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//움직일때마다 새로 그려줘
		this->UpdateMainRect();
	}
	if (_state == StateType::Attacked && this->_isAttackedCount < 200)
	{
		this->_angle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
		this->_position.x += cosf(_angle ) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle ) * _speed * _TimeManager->DeltaTime();
		//움직일때마다 새로 그려줘
		this->UpdateMainRect();
	}
}
//공격 상황
void Enemy::Attack()
{
	//플레이어와 나의 사이 거리를 재는 도구지!
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//만약 나와 플레이어간의 거리가 내 몸크기의 두배가 안된다면
	if (_distance < (_size.x * 2))
	{
		//난 공격을 시작할거야
		_state = StateType::attack;
	}
	//공격을 시작한다면?
	if (_state == StateType::attack)
	{
		//내 공격모션을 보여주기위한 카운트지!
		_attackCount++;
	}
	//카운트가 300보다 커진다면?!
	if (_attackCount > 800)
	{
		//난 이미 공격을 마쳤으니 카운트를 없애주고
		_attackCount = 0;
		//공격상태를 평상시 상태로 바꿀거야
		_state = StateType::Chasing;
	}
}
//공격 범위 안에 들어섰을때 어느 방향으로 공격할지의 처리.
void Enemy::MoveType()
{
	if (_angle > Math::PI / 4 && _angle < ((3 * Math::PI) / 4))
	{
		_move = MoveType::Top;
	}
	else if (_angle > ((3 * Math::PI) / 4) && _angle < (Math::PI + (Math::PI / 4)))
	{
		_move = MoveType::Left;
	}
	else if (_angle > (Math::PI + (Math::PI / 4)) && _angle < (Math::PI + ((3 * Math::PI) / 4)))
	{
		_move = MoveType::Bottom;
	}
	else
		_move = MoveType::Right;
}
//공격 렉트 구성.
void Enemy::AttackRender()
{
	//만약 탑부분이라면 
	if (this->_isAttackTop == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackTop, DefaultBrush::red);
	}
	//만약 레프트 부분이라면
	if (this->_isAttackLeft == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackLeft, DefaultBrush::red);
	}
	//만약 라이트 부분이라면
	if (this->_isAttackRight == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackRight, DefaultBrush::red);
	}
	//만약 바텀부분이라면
	if (this->_isAttackBottom == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackBottom, DefaultBrush::red);
	}
}
//내가 플레이어를 공격할때 의 상황들과 그에 맞는 공격설정 처리.
void Enemy::CardinalPointsAttack()
{
	if (_state == StateType::attack)
	{
		if (_move == MoveType::Left && _attackCount > 700)
		{
			_isAttackLeft = true;
			this->_attackLeft = Figure::RectMakeCenter({ _position.x - 60, _position.y }, _sizeLeft);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 700)
		{
			_isAttackRight = true;
			this->_attackRight = Figure::RectMakeCenter({ _position.x + 60, _position.y }, _sizeRight);
		}
		else _isAttackRight = false;

		if (_move == MoveType::Top && _attackCount > 700)
		{
			_isAttackTop = true;
			this->_attackTop = Figure::RectMakeCenter({ _position.x ,_position.y - 60 }, _sizeTop);
		}
		else _isAttackTop = false;

		if (_move == MoveType::Bottom && _attackCount > 700)
		{
			_isAttackBottom = true;
			this->_attackBottom = Figure::RectMakeCenter({ _position.x, _position.y + 60 }, _sizeBottom);
		}
		else _isAttackBottom = false;
	}
}
//어택을 위한 공격 상황.
void Enemy::Collision()
{
	RECT Temp = { 0 };
	if (IntersectRect(&Temp, &_attackLeft, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackTop, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackRight, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackBottom, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
}
//내 뎀지를 넘기기 위한 함수.
void Enemy::AttackedDemege(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		this->Destroy();
	}
	else
	{
		_state = StateType::Attacked;
		_isAttackedCount++;
		if (this->_isAttackedCount > 200)
		{
			this->_isAttackedCount = 0;
			_state = StateType::Chasing;
		}
	}
}





