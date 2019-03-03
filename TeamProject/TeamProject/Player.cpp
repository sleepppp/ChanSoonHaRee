#include "stdafx.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"

using namespace Figure;

Player::Player()
{	
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");	

	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->UpdateMainRect();
	this->_speed = 0.8515611f;
	
	this->_standRate = 0.5f;				//프레임 장당 시간
	this->_runRate = 0.082588f;				//달리기용 프레임 시간
	this->_frameCount = 0.f;				//프레임타이머를 위한 변수
	this->_changeIndexX = 0.f;				//각 X프레임 개수가 달라 변경값을 쉽게 넣기 위한 변수 선언	
	this->_isRolling = false;				//구르는 중인지 판단 bool값
	
	_rollCount = 0;							//
	_hp = 100;								//
	_demage = 10;							//

	//애니메이션클래스 사용
	_animation = new Animation;
	_animation->SetStartEndFrame(0, 9, 10, 9, false);
	_animation->SetFrameUpdateTime(0.1f);
	_animation->SetIsLoop(false);
	_animation->Play();

	//첫 행동을 위한 기본값
	this->_frameIndexX = 0.f;				//프레임가로X
	this->_frameIndexY = 11.f;				//11은 기본 정면을 바라보게 하기 위한 값(정면)	
	this->Move(StateMove::stand_D);			//최초 모션 상태 (정면보기)		
	this ->_rate = _standRate;

	//충돌판정으로 받아서 결과를 줄지 받을지 협의할것
	//공격을 위한 렉트(사이즈와 위치를 위한 변수를 새로 생성할 것)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);	//무기용 렉트 생성
	//_shieldRc = RectMakeCenter(_position.x, _position.y, 100, 100); //방패용 렉트 생성		
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2); //충돌판정용 렉트 생성
	//검Rc와 화살Rc를 따로 만들지, 상황에 사이즈만 변경할지 생각해 보기
	//정밀 충돌용 렉트 위치 초기화d
	this->_collisionRect = Figure::RectMakeCenter(_position, Vector2(60.f, 60.f));
}
Player::~Player() {}
void Player::Init() {}
void Player::Release() 
{
	//SafeDelete(_image);
	//SafeDelete(_animation);
}

void Player::Update()
{		
	this->Move(_stateMove);
	
	//이동량 측정할 변수
	Vector2 moveValue(0, 0);

	//구르기명령
	if (_Input->GetKeyDown(VK_SPACE))	
	{		
		_isRolling = true;
	}

	//구르기:조건시작
	if (_isRolling)
	{
		if (_stateMove==StateMove::stand_L || _stateMove == StateMove::run_L)
		{
			_stateMove = StateMove::roll_L;
		}
		if (_stateMove == StateMove::stand_R || _stateMove == StateMove::run_R)
		{			
			_stateMove = StateMove::roll_R;
		}
		if (_stateMove == StateMove::stand_U || _stateMove == StateMove::run_U)
		{
			_stateMove = StateMove::roll_U;
		}
		if (_stateMove == StateMove::stand_D || _stateMove == StateMove::run_D)
		{
			_stateMove = StateMove::roll_D;
		}
	}

	//구르기:완료 후 스탠드 동작으로 돌아가기
	if (!_isRolling)
	{				
		this->DefaultMove(); //기본동작
		if (_stateMove == StateMove::roll_L) this->DefaultMove();	
		if (_stateMove == StateMove::roll_R) this->DefaultMove();
		if (_stateMove == StateMove::roll_U) this->DefaultMove();
		if (_stateMove == StateMove::roll_D) this->DefaultMove();			
	}	
		
	//속도값
	if (_stateMove == StateMove::run_L)
	{		
		if (_Input->GetKey(VK_LEFT))
		{
			_position.x -= _speed;
		}
		else if (_Input->GetKey(VK_UP))
		{
			_position.x -= _speed;
			_position.y -= _speed;
			//_position.x -= direction.Normalize() * _speed * _TimeManager->DeltaTime();
			//Vector2 moveValue(-1.0f, -1.0f);
			//_position += moveValue.Normalize() * _speed * _TimeManager->DeltaTime();
		}
		else if (_Input->GetKeyUp(VK_DOWN))
		{
			//Vector2 moveValue(-1.0f, 1.0f);
			//_position += moveValue.Normalize() * _speed * _TimeManager->DeltaTime();
			_position.x -= _speed;
			_position.y += _speed;
		}
		//this->_position += direction.Normalize() * _speed * _TimeManager->DeltaTime();
		//_position += Vector2(-1.f, 0.f);
	}
	

	if (_stateMove == StateMove::run_R)
	{
		_position.x += _speed;
	}

	if (_stateMove == StateMove::run_U)
	{
		_position.y -= _speed;
	}

	if (_stateMove == StateMove::run_D)
	{
		_position.y += _speed;
	}

	if (_stateMove == StateMove::roll_L)	_position.x -= _speed *2;
	if (_stateMove == StateMove::roll_R)	_position.x += _speed *2;
	if (_stateMove == StateMove::roll_U)	_position.y -= _speed *2;
	if (_stateMove == StateMove::roll_D)	_position.y += _speed *2;


	//애니메이션 동작	
	this->_frameCount += _TimeManager->DeltaTime();		//리얼타임을 프레임시간에 더해준다

	//장당 지정시간 rate보다 값이 커질때 프레임을 넘긴다
	if (_frameCount >= _rate)
	{
		this->_frameIndexX++;	//다음프레임으로 이동
		
		if (_isRolling)
		{
			_rollCount++;
		}
		//프레임값이 커져서 넘어왔으니 다시 값을 빼준다.
		while (_frameCount >= _rate) this->_frameCount -= this->_rate;
		
		//만약 프레임인덱스X가 맥스와 같거나 커지면 0으로 초기화
		if (this->_changeIndexX <= this->_frameIndexX)
		{			
			this->_frameIndexX = 0;
		}
		if (_rollCount == 7)
		{
			_rollCount = 0;
			_isRolling = false;
		}
	}

	//충돌판정렉트
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);
	//무기용 렉트 생성(사이즈와 위치를 위한 변수를 새로 생성할 것)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);
	
}

void Player::Render()
{	
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER);
	
	//충돌판정렉트 확인용(확인후 삭제할 것)
	//_DXRenderer->DrawRectangle(_colliRc, DefaultBrush::blue, false, 2.0f);
	//무기용 렉트 확인용(확인후 삭제할 것)
	_DXRenderer->DrawRectangle(_weaponRc, DefaultBrush::red, false, 2.0f);
}



//추가함수:상하좌우(스탠드, 달리기)
void Player::Move(StateMove _move)
{
	switch (_move)
	{
	case StateMove::stand_L:
		this->_frameIndexY = 9;
		this->_changeIndexX = 10;
		this->_rate=_standRate;
		break;

	case StateMove::stand_R:
		this->_frameIndexY = 8;
		this->_changeIndexX = 10;
		this->_rate = _standRate;
		break;

	case StateMove::stand_U:
		this->_frameIndexY = 10;
		this->_changeIndexX = 10;
		this->_rate = _standRate;
		break;

	case StateMove::stand_D:
		this->_frameIndexY = 11;
		this->_changeIndexX = 10;
		this->_rate = _standRate;
		break;

	case StateMove::run_L:		
		this->_frameIndexY = 3;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::run_R:
		this->_frameIndexY = 2;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::run_U:
		this->_frameIndexY = 0;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::run_D:
		this->_frameIndexY = 1;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::roll_L:		
		this->_frameIndexY = 5;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::roll_R:
		//_position.x += _speed * 2;
		this->_frameIndexY = 4;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::roll_U:
		//_position.y -= _speed * 2;
		this->_frameIndexY = 6;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	case StateMove::roll_D:
		this->_frameIndexY = 7;
		this->_changeIndexX = 7;
		this->_standRate = _runRate;
		break;

	default:
		break;
	}
}

void Player::DefaultMove()
{
	if (_Input->GetKeyUp(VK_LEFT))  _stateMove = StateMove::stand_L;
	if (_Input->GetKeyUp(VK_RIGHT))  _stateMove = StateMove::stand_R;
	if (_Input->GetKeyUp(VK_UP))  _stateMove = StateMove::stand_U;
	if (_Input->GetKeyUp(VK_DOWN))  _stateMove = StateMove::stand_D;

	if (_Input->GetKey(VK_LEFT)) _stateMove = StateMove::run_L;
	if (_Input->GetKey(VK_RIGHT)) _stateMove = StateMove::run_R;
	if (_Input->GetKey(VK_UP)) _stateMove = StateMove::run_U;
	if (_Input->GetKey(VK_DOWN)) _stateMove = StateMove::run_D;
}


//뎀지 넘기기
//void Player::AttackedDemege(int damage)
//{
//	_hp -= damage;
//	if (_hp <= 0)
//	{
//		this->Destroy();
//	}
//	else
//	{
//
//	}
//}