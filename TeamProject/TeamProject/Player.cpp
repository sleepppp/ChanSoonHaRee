#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"		//�Ѿ�
#include "Enemy.h"

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
<<<<<<< HEAD
=======
	_bullet = new Bullet;
	_bullet->Init(10,WinSizeY);

>>>>>>> 69be1a8655bf950fb8e0229bd58b58aec27bf7af
	_speed = 200.0f;
	_name = "�÷��̾�";
	_position.x = WinSizeX / 2;
	_position.y = WinSizeY - 100;
	_size.x = 24;
	_size.y = 48;
	_pivot = Pivot::CENTER;
	this->UpdateRect();		//rc �ʱ�ȭ

	//bullet��
	_bullet = new Bullet;
	_bullet->Init(10, 500);

	_playerBullet.x = 40;		//�÷��̾ ��� �Ѿ��� ������
	_playerBullet.y = 40;	
}

void Player::Release()
{
	_bullet->Release();
	SafeDelete(_bullet);
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
	if (_Input->GetKeyDown(VK_SPACE))
	{
		_bullet->Fire(Vector2(_position), Vector2(_playerBullet), Math::PI/2, 200.f);				
		this->UpdateRect();			
	}

	_bullet->Update();
}

void Player::Render()
{
	this->UpdateRect();
	_DXRenderer->FillRectangle(_rc, DefaultBrush::blue, true);	
	
	_bullet->Render();
	
}

void Player::Collision()
{
	//_enemy�� ã���ϴ�.
	GameObject* _enemy = _ObjectManager->FindObject("_enemy");	

	//���ϰ��� nullptr�� �ƴ� ���
	if (_enemy!=nullptr)
	{
		//�÷��̾� �Ѿ˰� ���ʹ� ��ü�� �浹�� ���
		if (_bullet->Intersect(_enemy->GetRect()))
		{
			//
			_enemy->SetIsLive(false);
		}
	}
	
}