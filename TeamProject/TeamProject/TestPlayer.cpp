#include "stdafx.h"
#include "TestPlayer.h"

#include "Image.h"
#include "Animation.h"


TestPlayer::TestPlayer()
{
}


TestPlayer::~TestPlayer()
{
}

/***********************************************************************************
## Init ##
************************************************************************************/
void TestPlayer::Init()
{
	//이미지 추가 및 매니져로부터 찾아온다. 
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");
	//기본 변수들 초기화 
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(WinSizeX / 2 + 300, WinSizeY / 2);
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_speed = 300.0f;
	this->UpdateMainRect();
	//정밀 충돌용 렉트 위치 초기화d
	this->_collisionRect = Figure::RectMakeCenter(_position, Vector2(60.f, 60.f));
	//상태별로 애니메이션 전부 생성해서 맵에 담아둔다. 
	this->CreateAnimation();
	//처음 시작 상태는 DownIdle로 
	this->ChangeState(State::DownIdle);
}
/***********************************************************************************
## Release ##
애니메이션은 이 객체가 생성했고 관리하므로 이곳에서 삭제해주어야 한다. 
************************************************************************************/
void TestPlayer::Release()
{
	AnimationIter iter = _animationList.begin();
	for (; iter != _animationList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	_animationList.clear();
}
/***********************************************************************************
## Update ##

************************************************************************************/
void TestPlayer::Update()
{
	//이동량 측정할 변수
	Vector2 moveValue(0,0);
	//상태에 따라 다르게 업데이트
	switch (_state)
	{
	case TestPlayer::State::LeftIdle:
		//키 입력에 따라 
		this->IdleKeyInput();
		break;
	case TestPlayer::State::RightIdle:
		this->IdleKeyInput();
		break;
	case TestPlayer::State::UpIdle:
		this->IdleKeyInput();
		break;
	case TestPlayer::State::DownIdle:
		this->IdleKeyInput();
		break;
	case TestPlayer::State::LeftRun:
		if (_Input->GetKey('A'))
			moveValue += Vector2(-1.f, 0.f);
		else if (_Input->GetKeyUp('A'))
			this->ChangeState(State::LeftIdle);

		if (_Input->GetKey('W'))
			moveValue += Vector2(0.f, -1.f);
		else if (_Input->GetKey('S'))
			moveValue += Vector2(0.f, 1.f);
		break;
	case TestPlayer::State::RightRun:
		if (_Input->GetKey('D'))
			moveValue += Vector2(1.f, 0.f);
		else if (_Input->GetKeyUp('D'))
			this->ChangeState(State::RightIdle);

		if (_Input->GetKey('W'))
			moveValue += Vector2(0.f, -1.f);
		else if (_Input->GetKey('S'))
			moveValue += Vector2(0.f, 1.f);
		break;
	case TestPlayer::State::UpRun:
		if (_Input->GetKey('W'))
			moveValue += Vector2(0.f, -1.f);
		else if (_Input->GetKeyUp('W'))
			this->ChangeState(State::UpIdle);

		if (_Input->GetKey('A'))
			moveValue += Vector2(-1.f, 0.f);
		else if (_Input->GetKey('D'))
			moveValue += Vector2(1.f, 0.f);
		break;
	case TestPlayer::State::DownRun:
		if (_Input->GetKey('S'))
			moveValue += Vector2(0.f, 1.f);
		else if (_Input->GetKeyUp('S'))
			this->ChangeState(State::DownIdle);

		if (_Input->GetKey('A'))
			moveValue += Vector2(-1.f, 0.f);
		else if (_Input->GetKey('D'))
			moveValue += Vector2(1.f, 0.f);
		break;
		break;
	default:
		break;
	}
	
	if(FLOAT_EQUAL(moveValue.x,0.f) == false || FLOAT_EQUAL(moveValue.y,0.f) == false)
		this->Move(moveValue);
	_mainAnimation->UpdateFrame();
}
/***********************************************************************************
## Render ##
************************************************************************************/
void TestPlayer::Render()
{
	_image->SetSize(_size);
	_image->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(),
		_mainAnimation->GetNowFrameY(), Pivot::CENTER, true);

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_collisionRect, DefaultBrush::red, true);
	}
}
/***********************************************************************************
## ChangeState ##
@@ State state : 바꿀 상태
************************************************************************************/
void TestPlayer::ChangeState(State state)
{
	_state = state;
	this->ChangeAnimation(state);

	switch (_state)
	{
	case TestPlayer::State::LeftIdle:
		break;
	case TestPlayer::State::RightIdle:
		break;
	case TestPlayer::State::UpIdle:
		break;
	case TestPlayer::State::DownIdle:
		break;
	case TestPlayer::State::LeftRun:
		break;
	case TestPlayer::State::RightRun:
		break;
	case TestPlayer::State::UpRun:
		break;
	case TestPlayer::State::DownRun:
		break;
	default:
		break;
	}
}

/**********************************************************************************
## Move ##
@@ Vector2 direction : 방향
************************************************************************************/
void TestPlayer::Move(Vector2 direction)
{
	this->_position += direction.Normalize() * _speed * _TimeManager->DeltaTime();
	_collisionRect = Figure::RectMakeCenter(_position, Vector2(60.f, 60.f));
	this->UpdateMainRect();
}
/***********************************************************************************
## ChangeAnimation ##
************************************************************************************/
void TestPlayer::ChangeAnimation(State state)
{
	AnimationIter iter = _animationList.find(state);
	if (iter != _animationList.end())
	{
		_mainAnimation = iter->second;
		_mainAnimation->Stop();
		_mainAnimation->Play();
	}
}

/***********************************************************************************
## CreateAnimation ##
************************************************************************************/
void TestPlayer::CreateAnimation()
{
	Animation* leftIdle = new Animation;
	leftIdle->SetStartEndFrame(0, 9, 10, 9, false);
	leftIdle->SetIsLoop(true);
	leftIdle->SetFrameUpdateTime(0.5f);
	_animationList.insert(make_pair(State::LeftIdle, leftIdle));
	Animation* rightIdle = new Animation;
	rightIdle->SetStartEndFrame(0, 8, 10, 8, false);
	rightIdle->SetIsLoop(true);
	rightIdle->SetFrameUpdateTime(0.5f);
	_animationList.insert(make_pair(State::RightIdle, rightIdle));
	Animation* upIdle = new Animation;
	upIdle->SetStartEndFrame(0, 10, 10, 10, false);
	upIdle->SetIsLoop(true);
	upIdle->SetFrameUpdateTime(0.5f);
	_animationList.insert(make_pair(State::UpIdle, upIdle));
	Animation* downIdle = new Animation;
	downIdle->SetStartEndFrame(0, 11, 10, 11, false);
	downIdle->SetIsLoop(true);
	downIdle->SetFrameUpdateTime(0.5f);
	_animationList.insert(make_pair(State::DownIdle, downIdle));
	Animation* leftRun = new Animation;
	leftRun->SetStartEndFrame(0, 3, 7, 3, false);
	leftRun->SetIsLoop(true);
	leftRun->SetFrameUpdateTime(0.08f);
	_animationList.insert(make_pair(State::LeftRun, leftRun));
	Animation* rightRun = new Animation;
	rightRun->SetStartEndFrame(0, 2, 7, 2, false);
	rightRun->SetIsLoop(true);
	rightRun->SetFrameUpdateTime(0.08f);
	_animationList.insert(make_pair(State::RightRun, rightRun));
	Animation* upRun = new Animation;
	upRun->SetStartEndFrame(0, 0, 7, 0, false);
	upRun->SetIsLoop(true);
	upRun->SetFrameUpdateTime(0.08f);
	_animationList.insert(make_pair(State::UpRun, upRun));
	Animation* downRun = new Animation;
	downRun->SetStartEndFrame(0, 1, 7, 1, false);
	downRun->SetIsLoop(true);
	downRun->SetFrameUpdateTime(0.08f);
	_animationList.insert(make_pair(State::DownRun, downRun));
}

/***********************************************************************************
## IdleKeyInput ##
************************************************************************************/
void TestPlayer::IdleKeyInput()
{
	if (_Input->GetKeyDown('A'))
		this->ChangeState(State::LeftRun);
	else if (_Input->GetKeyDown('D'))
		this->ChangeState(State::RightRun);
	else if (_Input->GetKeyDown('W'))
		this->ChangeState(State::UpRun);
	else if (_Input->GetKeyDown('S'))
		this->ChangeState(State::DownRun);
}
