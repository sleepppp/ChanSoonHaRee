#include "stdafx.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Timer.h"

using namespace Figure;
/********************************************************************************/
//## Init ##
/********************************************************************************/
void Player::Init()
{
	//�̹��� �߰�, �Ŵ������� FInd �Ͽ� ã�ƿ�
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");

	//�⺻ ���� �ʱ�ȭ
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_speed = 600.0f;
	//this->_speed = Vector2(300.0f, 300.0f);
	this->UpdateMainRect();

	//�ð��� �ѹ���!
	_frameRun = 0.1f;
	_frameIdle = 0.1f;

	//���� �浹�� ��Ʈ ��ġ �ʱ�ȭ
	this->_collisionRect = RectMakeCenter(_position, Vector2(60.f, 60.f));
	//���º� �ִϸ��̼� ���� �����Ͽ� �ʿ� ��Ƶд�.
	this->CreateAnimation();

	// ó�� ���� ���¸� ���� ����
	this->ChangeState(State::DownIdle);


	//_frameRoll = 0.1f;
}

/********************************************************************************/
//## Release ##
/********************************************************************************/
void Player::Release()
{
	AnimationIter iter = _animationList.begin();
	for (; iter != _animationList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	_animationList.clear();
}

/********************************************************************************/
//## Update ##
/********************************************************************************/
void Player::Update()
{
	//�̵��� ������ ����
	Vector2 moveValue(0, 0);

	//���¿� ���� �ٸ��� ������Ʈ
	switch (_state)
	{
	case Player::State::LeftIdle:
		//if (_Input->GetKeyDown('A')) this->ChangeState(State::LeftRun);
		//else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
		//
		//else if (_Input->GetKeyDown('D')) this->ChangeState(State::RightRun);
		//else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
		//
		//else if (_Input->GetKeyDown('W')) this->ChangeState(State::UpRun);
		//else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
		//
		//else if (_Input->GetKeyDown('S'))
		//{
		//	this->ChangeState(State::DownRun);
		//}






		this->IdleKeyInput();
		break;

	case Player::State::RightIdle:
		this->IdleKeyInput();
		break;

	case Player::State::UpIdle:
		this->IdleKeyInput();
		break;

	case Player::State::DownIdle:
		this->IdleKeyInput();
		break;


	case Player::State::LeftRun:
		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);	//�޴�����
		else if (_Input->GetKeyUp('A')) this->ChangeState(State::LeftIdle); //�޶���

		if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);	//��
		else if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);	//�Ʒ�
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
		break;

	case Player::State::RightRun:
		if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
		else if (_Input->GetKeyUp('D')) this->ChangeState(State::RightIdle);

		if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);
		else if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
		break;

	case Player::State::UpRun:
		if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);
		else if (_Input->GetKeyUp('W')) this->ChangeState(State::UpIdle);

		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
		else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
		break;

	case Player::State::DownRun:
		if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);
		else if (_Input->GetKeyUp('S')) this->ChangeState(State::DownIdle);

		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
		else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
		break;

	case Player::State::LeftRoll:
		if(_mainAnimation->UpdateFrame()) moveValue += Vector2(-2.0f, 0.0f);
		if (!_mainAnimation->UpdateFrame()) moveValue += Vector2(0.0f, 0.0f);

		//if(this->CreateAnimation->upRun)
		break;

	case Player::State::RightRoll:
		moveValue += Vector2(2.0f, 0.0f);
		break;

	case Player::State::UpRoll:
		moveValue += Vector2(0.0f, -2.0f);
		break;

	case Player::State::DownRoll:
		moveValue += Vector2(0.0f, 2.0f);
		break;

	default:
		break;
	}
	this->Move(moveValue);
	_mainAnimation->UpdateFrame();
}

/********************************************************************************/
//## Render ##
/********************************************************************************/
void Player::Render()
{
	//�̹��� ������ ����
	_image->SetSize(_size);
	//������
	_image->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);

	//����� ����� ����� ��Ʈ�� ������ (F1)
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_collisionRect, DefaultBrush::red, true);
	}
}

/********************************************************************************/
//## ChangeState ##
//���¸� �ٲ� ���� _state=state; ���ٴ� ���� �Լ��� ���ؼ� �����ϸ� 
//����� �� �ڵ� ������ ��������.
/********************************************************************************/
void Player::ChangeState(State state)
{
	//�� ���¿� �����ϴٸ� �����Ű�� �ʰ� ����������
	if (_state == state) return;

	//�� ���¿� �������� �ʴٸ� �����Ѵ�.
	_state = state;
	//���°� �ٲ�鼭 �ִϸ��̼ǵ� �����Ѵ�
	this->ChangeAnimation(state);


	//���°� �ٲ�� ���� ó���� ..������ ���� ����
	switch (_state)
	{
	case Player::State::LeftIdle:
		break;
	case Player::State::RightIdle:
		break;
	case Player::State::UpIdle:
		break;
	case Player::State::DownIdle:
		break;
	case Player::State::LeftRun:
		_speed = 300.0f;
		break;
	case Player::State::RightRun:
		break;
	case Player::State::UpRun:
		break;
	case Player::State::DownRun:
		break;
	case Player::State::LeftRoll:
		break;
	case Player::State::RightRoll:
		break;
	case Player::State::UpRoll:
		break;
	case Player::State::DownRoll:
		break;
	default:
		break;
	}
}

/********************************************************************************/
//## Move ##
//Vector2 direction:����
/********************************************************************************/
void Player::Move(Vector2 direction)
{
	//�� ��ǥ�� ����*���ǵ�*��ŸŸ��
	this->_position += direction.Normalize()*_speed*_TimeManager->DeltaTime();
	//�̵������� ���� �浹 ��Ʈ ��ġ�� �����Ѵ�.
	_collisionRect = RectMakeCenter(_position, Vector2(60.0f, 60.0f));
	//mainRect�� ��ġ�� ����
	this->UpdateMainRect();
}

/********************************************************************************/
//## ChangeAnimation ##
//���¿� ���� �ִϸ��̼��� �ٲ��ش�. (Ű���� State state)
/********************************************************************************/
void Player::ChangeAnimation(State state)
{
	//�ݺ��ڸ� ���� �ʿ��� �ش� Ű���� �ִϸ��̼��� ã�´�.
	AnimationIter iter = _animationList.find(state);

	//���� ���� �ƴϸ� ã�� ���̴� �� �ִϸ��̼��� �ٲ� �ִϸ��̼����� ��ü�Ѵ�.
	if (iter != _animationList.end())
	{
		_mainAnimation = iter->second;
		_mainAnimation->Stop();
		_mainAnimation->Play();
	}
}

/********************************************************************************/
//## CreateAnimation ##
//�ִϸ��̼� ���� �̸� ���� �� �ʱ�ȭ ���� �� �ʿ� ��Ƽ� ����
/********************************************************************************/
void Player::CreateAnimation()
{
	Animation* leftIdle = new Animation;
	leftIdle->SetStartEndFrame(0, 9, 9, 9, false);
	leftIdle->SetIsLoop(true);
	leftIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::LeftIdle, leftIdle));

	Animation* rightIdle = new Animation;
	rightIdle->SetStartEndFrame(0, 8, 9, 8, false);
	rightIdle->SetIsLoop(true);
	rightIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::RightIdle, rightIdle));

	Animation* upIdle = new Animation;
	upIdle->SetStartEndFrame(0, 10, 9, 10, false);
	upIdle->SetIsLoop(true);
	upIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::UpIdle, upIdle));

	Animation* downIdle = new Animation;
	downIdle->SetStartEndFrame(0, 11, 9, 11, false);
	downIdle->SetIsLoop(true);
	downIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::DownIdle, downIdle));

	Animation* leftRun = new Animation;
	leftRun->SetStartEndFrame(0, 3, 7, 3, false);
	leftRun->SetIsLoop(true);
	leftRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::LeftRun, leftRun));

	Animation* rightRun = new Animation;
	rightRun->SetStartEndFrame(0, 2, 7, 2, false);
	rightRun->SetIsLoop(true);
	rightRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::RightRun, rightRun));

	Animation* upRun = new Animation;
	upRun->SetStartEndFrame(0, 0, 7, 0, false);
	upRun->SetIsLoop(true);
	upRun->SetFrameUpdateTime(0.1f);
	_animationList.insert(make_pair(State::UpRun, upRun));

	Animation* downRun = new Animation;
	downRun->SetStartEndFrame(0, 1, 7, 1, false);
	downRun->SetIsLoop(true);
	downRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::DownRun, downRun));

	Animation* leftRoll = new Animation;
	leftRoll->SetStartEndFrame(0, 5, 7, 5, false);
	leftRoll->SetIsLoop(false);
	leftRoll->SetFrameUpdateTime(_frameRun);	
	leftRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	
	_animationList.insert(make_pair(State::LeftRoll, leftRoll));

	Animation* rightRoll = new Animation;
	rightRoll->SetStartEndFrame(0, 4, 7, 4, false);
	rightRoll->SetIsLoop(false);
	rightRoll->SetFrameUpdateTime(_frameRun);
	rightRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//���ٽ� �Լ� ȣ��
	_animationList.insert(make_pair(State::RightRoll, rightRoll));

	Animation* upRoll = new Animation;
	upRoll->SetStartEndFrame(0, 6, 7, 6, false);
	upRoll->SetIsLoop(false);
	upRoll->SetFrameUpdateTime(_frameRun);
	upRoll->SetCallbackFunc([this]() {this->EndAnimation(); });		//�������� �� ���� �����Ѵ�
	_animationList.insert(make_pair(State::UpRoll, upRoll));

	Animation* downRoll = new Animation;
	downRoll->SetStartEndFrame(0, 7, 7, 7, false);
	downRoll->SetIsLoop(false);
	downRoll->SetFrameUpdateTime(_frameRun);
	downRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//�� ����� public�� ����� �ָ� ������!
	_animationList.insert(make_pair(State::DownRoll, downRoll));
}


void Player::EndAnimation()
{
	switch (_state)
	{
	case Player::State::LeftIdle:
		break;
	case Player::State::RightIdle:
		break;
	case Player::State::UpIdle:
		break;
	case Player::State::DownIdle:
		break;
	case Player::State::LeftRun:
		break;
	case Player::State::RightRun:
		break;
	case Player::State::UpRun:
		break;
	case Player::State::DownRun:
		break;
	case Player::State::LeftRoll:
		this->ChangeState(State::LeftIdle);
		break;
	case Player::State::RightRoll:
		break;
	case Player::State::UpRoll:
		break;
	case Player::State::DownRoll:
		break;
	default:
		break;
	}
}

/********************************************************************************/
//## IdleKeyInut ##
//Idle ������ �� Ű �Է� ó��
/********************************************************************************/
void Player::IdleKeyInput()
{
	if (_Input->GetKeyDown('A'))
	{
		this->ChangeState(State::LeftRun);
	}
	else if (_Input->GetKeyDown('D'))
	{
		this->ChangeState(State::RightRun);
	}
	else if (_Input->GetKeyDown('W'))
	{
		this->ChangeState(State::UpRun);
	}
	else if (_Input->GetKeyDown('S'))
	{
		this->ChangeState(State::DownRun);
	}
}


