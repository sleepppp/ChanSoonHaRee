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

	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		_golemTopMove->SetSize(_golemTopMove->GetFrameSize(0));
		_golemTopMove->SetScale(1.0f);
		_golemTopMove->FrameRender(_position.x, _position.y, _golemTopMoveCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		_golemLeftMove->SetSize(_golemLeftMove->GetFrameSize(0));
		_golemLeftMove->SetScale(1.0f);
		_golemLeftMove->FrameRender(_position.x, _position.y, _golemLeftMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		_golemRightMove->SetSize(_golemRightMove->GetFrameSize(0));
		_golemRightMove->SetScale(1.0f);
		_golemRightMove->FrameRender(_position.x, _position.y, _golemRightMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		_golemBottomMove->SetSize(_golemBottomMove->GetFrameSize(0));
		_golemBottomMove->SetScale(1.0f);
		_golemBottomMove->FrameRender(_position.x, _position.y, _golemBottomMoveCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		_golemTopAttack->SetSize(_golemTopAttack->GetFrameSize(0));
		_golemTopAttack->SetScale(1.0f);
		_golemTopAttack->FrameRender(_position.x, _position.y, _golemTopAttackCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		_golemLeftAttack->SetSize(_golemLeftAttack->GetFrameSize(0));
		_golemLeftAttack->SetScale(1.0f);
		_golemLeftAttack->FrameRender(_position.x, _position.y, _golemLeftAttackCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		_golemRightAttack->SetSize(_golemRightAttack->GetFrameSize(0));
		_golemRightAttack->SetScale(1.0f);
		_golemRightAttack->FrameRender(_position.x, _position.y, _golemRightAttackCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		_golemBottomAttack->SetSize(_golemBottomAttack->GetFrameSize(0));
		_golemBottomAttack->SetScale(1.0f);
		_golemBottomAttack->FrameRender(_position.x, _position.y, _golemBottomAttackCount, 0, Pivot::CENTER, true);
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
	this->_sizeLeft = Vector2(-100, 10);
	this->_sizeRight = Vector2(100, 10);
	this->_sizeTop = Vector2(10, -100);
	this->_sizeBottom = Vector2(10, 100);
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

void Enemy::GolemImageInit()
{
	_ImageManager->AddFrameImage("GolemTopMove", L"../Resources/Enemy/Golem/GolemTopMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemLeftMove", L"../Resources/Enemy/Golem/GolemLeftMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemRightMove", L"../Resources/Enemy/Golem/GolemRightMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemBottomMove", L"../Resources/Enemy/Golem/GolemBottomMove.png", 47, 1);

	_ImageManager->AddFrameImage("GolemTopAttack", L"../Resources/Enemy/Golem/GolemTopAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemLeftAttack", L"../Resources/Enemy/Golem/GolemLeftAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemRightAttack", L"../Resources/Enemy/Golem/GolemRightAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemBottomAttack", L"../Resources/Enemy/Golem/GolemBottomAttack.png", 13, 1);

	this->_golemTopMove = _ImageManager->FindImage("GolemTopMove");
	this->_golemLeftMove = _ImageManager->FindImage("GolemLeftMove");
	this->_golemRightMove = _ImageManager->FindImage("GolemRightMove");
	this->_golemBottomMove = _ImageManager->FindImage("GolemBottomMove");

	this->_golemTopAttack = _ImageManager->FindImage("GolemTopAttack");
	this->_golemLeftAttack = _ImageManager->FindImage("GolemLeftAttack");
	this->_golemRightAttack = _ImageManager->FindImage("GolemRightAttack");
	this->_golemBottomAttack = _ImageManager->FindImage("GolemBottomAttack");


	this->_golemTopMoveCount = 0;
	this->_golemLeftMoveCount = 0;
	this->_golemRightMoveCount = 0;
	this->_golemBottomMoveCount = 0;

	this->_golemTopAttackCount = 0;
	this->_golemLeftAttackCount = 0;
	this->_golemRightAttackCount = 0;
	this->_golemBottomAttackCount = 0;

	this->_state = StateType::Chasing;
	this->_move = MoveType::Left;

}

void Enemy::GolemImageCount()
{
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		if (_count % 5 == 0)
		{
			_golemTopMoveCount++;
		}
		if (_golemTopMoveCount > 47)
		{
			_golemTopMoveCount = 0;
		}
	}
	else
		_golemTopMoveCount = 0;

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		if (_count % 5 == 0)
		{
			_golemLeftMoveCount++;
		}
		if (_golemLeftMoveCount > 47)
		{
			_golemLeftMoveCount = 0;
		}
	}
	else
		_golemLeftMoveCount = 0;
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		if (_count % 5 == 0)
		{
			_golemRightMoveCount++;
		}
		if (_golemRightMoveCount > 47)
		{
			_golemRightMoveCount = 0;
		}
	}
	else
		_golemRightMoveCount = 0;

	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		if (_count % 5 == 0)
		{
			_golemBottomMoveCount++;
		}
		if (_golemBottomMoveCount > 47)
		{
			_golemBottomMoveCount = 0;
		}
	}
	else
		_golemBottomMoveCount = 0;


	if (_state == StateType::attack && _move == MoveType::Top)
	{
		if (_count % 5 == 0)
		{
			_golemTopAttackCount++;
		}
		if (_golemTopAttackCount > 13)
		{
			_golemTopAttackCount = 0;
		}
	}
	else
		_golemTopAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		if (_count % 5 == 0)
		{
			_golemLeftAttackCount++;
		}
		if (_golemLeftAttackCount > 13)
		{
			_golemLeftAttackCount = 0;
		}
	}
	else
		_golemLeftAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		if (_count % 5 == 0)
		{
			_golemRightAttackCount++;
		}
		if (_golemRightAttackCount > 13)
		{
			_golemRightAttackCount = 0;
		}
	}
	else
		_golemRightAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		if (_count % 5 == 0)
		{
			_golemBottomAttackCount++;
		}
		if (_golemBottomAttackCount > 13)
		{
			_golemBottomAttackCount = 0;
		}
	}
	else
		_golemBottomAttackCount = 0;


}
//무브 상황
void Enemy::Move()
{
	// 난 항상 플레이어를 중심으로 움직일 거야
	this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	if (_state == StateType::Chasing)
	{
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//움직일때마다 새로 그려줘
		this->UpdateMainRect();
	}
	if (_state == StateType::Attacked && this->_isAttackedCount < 200)
	{
		this->_position.x += cosf(_angle - Math::PI) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle - Math::PI) * _speed * _TimeManager->DeltaTime();
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
	if (_attackCount > 300)
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
		if (_move == MoveType::Left && _attackCount > 280)
		{
			_isAttackLeft = true;
			this->_attackLeft = Figure::RectMakeCenter({ _position.x - 60, _position.y }, _sizeLeft);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 280)
		{
			_isAttackRight = true;
			this->_attackRight = Figure::RectMakeCenter({ _position.x + 60, _position.y }, _sizeRight);
		}
		else _isAttackRight = false;

		if (_move == MoveType::Top && _attackCount > 280)
		{
			_isAttackTop = true;
			this->_attackTop = Figure::RectMakeCenter({ _position.x ,_position.y - 60 }, _sizeTop);
		}
		else _isAttackTop = false;

		if (_move == MoveType::Bottom && _attackCount > 280)
		{
			_isAttackBottom = true;
			this->_attackBottom = Figure::RectMakeCenter({ _position.x, _position.y + 60 }, _sizeBottom);
		}
		else _isAttackBottom = false;
	}
}

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





