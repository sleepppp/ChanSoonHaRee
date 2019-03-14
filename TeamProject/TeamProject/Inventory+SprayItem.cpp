#include "stdafx.h"
#include "Inventory.h"
#include "Player.h"
#include "StringHelper.h"
#include "Image.h"
#include "MoveItem.h"
#include "Plankton.h"

//�÷��̾� ��� �� ������ �Ѹ��� �Լ�
void Inventory::SprayItemPlayer()
{
	//�÷��̾� ������ �÷��̾ �ٿ�ĳ���� �����ؼ� Ŭ���� ��������
	Player* player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

	//���� ���� �����ŭ
	for (UINT i = 0; i < _bagSlotList.size(); ++i)
	{
		//���� ������ ������� ������
		if (_bagSlotList[i]->itemCount > 0)
		{
			//������ ī��Ʈ üũ
			for (UINT i = 0; i < _bagSlotList[i]->itemCount; ++i)
			{
				//���� ������ ��ǥ�� ���� ���� ����
				Vector2 randomPos;
				//���� ��ǥ X -100 ~ +100
				randomPos.x = Math::Random(player->GetPosition().x - 100.f, player->GetPosition().x + 100.f);
				//���� ��ǥ Y -100 ~ +100
				randomPos.y = Math::Random(player->GetPosition().y - 100.f, player->GetPosition().y + 100.f);
				//���� ������ Ŭ���� NEW ���� (���� ���� ����Ʈ�� �̹��� Ű ��, ���� ������ ��ǥ)
				MoveItem* item = new MoveItem(_bagSlotList[i]->data.image->GetKey(), randomPos);
				//������Ʈ �߰� (Ÿ�� : ������Ʈ, ���ӿ�����Ʈ : ���� ������ Ŭ����)
				_ObjectManager->AddObject(ObjectType::Object, item);
			}
			//������ ���� 0���� �����
			_bagSlotList[i]->itemCount = 0;
		}
	}
}
