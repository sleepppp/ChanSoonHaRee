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
	this->_pivot = Pivot::LEFT_TOP;
	this->_position = Vector2(WinSizeX / 1.2f, WinSizeY / 5.0f);
	this->_size = Vector2(50, 50);
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _size.x, _size.y);

	_angle = 0.f;		//아이템 흔들림을 위한 앵글 변수
	_speed = 1.5f;	//아이템 흔들림 속도를 위한 속도 변수

	_itemState = ItemState::Follow;

	_moveCount = 0;
}

void MoveItem::Release()
{
	//_itemBrenchImg->Release();
	//SafeDelete(_itemBrenchImg);
}

void MoveItem::Update()
{
	GameObject* _player = _ObjectManager->FindObject(ObjectType::Object,"Will");

	//상태가 따라가기 상태이면
	if (_itemState == ItemState::Follow)
	{
		//만일 _player가 있으면
		if (_player)
		{
			//거리 구하기
			float distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

			//상대 각도 구하기
			float angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

			//둥둥 뜨게하기
			if (250 < distance)
			{
				_angle += 0.05f;
				if (_angle >= Math::PI * 2.f)
					_angle -= Math::PI * 2.f;

				_position.y += sinf(_angle) * 50.0f * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}

			//만일 거리가 250보다 낮고 50보다 높으면
			else if (250 > distance && distance > 150)
			{
				float speed = 20.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
			//만일 거리가 50이랑 같거나 낮아지면
			else if (distance <= 150)
			{
				float speed = 150.0f;
				this->_position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
				this->_position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
				this->UpdateMainRect();
			}
			else if (distance <= 30)
			{
				//아이템 상태는 인벤 상태로 변환
				_itemState = ItemState::Inven;
			}
		}

	}

	//아이템 상태가 인벤이면 
	else if (_itemState == ItemState::Inven)
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

void MoveItem::Render()
{
	_itemBrenchImg->Render(_position.x, _position.y, Pivot::LEFT_TOP, true);
	if (_isDebug)
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
	//렉트 렌더 토글키
	//if (_Input->IsToggleKey(VK_F10)) 
	//{
	//	_DXRenderer->FillRectangle(this->_mainRect, DefaultBrush::yello, false);
	//}
}
