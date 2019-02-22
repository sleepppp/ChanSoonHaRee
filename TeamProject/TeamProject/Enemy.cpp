#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(Vector2 position)
{
	this->_position = position;
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//ũ��
	this->_size = Vector2(50, 50);
	//��ǥ���� ��Ʈ ���� ���
	this->_pivot = Pivot::CENTER;
	//�ӵ�
	_speed = 300.0f;
	//�¿�Ȯ��
	_isLeft = false;
	//��Ʈ ����.

	this->UpdateRect();
}

void Enemy::Release()
{
}

void Enemy::Update()
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
	
	if(_isLeft == false)
	{
		_position.x -= _speed * _Time->DeltaTime();
		this->UpdateRect();
	}
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

