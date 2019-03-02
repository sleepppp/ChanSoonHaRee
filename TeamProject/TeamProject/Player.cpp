#include "stdafx.h"
#include "Image.h"
#include "Player.h"
//#include "Animation.h"
using namespace Figure;

Player::Player()
{
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_isActive = true;
	this->GetLive();	//?

	this->_pivot = Pivot::CENTER;
	this->UpdateMainRect();
	this->_speed = 0.5f;

	this->_frameCount = 0.f;		//프레임타이머를 위한 변수

	this->_standRate = 0.5f;		//프레임 장당 시간
	this->_runRate = 0.082588f;		//달리기용 프레임 시간
	this->_changeIndexX = 0.f;		//각 X프레임 개수가 달라 변경값을 쉽게 넣기 위한 변수 선언	
	_ImageManager->AddFrameImage("Will", L"../Resources/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");

	//첫 행동을 위한 기본값

	this->_frameIndexX = 0.f;		//프레임가로X
	this->_frameIndexY = 11.f;		//11은 기본 정면을 바라보게 하기 위한 값(정면)	
	this->_state = State::stand_D;	//최초 모션 상태 	



}
Player::~Player()
{
}
void Player::Init()
{

}
void Player::Release()
{

}
void Player::Update()
{
	//롤링롤링
	if (_Input->GetKey(VK_SPACE))
	{
		this->_state = State::end;	//우선권을 위해 enum값의 값을 빼준다
		_isRolling = true;

		if (_Input->GetKeyUp(VK_LEFT) || _Input->GetKey(VK_LEFT))
		{
			_position.x -= _speed * 2;
			//this->rolling = true;	
			this->_frameIndexY = 5;
			this->_changeIndexX = 7;
			this->_standRate = 0.05f;
		}
	}

	//롤링을 우선시하기 위한 조건
	if (!_isRolling)
	{
		if (_Input->GetKeyUp(VK_LEFT))		_state = State::stand_L;
		if (_Input->GetKeyUp(VK_RIGHT))		_state = State::stand_R;
		if (_Input->GetKeyUp(VK_UP))		_state = State::stand_U;
		if (_Input->GetKeyUp(VK_DOWN))		_state = State::stand_D;

		//switch:상태처리는 ok, 이동값 등은 no
		if (_Input->GetKey(VK_LEFT))
		{
			_state = State::run_L;
			_position.x -= _speed;
		}
		if (_Input->GetKey(VK_RIGHT))
		{
			_state = State::run_R;
			_position.x += _speed;
			//cout << "asd" << endl;
		}
		if (_Input->GetKey(VK_UP))
		{
			_state = State::run_U;
			_position.y -= _speed;
		}
		if (_Input->GetKey(VK_DOWN))
		{
			_state = State::run_D;
			_position.y += _speed;
		}

		switch (_state)
		{
		case State::stand_L:
			this->_frameIndexY = 9;
			this->_changeIndexX = 10;
			this->_standRate = 0.4f;

			break;

		case State::stand_R:
			this->_frameIndexY = 8;
			this->_changeIndexX = 10;
			this->_standRate = 0.4f;
			break;

		case State::stand_U:
			this->_frameIndexY = 10;
			this->_changeIndexX = 10;
			this->_standRate = 0.4f;
			break;

		case State::stand_D:
			this->_frameIndexY = 11;
			this->_changeIndexX = 10;
			this->_standRate = 0.4f;
			break;

		case State::run_L:
			this->_frameIndexY = 3;
			this->_changeIndexX = 7;
			this->_standRate = _runRate;

			break;

		case State::run_R:
			this->_frameIndexY = 2;
			this->_changeIndexX = 7;
			this->_standRate = _runRate;
			break;

		case State::run_U:
			this->_frameIndexY = 0;
			this->_changeIndexX = 7;
			this->_standRate = _runRate;
			break;

		case State::run_D:
			this->_frameIndexY = 1;
			this->_changeIndexX = 7;
			this->_standRate = _runRate;
			break;

		default:
			break;
		}
	}


	//리얼타임을 프레임시간에 더해준다
	this->_frameCount += _TimeManager->DeltaTime();

	//프레임카운트당 인덱스 한장씩 플러스
	if (_frameCount >= _standRate)
	{
		this->_frameIndexX++;	//다음프레임으로 이동

		//프레임값이 커져서 넘어왔으니 다시 값을 빼준다.
		while (_frameCount >= _standRate) this->_frameCount -= this->_standRate;

		//만약 프레임인덱스X가 맥스와 같거나 커지면 0으로 초기화
		if (this->_changeIndexX <= _frameIndexX) this->_frameIndexX = 0;
	}
}

void Player::Render()
{
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER, true);
}