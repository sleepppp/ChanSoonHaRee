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
	
	this->_standRate = 0.5f;				//������ ��� �ð�
	this->_runRate = 0.082588f;				//�޸���� ������ �ð�
	this->_frameCount = 0.f;				//������Ÿ�̸Ӹ� ���� ����
	this->_changeIndexX = 0.f;				//�� X������ ������ �޶� ���氪�� ���� �ֱ� ���� ���� ����	
	this->_isRolling = false;				//������ ������ �Ǵ� bool��
	
	_rollCount = 0;							//
	_hp = 100;								//
	_demage = 10;							//

	//�ִϸ��̼�Ŭ���� ���
	_animation = new Animation;
	_animation->SetStartEndFrame(0, 9, 10, 9, false);
	_animation->SetFrameUpdateTime(0.1f);
	_animation->SetIsLoop(false);
	_animation->Play();

	//ù �ൿ�� ���� �⺻��
	this->_frameIndexX = 0.f;				//�����Ӱ���X
	this->_frameIndexY = 11.f;				//11�� �⺻ ������ �ٶ󺸰� �ϱ� ���� ��(����)	
	this->Move(StateMove::stand_D);			//���� ��� ���� (���麸��)		
	this ->_rate = _standRate;

	//�浹�������� �޾Ƽ� ����� ���� ������ �����Ұ�
	//������ ���� ��Ʈ(������� ��ġ�� ���� ������ ���� ������ ��)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);	//����� ��Ʈ ����
	//_shieldRc = RectMakeCenter(_position.x, _position.y, 100, 100); //���п� ��Ʈ ����		
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2); //�浹������ ��Ʈ ����
	//��Rc�� ȭ��Rc�� ���� ������, ��Ȳ�� ����� �������� ������ ����
	//���� �浹�� ��Ʈ ��ġ �ʱ�ȭd
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
	
	//�̵��� ������ ����
	Vector2 moveValue(0, 0);

	//��������
	if (_Input->GetKeyDown(VK_SPACE))	
	{		
		_isRolling = true;
	}

	//������:���ǽ���
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

	//������:�Ϸ� �� ���ĵ� �������� ���ư���
	if (!_isRolling)
	{				
		this->DefaultMove(); //�⺻����
		if (_stateMove == StateMove::roll_L) this->DefaultMove();	
		if (_stateMove == StateMove::roll_R) this->DefaultMove();
		if (_stateMove == StateMove::roll_U) this->DefaultMove();
		if (_stateMove == StateMove::roll_D) this->DefaultMove();			
	}	
		
	//�ӵ���
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


	//�ִϸ��̼� ����	
	this->_frameCount += _TimeManager->DeltaTime();		//����Ÿ���� �����ӽð��� �����ش�

	//��� �����ð� rate���� ���� Ŀ���� �������� �ѱ��
	if (_frameCount >= _rate)
	{
		this->_frameIndexX++;	//�������������� �̵�
		
		if (_isRolling)
		{
			_rollCount++;
		}
		//�����Ӱ��� Ŀ���� �Ѿ������ �ٽ� ���� ���ش�.
		while (_frameCount >= _rate) this->_frameCount -= this->_rate;
		
		//���� �������ε���X�� �ƽ��� ���ų� Ŀ���� 0���� �ʱ�ȭ
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

	//�浹������Ʈ
	//_colliRc = RectMakeCenter(_position.x, _position.y, _size.x / 2, _size.y / 2);
	//����� ��Ʈ ����(������� ��ġ�� ���� ������ ���� ������ ��)
	_weaponRc = RectMakeCenter(_position.x, _position.y, 100, 100);
	
}

void Player::Render()
{	
	_image->SetSize(_size);
	_image->FrameRender(_position.x, _position.y, _frameIndexX, _frameIndexY, Pivot::CENTER);
	
	//�浹������Ʈ Ȯ�ο�(Ȯ���� ������ ��)
	//_DXRenderer->DrawRectangle(_colliRc, DefaultBrush::blue, false, 2.0f);
	//����� ��Ʈ Ȯ�ο�(Ȯ���� ������ ��)
	_DXRenderer->DrawRectangle(_weaponRc, DefaultBrush::red, false, 2.0f);
}



//�߰��Լ�:�����¿�(���ĵ�, �޸���)
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


//���� �ѱ��
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