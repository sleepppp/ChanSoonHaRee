#include "stdafx.h"
#include "Player.h"
//#include "Image.h"
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

	this->_standRate = 0.5f;				//������ ��� �ð�
	this->_runRate = 0.082588f;				//�޸���� ������ �ð�
	this->_frameCount = 0.f;				//������Ÿ�̸Ӹ� ���� ����
	this->_changeIndexX = 0.f;				//�� X������ ������ �޶� ���氪�� ���� �ֱ� ���� ���� ����	
	this->_isRolling = false;				//������ ������ �Ǵ� bool��

	//ù �ൿ�� ���� �⺻��
	//this->_frameIndexX = 0.f;				//�����Ӱ���X
	//this->_frameIndexY = 11.f;				//11�� �⺻ ������ �ٶ󺸰� �ϱ� ���� ��(����)	
	//this->Move(StateMove::stand_D);			//���� ��� ���� (���麸��)		

	//�浹�������� �޾Ƽ� ����� ���� ������ �����Ұ�
	//������ ���� ��Ʈ(������� ��ġ�� ���� ������ ���� ������ ��)
	//_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);	//����� ��Ʈ ����
	//_shieldRc = RectMakeCenter(_position.x, _position.y, 100, 100); //���п� ��Ʈ ����		
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2); //�浹������ ��Ʈ ����
	//��Rc�� ȭ��Rc�� ���� ������, ��Ȳ�� ����� �������� ������ ����

	//�ִϸ��̼�Ŭ���� ���
	_animation = new Animation;
	_animation->SetStartEndFrame(0, 9, 10, 9, false);
	_animation->SetFrameUpdateTime(0.1f);
	_animation->SetIsLoop(true);
	_animation->Play();
}
Player::~Player() {}
void Player::Init() {}
void Player::Release() 
{
	SafeDelete(_image);
	SafeDelete(_animation);
}

void Player::Update()
{
	_animation->UpdateFrame();
	/*
	//�Ѹ� enum���� �����
	if (_Input->GetKeyDown(VK_SPACE))
	{
		_isRolling = true;	//�ٸ���Ǻ��� �켱�� �ϱ� ���� bool��
	}

	//_isRolling = false;

	if (_Input->GetKeyUp(VK_LEFT))
	{
		if (_isRolling)
		{
			this->Move(StateMove::roll_L);
		}
		if (!_isRolling)
		{
			this->Move(StateMove::stand_L);
			//_position.x -= _speed;
		}
	}
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
	//switch:����ó���� ok, �̵��� ���� no
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


	cout << _isRolling << endl;








	//this->RollTime(_stateAction);
	//����Ÿ���� �����ӽð��� �����ش�
	this->_frameCount += _TimeManager->DeltaTime();

	//������ī��Ʈ�� �ε��� ���徿 �÷���
	//!!!���ĵ巹��Ʈ�� �Ǿ����� ������ ��
	if (_frameCount >= _standRate)
	{
		this->_frameIndexX++;	//�������������� �̵�

		//1���� ���������� ���ǹ�
		//if (_isRolling == true && _frameCount == 6)
		//{
		//	_isRolling = false;
		//}
		
		//�����Ӱ��� Ŀ���� �Ѿ������ �ٽ� ���� ���ش�.
		while (_frameCount >= _standRate) this->_frameCount -= this->_standRate;

		//���� �������ε���X�� �ƽ��� ���ų� Ŀ���� 0���� �ʱ�ȭ
		if (this->_changeIndexX <= _frameIndexX) this->_frameIndexX = 0;

		
	}
	//this->UpdateMainRect();

	//�浹������Ʈ
	_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);
	//����� ��Ʈ ����(������� ��ġ�� ���� ������ ���� ������ ��)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);
*/
}
//�Ѹ����϶� _frameIndexX�� ���� �ٴٸ��� _isRolling true
void Player::Render()
{
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER);

	//�浹������Ʈ Ȯ�ο�(Ȯ���� ������ ��)
	//_DXRenderer->DrawRectangle(_colliRc, DefaultBrush::blue, false, 2.0f);
	//����� ��Ʈ Ȯ�ο�(Ȯ���� ������ ��)
	//_DXRenderer->DrawRectangle(_weaponRc, DefaultBrush::red, false, 2.0f);
}

//�߰��Լ�:�����¿�(���ĵ�, �޸���)
void Player::Move(StateMove _move)
{
	switch (_move)
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

	case StateMove::roll_L:
		//_position.x -= _speed * 2;
		//this->_frameIndexY = 5;
		//this->_changeIndexX = 7;
		//this->_standRate = 0.05f;
		_animation->UpdateFrame();
		//_animation->SetStartEndFrame(0, 5, 7, 5, false);
		break;

	case StateMove::roll_R:
		//_position.x += _speed * 2;
		this->_frameIndexY = 4;
		this->_changeIndexX = 7;
		this->_standRate = 0.05f;
		break;

	case StateMove::roll_U:
		//_position.y -= _speed * 2;
		this->_frameIndexY = 6;
		this->_changeIndexX = 7;
		this->_standRate = 0.05f;
		break;

	case StateMove::roll_D:
		this->_frameIndexY = 7;
		this->_changeIndexX = 7;
		this->_standRate = 0.05f;
		break;

	default:
		break;
	}
	
}

//�߰��Լ�:������ ���ǵ�(�����Ⱓ���� ��Ҿ��� ������ ����)
//void Player::RollTime(StateAction _roll)
//{
//	switch (_roll)
//	{
//	case StateAction::roll_L:
//		_position.x -= _speed * 2;
//		break;
//
//	case StateAction::roll_R:
//		_position.x += _speed * 2;
//		break;
//
//	case StateAction::roll_U:
//		_position.y -= _speed * 2;		
//		break;
//
//	case StateAction::roll_D:
//		_position.y += _speed * 2;
//		break;
//	case StateAction::end:
//		break;
//	default:
//		break;
//	}
//}
