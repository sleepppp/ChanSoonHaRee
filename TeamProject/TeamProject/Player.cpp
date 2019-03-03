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
	this->_speed = 0.5f;
	
	this->_standRate = 0.5f;				//프레임 장당 시간
	this->_runRate = 0.082588f;				//달리기용 프레임 시간
	this->_frameCount = 0.f;				//프레임타이머를 위한 변수
	this->_changeIndexX = 0.f;				//각 X프레임 개수가 달라 변경값을 쉽게 넣기 위한 변수 선언	
	this->_isRolling = false;				//구르는 중인지 판단 bool값
	
	_rollCount = 0;

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
	//_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);	//무기용 렉트 생성
	//_shieldRc = RectMakeCenter(_position.x, _position.y, 100, 100); //방패용 렉트 생성		
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2); //충돌판정용 렉트 생성
	//검Rc와 화살Rc를 따로 만들지, 상황에 사이즈만 변경할지 생각해 보기
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
			this->Move(StateMove::roll_L);
		}
	}
	//구르기:완료 후 스탠드 동작으로 돌아가기
	if (!_isRolling)
	{
		if (_stateMove == StateMove::roll_L)
		{
			this->Move(StateMove::stand_L);
		}
	}

	//기본동작
	if (_Input->GetKeyUp(VK_LEFT))
	{
		this->Move(StateMove::stand_L);
	}
	if (_Input->GetKeyDown(VK_LEFT))
	{
		this->Move(StateMove::run_L);
	}

	//애니메이션 동작	
	this->_frameCount += _TimeManager->DeltaTime();		//리얼타임을 프레임시간에 더해준다

	if (_frameCount >= _rate)						//프레임카운트당 인덱스 한장씩 플러스
	{
		this->_frameIndexX++;	//다음프레임으로 이동
		if (_isRolling)
		{
			_rollCount++;
			//_position.x -= _speed;
		}
		
		//프레임값이 커져서 넘어왔으니 다시 값을 빼준다.
		while (_frameCount >= _rate) this->_frameCount -= this->_rate;
		
		//만약 프레임인덱스X가 맥스와 같거나 커지면 0으로 초기화
		if (this->_changeIndexX <= this->_frameIndexX)
		{			
			this->_frameIndexX = 0;

			if (_rollCount == 6)
			{
				_rollCount = 0;
				_isRolling = false;
			}
		}
		
		
	}
	//this->UpdateMainRect();
	cout << "_frameCount:" << _frameCount << endl;
	cout << "_changeIndexX:" << _changeIndexX << endl;
	cout << "_frameIndexX: " << _frameIndexX << endl;
	cout << "_isRolling: " << _isRolling << endl;




	
	//_isRolling = false;

	/*	
	if (_Input->GetKeyUp(VK_RIGHT))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_R);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::stand_R);
			//_position.x += _speed;
		}
	}

	if (_Input->GetKeyUp(VK_UP))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_U);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::stand_U);
			//_position.y -= _speed;
		}
	}
	if (_Input->GetKeyUp(VK_DOWN))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_D);

		}
		if (!_isRolling)
		{
			this->Move(StateMove::stand_D);
			//_position.y -= _speed;
		}
	}
	//switch:상태처리는 ok, 이동값 등은 no
	if (_Input->GetKey(VK_LEFT))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_L);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::run_L);
			_position.x -= _speed;
		}
	}
	if (_Input->GetKey(VK_RIGHT))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_R);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::run_R);
			_position.x += _speed;
		}
	}
	if (_Input->GetKey(VK_UP))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_U);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::run_U);
			_position.y -= _speed;
		}
	}
	if (_Input->GetKey(VK_DOWN))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_D);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::run_D);
			_position.y += _speed;
		}
	}


	

	

	
	//충돌판정렉트
	_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);
	//무기용 렉트 생성(사이즈와 위치를 위한 변수를 새로 생성할 것)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);
	*/
}
//롤링중일때 _frameIndexX가 끝에 다다르면 _isRolling true
void Player::Render()
{
	if(_isRolling == true)
	{
		_image->SetSize(_size);
		_image->FrameRender(_position.x, _position.y, _animation->GetNowFrameX(), _animation->GetNowFrameY(), Pivot::CENTER);
	}
	if(_isRolling==false)
	{
		_image->SetSize(_size);
		_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER);
	}
	//충돌판정렉트 확인용(확인후 삭제할 것)
	//_DXRenderer->DrawRectangle(_colliRc, DefaultBrush::blue, false, 2.0f);
	//무기용 렉트 확인용(확인후 삭제할 것)
	//_DXRenderer->DrawRectangle(_weaponRc, DefaultBrush::red, false, 2.0f);
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
		//this->_frameIndexX = 0;		//먹힘?
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
		//_animation->UpdateFrame();
		//_animation->SetStartEndFrame(0, 5, 7, 5, false);
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