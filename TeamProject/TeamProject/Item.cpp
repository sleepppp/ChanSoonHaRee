#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::Init()
{
	this->_name = "testItem";
	this->_pivot = Pivot::CENTER;
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_size = Vector2(50, 50);
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _size.x, _size.y);


	_angle = 0;						//������ ��鸲�� ���� �ޱ� ����
	_speed = 1.5f;					//������ ��鸲 �ӵ��� ���� �ӵ� ����

	_itemState = ItemState::Follow;	//�⺻ ���´� ĳ���͸� ���󰡱�

	_moveCount = 0;

	this->UpdateMainRect();
}

void Item::Release()
{
}

void Item::Update()
{
	//GameObject* _player = _ObjectManager->FindObject("");


	//������ ī��Ʈ ����
	_moveCount++;
	_angle += 50;

	if (_moveCount > 0 && _moveCount < 50)
	{
		_position.y += sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//_rc.bottom += 1;
		//_rc.top += 1;
	}
	if (_moveCount >= 50 && _moveCount < 100)
	{
		_position.y += sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//_rc.bottom -= 1;
		//_rc.top -= 1;
	}
	if (_moveCount >= 100)
	{
		_moveCount = 0;
	}

	RECT temp;
	//���°� ���󰡱� �����̸�
	if (_itemState == ItemState::Follow)
	{
		//���� _player�� ������
		if (_player)
		{
			//�Ÿ� ���ϱ�
			float distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

			//��� ���� ���ϱ�
			float angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

			//�յ� �߰��ϱ�
			if (250 < distance)
			{


			}

			//���� �Ÿ��� 250���� ���� 50���� ������
			if (250 > distance && distance > 150)
			{
				float speed = 20.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
			//���� �Ÿ��� 50�̶� ���ų� ��������
			else if (distance <= 150)
			{
				float speed = 150.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
		}
	}
	//���� ������ ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ�
	else if (IntersectRect(&temp, &_mainRect, &_player->GetRect()))
	{
		//������ ���´� �κ� ���·� ��ȯ
		_itemState = ItemState::MoveInven;
	}

	//������ ���°� �κ��̸� ����
	if (_itemState == ItemState::MoveInven)
	{

	}

}

void Item::Render()
{
	_DXRenderer->FillRectangle(this->_mainRect, DefaultBrush::yello, false);
}
