#include "stdafx.h"
#include "Inventory.h"
#include "Player.h"
#include "StringHelper.h"
#include "Image.h"
#include "MoveItem.h"

//
void Inventory::SprayItemPlayer()
{
	//���� �÷��̾� HP�� 0���� ���ų� ��������
	if (_player->GetPlayerCurrentHp() <= 0) 
	{
		//�÷��̾� ������ �÷��̾ �ٿ�ĳ���� �����ؼ� Ŭ���� ��������
		Player* player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

		//���� ���� �����ŭ
		for (UINT i = 0; i < _bagSlotList.size(); ++i)
		{
			//���� ������ ������� ������
			if (_bagSlotList[i]->isEmpty == false)
			{
				for (UINT i = 0; i < _bagSlotList[i]->itemCount; ++i)
				{
					Vector2 randomPos;
					randomPos.x = Math::Random(player->GetPosition().x - 50.f, player->GetPosition().x + 50.f);
					randomPos.y = Math::Random(player->GetPosition().y - 50.f, player->GetPosition().y + 50.f);
					MoveItem* item = new MoveItem(_bagSlotList[i]->data.image->GetKey(), randomPos);
					_ObjectManager->AddObject(ObjectType::Object, item);
				}
				_bagSlotList[i]->itemCount = 0;
				_bagSlotList[i]->isEmpty = true;
			}
		}
	}
}