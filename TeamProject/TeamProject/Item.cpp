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
	//만일 충돌처리되면서 bool값이 true가 되면
	if (true)
	{
		//Inventory* inven(인벤토리 포인터) dynamic_cast(다이나믹 캐스트) 다운 캐스팅으로 형변환해서 인벤토리에 접근한 뒤 
		//만일 인벤이 nullptr이 아니면 인벤에 addItem으로 이름을 받아 true이면  아이템을 파괴 --> 즉, 아이템 안 보이게 하기
		//난 캐릭터 충돌하고 아이템 인벤 ui에 이동되면 파괴하기
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
