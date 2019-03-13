#include "stdafx.h"
#include "Inventory.h"
#include "Player.h"
#include "StringHelper.h"
#include "Image.h"
#include "MoveItem.h"

//
void Inventory::SprayItemPlayer()
{
	//만일 플레이어 HP가 0보다 같거나 낮아지면
	if (_player->GetPlayerCurrentHp() <= 0) 
	{
		//플레이어 포인터 플레이어에 다운캐스팅 적용해서 클래스 가져오기
		Player* player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

		//가방 슬롯 사이즈만큼
		for (UINT i = 0; i < _bagSlotList.size(); ++i)
		{
			//가방 슬롯이 비어있지 않으면
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