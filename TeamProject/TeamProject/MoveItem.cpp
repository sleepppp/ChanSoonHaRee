#include "stdafx.h"
#include "MoveItem.h"
#include "UIWeaponAndBag.h"
#include "Inventory.h"
#include "Player.h"
MoveItem::MoveItem(string name, Vector2 position)
{
	_name = name;
	_position = position;

	_itemBrenchImg = _ImageManager->FindImage("item_brench");
	_pivot = Pivot::LEFT_TOP;
	_size = Vector2(50, 50);
	_mainRect = Figure::RectMake(_position.x, _position.y, _size.x, _size.y);

	_angle = 0.f;		//������ ��鸲�� ���� �ޱ� ����
	_speed = 1.5f;		//������ ��鸲 �ӵ��� ���� �ӵ� ����

	_itemState = ItemState::Follow;

	_moveCount = 0;
}


MoveItem::~MoveItem()
{

}

void MoveItem::Init()
{
	
}

void MoveItem::Release()
{
}

void MoveItem::Update()
{
	GameObject* _player = _ObjectManager->FindObject(ObjectType::Object,"Will");

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

			//���� �Ÿ��� 250���� �־�����
			//������ �յ� �߰��ϱ�
			if (250 < distance)
			{
				_angle += 0.05f;
				if (_angle >= Math::PI * 2.0f)
					_angle -= Math::PI * 2.0f;

				_position.y += sinf(_angle) * 20.0f * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}

			//���� �Ÿ��� 250���� ���� 150���� ������
			else if (250 > distance && distance > 150)
			{
				float speed = 20.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
			//���� �Ÿ��� 150�̶� ���ų� ��������
			else if (distance <= 150)
			{
				float speed = 150.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
			//���� �Ÿ��� 10���� ��������
			if (distance <= 10)
			{
				//������ �̵� ���� ����
				_itemState = ItemState::MoveItem;
			}
		}
	}

	//������ ���°� ������ �̵� �����̸�
	else if (_itemState == ItemState::MoveItem) 
	{
		GameObject* _moveItem = _ObjectManager->FindObject(ObjectType::UI, "UIWeaponAndBag");
		//���� ������(_moveItem)�� ������ 
		if (_moveItem)
		{
			Vector2 moveItemPos(_moveItem->GetMainRect().left, _moveItem->GetMainRect().top);
			moveItemPos = _Camera->GetWorldVector2(moveItemPos);
			//�Ÿ� ���ϱ�
			float distanceItemBag = Math::GetDistance(_position.x, _position.y, moveItemPos.x, moveItemPos.y);

			//���� ���ϱ�
			float angleItemBag = Math::GetAngle(_position.x, _position.y, moveItemPos.x, moveItemPos.y);

			//������ �̵� �ӵ�
			float moveItemSpd = 950.0f;

			//���� ������ ������ �ӵ��� �������� �̵���Ű��
			this->_position.x += cosf(angleItemBag) * moveItemSpd * _TimeManager->DeltaTime();
			this->_position.y -= sinf(angleItemBag) * moveItemSpd * _TimeManager->DeltaTime();
			this->UpdateMainRect();

			if (distanceItemBag <= 20)
			{
				//������ ���´� �κ� ���·� ��ȯ
				_itemState = ItemState::Inven;
			}
		}
	}

	//������ ���°� �κ��̸� 
	else if (_itemState == ItemState::Inven)
	{
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

}

void MoveItem::Render()
{
	_itemBrenchImg->Render(_position.x, _position.y, Pivot::LEFT_TOP, true);
	if (_isDebug)
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
	//��Ʈ ���� ���Ű
	//if (_Input->IsToggleKey(VK_F10)) 
	//{
	//	_DXRenderer->FillRectangle(this->_mainRect, DefaultBrush::yello, false);
	//}

	if (_isDebug)
	{
		ImGui::Begin("Chan");
		ImGui::Text("X : %d , Y : %d", (int)_Input->GetMousePosition().x,(int) _Input->GetMousePosition().y);
		ImGui::End();
	}
}
