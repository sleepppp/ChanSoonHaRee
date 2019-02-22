#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"		//�Ѿ�

/*****************************************
����: ����: _player , bool��: _isActive
����: ����: player, bool��: isActive
���� ��(�Լ�, Ŭ����): Player
*****************************************/
//�÷��̾�: ������, ��ȣ����...��... �浹...ó��...

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	_speed = 200.0f;
	_name = "�÷��̾�";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;

	this->UpdateRect();		//rc �ʱ�ȭ
}

void Player::Release()
{
}

void Player::Update()
{
	//�̵�:��
	if (_Input->GetKey('A'))
	{
		// �׳� ��ǥ �����ΰ� ������ ����� SetPosition(Vector2(-200.f, 0.f));
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
	//�̵�:��
	if (_Input->GetKey('D'))
	{
		_position.x += _speed * _Time->DeltaTime();
		this->UpdateRect();
	}

	//�׼�:�Ѿ˹߻�
	if (_Input->GetKey(VK_SPACE))
	{
		this->BulletFire();		//�Ѿ� ���� �� �߻�
		this->UpdateRect();		
	}
}

void Player::Render()
{
	this->UpdateRect();
	_DXRenderer->FillRectangle(_rc, DefaultBrush::blue, true);	
}

//�÷��̾� �Ѿ� �߻�
void Player::BulletFire()
{
	//�ҷ�Ŭ������ ���Ϳ� ��Ƽ�...�׷��ְ� �Ұ� ������ �߰��ϰ�
	
	//�Ѿ� ���� 10��
	//�߻��� ��� bool������ false�� continue, true�� ����;
	
	//�߻��� ��� bool�� false�� ����
	//rc�׸���

	//Vector
}