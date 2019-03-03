#include "stdafx.h"
#include "MoveItem.h"

#include "Inventory.h"
#include "Player.h"
MoveItem::MoveItem()
{

}


MoveItem::~MoveItem()
{

}

void MoveItem::Init()
{
	this->_name = "item_brench";
	_itemBrenchImg = _ImageManager->AddImage("brench1", L"../Resources/Object/item_brench.png",false);
	this->_pivot = Pivot::CENTER;
	this->_position = Vector2(WinSizeX / 1.2f, WinSizeY / 5.0f);
	this->_size = Vector2(50, 50);
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _size.x, _size.y);

	_angle = 0;		//������ ��鸲�� ���� �ޱ� ����
	_speed = 1.5f;	//������ ��鸲 �ӵ��� ���� �ӵ� ����

	_itemState = ItemState::Follow;

	_moveCount = 0;
}

void MoveItem::Release()
{
	_itemBrenchImg->Release();
	SafeDelete(_itemBrenchImg);
}

void MoveItem::Update()
{
	GameObject* _player = _ObjectManager->FindObject(ObjectType::Object,"Will");

	//������ ī��Ʈ ����
	_moveCount++;
	_angle += 50;

	if (_moveCount > 0 && _moveCount < 50)
	{
		//_position.y += sinf(_angle) * _speed * _TimeManager->DeltaTime();
		_mainRect.bottom += 1;
		_mainRect.top += 1;
	}
	if (_moveCount >= 50 && _moveCount < 100)
	{
		//_position.y += sinf(_angle) * _speed * _TimeManager->DeltaTime();
		_mainRect.bottom -= 1;
		_mainRect.top -= 1;
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
	else if (IntersectRect(&temp, &_mainRect, &_player->GetMainRect()))
	{
		//������ ���´� �κ� ���·� ��ȯ
		_itemState = ItemState::Inven;

		//Inventory* inven(�κ��丮 ������) dynamic_cast(���̳��� ĳ��Ʈ) �ٿ� ĳ�������� ����ȯ�ؼ� �κ��丮�� ������ �� 
		//���� �κ��� nullptr�� �ƴϸ� �κ��� addItem���� �̸��� �޾� true�̸�  �������� �ı� --> ��, ������ �� ���̰� �ϱ�
		//�� ĳ���� �浹�ϰ� ������ �κ� ui�� �̵��Ǹ� �ı��ϱ�
		Inventory* inven = dynamic_cast<Inventory*>(_ObjectManager->FindObject(ObjectType::UI, "Inventory"));
		if (inven != nullptr)
		{
			if (inven->AddItem(this->_name) == true)
			{
				this->Destroy();
			}
		}
	}

	//������ ���°� �κ��̸� 
	if (_itemState == ItemState::Inven)
	{

	}

	//���� �浹ó���Ǹ鼭 bool���� true�� �Ǹ�
	//if (true)
	//{
	//
	//}
}

void MoveItem::Render()
{
	_itemBrenchImg->Render(_position.x, _position.y, Pivot::LEFT_TOP, false);

	//��Ʈ ���� ���Ű
	if (_Input->IsToggleKey(VK_F10)) 
	{
		_DXRenderer->FillRectangle(this->_mainRect, DefaultBrush::yello, false);
	}
}