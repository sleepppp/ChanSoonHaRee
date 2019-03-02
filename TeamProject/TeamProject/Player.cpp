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
	

	this->_pivot = Pivot::CENTER;
	this->UpdateMainRect();
	this->_speed = 0.5f;

	this->_frameCount = 0.f;		//������Ÿ�̸Ӹ� ���� ����

	this->_standRate = 0.5f;		//������ ��� �ð�
	this->_runRate = 0.082588f;		//�޸���� ������ �ð�
	this->_changeIndexX = 0.f;		//�� X������ ������ �޶� ���氪�� ���� �ֱ� ���� ���� ����	
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_image = _ImageManager->FindImage("Will");

	//ù �ൿ�� ���� �⺻��
	this->_frameIndexX = 0.f;		//�����Ӱ���X
	this->_frameIndexY = 11.f;		//11�� �⺻ ������ �ٶ󺸰� �ϱ� ���� ��(����)	
	this->_stateMove = StateMove::stand_D;	//���� ��� ���� 	
	this->_isRolling = false;

	//�浹������ ��Ʈ ����
	_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);

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
	//if (_Input->GetKey(VK_SPACE))
	//{
	//	this->_stateMove = StateMove::end;	//�켱���� ���� enum���� ���� ���ش�
	//	_isRolling = true;
	//
	//	//������ ���õ� ��� �ൿ�� �� ���¿����� ���ʸ��+�̵�
	//	if (_Input->GetKeyUp(VK_LEFT) || _Input->GetKey(VK_LEFT))
	//	{
	//		_position.x -= _speed * 2;
	//		//this->rolling = true;	
	//		this->_frameIndexY = 5;
	//		this->_changeIndexX = 7;
	//		this->_standRate = 0.05f;
	//	}
	//}

	//�Ѹ� enum���� �����
	if (_Input->GetKey(VK_SPACE))
	{
		_isRolling = true;	//�ٸ���Ǻ��� �켱�� �ϱ� ���� bool��

		//LeftŰ ���� ���¸�
		if (_stateMove==StateMove::stand_L|| _stateMove == StateMove::run_L)
		{
			_stateAction = StateAction::roll_L;
			_position.x -= _speed * 2;
			//this->rolling = true;	
			this->_frameIndexY = 5;
			this->_changeIndexX = 7;
			this->_standRate = 0.05f;
		}

		if (_stateMove == StateMove::stand_R || _stateMove == StateMove::run_R)
		{
			_stateAction = StateAction::roll_R;
			_position.x += _speed * 2;
			this->_frameIndexY = 4;
			this->_changeIndexX = 7;
			this->_standRate = 0.05f;
		}

		if (_stateMove == StateMove::stand_U || _stateMove == StateMove::run_U)
		{
			_stateAction = StateAction::roll_U;
			_position.y -= _speed * 2;
			this->_frameIndexY = 6;
			this->_changeIndexX = 7;
			this->_standRate = 0.05f;
		}

		if (_stateMove == StateMove::stand_D || _stateMove == StateMove::run_D)
		{
			_stateAction = StateAction::roll_D;
			_position.y += _speed * 2;
			this->_frameIndexY = 7;
			this->_changeIndexX = 7;
			this->_standRate = 0.05f;
		}
	}



	//�Ѹ��� �켱���ϱ� ���� ����
	if (!_isRolling)
	{
		if (_Input->GetKeyUp(VK_LEFT))		_stateMove = StateMove::stand_L;
		if (_Input->GetKeyUp(VK_RIGHT))		_stateMove = StateMove::stand_R;
		if (_Input->GetKeyUp(VK_UP))		_stateMove = StateMove::stand_U;
		if (_Input->GetKeyUp(VK_DOWN))		_stateMove = StateMove::stand_D;

		//switch:����ó���� ok, �̵��� ���� no
		if (_Input->GetKey(VK_LEFT))
		{
			_stateMove = StateMove::run_L;
			_position.x -= _speed;
		}
		if (_Input->GetKey(VK_RIGHT))
		{
			_stateMove = StateMove::run_R;
			_position.x += _speed;
			//cout << "asd" << endl;
		}
		if (_Input->GetKey(VK_UP))
		{
			_stateMove = StateMove::run_U;
			_position.y -= _speed;
		}
		if (_Input->GetKey(VK_DOWN))
		{
			_stateMove = StateMove::run_D;
			_position.y += _speed;
		}

		//���°� ����
		this->State(_stateMove);
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

		//1���� ���������� ���ǹ�
		if (_isRolling && this->_frameIndexX == 6)
		{
			_isRolling = false;
			//if()
		}
	}		

	//�浹������Ʈ
	_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);
}

void Player::Render()
{
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER, true);
	
	//�浹������Ʈ Ȯ�ο�(Ȯ���� ������ ��)
	_DXRenderer->DrawRectangle(_colliRc, DefaultBrush::blue, false, 2.0f);
}





void Player::State(StateMove _state)
{
	switch (_state)
	{
	case StateMove::stand_L:
		this->_frameIndexY = 9;
		this->_changeIndexX = 10;
		this->_standRate = 0.4f;

		break;

	case StateMove::stand_R:
		this->_frameIndexY = 8;
		this->_changeIndexX = 10;
		this->_standRate = 0.4f;
		break;

	case StateMove::stand_U:
		this->_frameIndexY = 10;
		this->_changeIndexX = 10;
		this->_standRate = 0.4f;
		break;

	case StateMove::stand_D:
		this->_frameIndexY = 11;
		this->_changeIndexX = 10;
		this->_standRate = 0.4f;
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

	default:
		break;
	}
}
