#include "stdafx.h"
#include "Player.h"

/*****************************************
����: ����: _player , bool��: _isActive
����: ����: player, bool��: isActive
���� ��(�Լ�, Ŭ����): Player
*****************************************/

//�÷��̾�: ������, ��ȣ����...��... �浹...ó��...

Player::Player()
{
	_speed = 0;
	_name = "�÷��̾�";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;

	this->UpdateRect();		//rc �ʱ�ȭ
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
	//�̵�:��
	if (_Input->GetKey('A'))
	{
		// �׳� ��ǥ �����ΰ� ������ ����� SetPosition(Vector2(-200.f, 0.f));
		_position.x -= 200.f * _Time->DeltaTime();
		this->UpdateRect();
	}
	//�̵�:��
	if (_Input->GetKey('D'))
	{
		_position.x += 200.f * _Time->DeltaTime();
		this->UpdateRect();
	}

	//�׼�:�Ѿ˹߻�
	if (_Input->GetKey(VK_SPACE))
	{

		this->UpdateRect();
	}
}

void Player::Render()
{

}


//�÷��̾� �Ѿ� �߻�
void BulletFire()
{

}

//�÷��̾� �Ѿ� �̵�
void BulletMove()
{

}

//�÷��̾�� ���ʹ� �Ѿ� �浹�� ���