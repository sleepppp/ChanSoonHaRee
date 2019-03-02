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

	this->_frameCount = 0.f;		//������Ÿ�̸Ӹ� ���� ����

	this->_standRate = 0.5f;		//������ ��� �ð�
	this->_runRate = 0.082588f;		//�޸���� ������ �ð�
	this->_changeIndexX = 0.f;		//�� X������ ������ �޶� ���氪�� ���� �ֱ� ���� ���� ����	
	_ImageManager->AddFrameImage("Will", L"../Resources/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");

	//ù �ൿ�� ���� �⺻��

	this->_frameIndexX = 0.f;		//�����Ӱ���X
	this->_frameIndexY = 11.f;		//11�� �⺻ ������ �ٶ󺸰� �ϱ� ���� ��(����)	
	this->_state = State::stand_D;	//���� ��� ���� 	



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
	//�Ѹ��Ѹ�
	if (_Input->GetKey(VK_SPACE))
	{
		this->_state = State::end;	//�켱���� ���� enum���� ���� ���ش�
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

	//�Ѹ��� �켱���ϱ� ���� ����
	if (!_isRolling)
	{
		if (_Input->GetKeyUp(VK_LEFT))		_state = State::stand_L;
		if (_Input->GetKeyUp(VK_RIGHT))		_state = State::stand_R;
		if (_Input->GetKeyUp(VK_UP))		_state = State::stand_U;
		if (_Input->GetKeyUp(VK_DOWN))		_state = State::stand_D;

		//switch:����ó���� ok, �̵��� ���� no
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


	//����Ÿ���� �����ӽð��� �����ش�
	this->_frameCount += _TimeManager->DeltaTime();

	//������ī��Ʈ�� �ε��� ���徿 �÷���
	if (_frameCount >= _standRate)
	{
		this->_frameIndexX++;	//�������������� �̵�

		//�����Ӱ��� Ŀ���� �Ѿ������ �ٽ� ���� ���ش�.
		while (_frameCount >= _standRate) this->_frameCount -= this->_standRate;

		//���� �������ε���X�� �ƽ��� ���ų� Ŀ���� 0���� �ʱ�ȭ
		if (this->_changeIndexX <= _frameIndexX) this->_frameIndexX = 0;
	}
}

void Player::Render()
{
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER, true);
}