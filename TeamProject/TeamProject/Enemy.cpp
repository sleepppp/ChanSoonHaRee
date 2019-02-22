#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(Vector2 position)
{
	this->_position = position;
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	_name = "enemy";
	this->EnemyInit();
	_player =(Player*) _ObjectManager->FindObject("player");
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	_player = (Player*) _ObjectManager->FindObject("player");
	this->_count++;
	this->EnemyMove();
	this->EnemyFire();
}

void Enemy::Render()
{
	_DXRenderer->DrawRectangle(_rc, DefaultBrush::green);
	//â ����(�̸��� EnemySpeed)
	//ImGui::Begin("EnemySpeed");
	//{
	//	//�����̴� �÷��� ����� 
	//	//@@ �̸� ,�ٲ� float�ּ�,�ּҰ�,�ִ밪
	//	ImGui::SliderFloat("Speed", &_speed, 0.f, 300.0f);
	//}
	////â�� ������� 
	//ImGui::End();
}

//���ʹ��� init�� �����Ѵ�.
void Enemy::EnemyInit()
{
	//ī��Ʈ �ʱ�ȭ
	_count = 0;
	//ũ��
	this->_size = Vector2(50, 50);
	//��ǥ���� ��Ʈ ���� ���
	this->_pivot = Pivot::CENTER;
	//�ӵ�
	_speed = 300.0f;
	//�¿�Ȯ��
	_isLeft = false;
	//�ޱ۰� �ʱ�ȭ
	_angle = 0.f;
	//��Ʈ ����.
	_bullet = new Bullet;
	_bullet->Init(300, 700);
	this->UpdateRect();
}
//���ʹ��� �������� �����Ѵ�.
void Enemy::EnemyMove()
{
	if (_rc.right > WinSizeX)
	{
		_isLeft = false;
	}

	if (_rc.left < 0)
	{
		_isLeft = true;
	}

	if (_isLeft == true)
	{
		_position.x += _speed * _Time->DeltaTime();
		this->UpdateRect();
	}

	if (_isLeft == false)
	{
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
}
//���ʹ��� �Ѿ��� �߻��ϴ� ���θ� Ȯ���ϰ� �÷��̾ Ÿ������ �Ѿ��� �߻��Ѵ�.
void Enemy::EnemyFire()
{
	if (_count % 100 == 0)
	{
		_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		_bullet->Fire(Vector2(_position.x, _position.y), Vector2(10, 10), _angle, 60.0f);
		this->UpdateRect();
	}
}

