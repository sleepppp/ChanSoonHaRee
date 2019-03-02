#include "stdafx.h"
#include "Item.h"

#include "Inventory.h"
Item::Item()
{

}


Item::~Item()
{

}

void Item::Update()
{
	//���� �浹ó���Ǹ鼭 bool���� true�� �Ǹ�
	if (true)
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
