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


	_angle = 0;						//아이템 흔들림을 위한 앵글 변수
	_speed = 1.5f;					//아이템 흔들림 속도를 위한 속도 변수

	_itemState = ItemState::Follow;	//기본 상태는 캐릭터를 따라가기

	_moveCount = 0;

	this->UpdateMainRect();
}

void Item::Release()
{
}

void Item::Update()
{
	//GameObject* _player = _ObjectManager->FindObject("");


	//움직임 카운트 증가
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


			}

			//만일 거리가 250보다 낮고 50보다 높으면
			if (250 > distance && distance > 150)
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
		}
	}
	//만일 아이템 렉트와 플레이어 렉트와 충돌하면
	else if (IntersectRect(&temp, &_mainRect, &_player->GetRect()))
	{
		//아이템 상태는 인벤 상태로 변환
		_itemState = ItemState::MoveInven;
	}

	//아이템 상태가 인벤이면 상점
	if (_itemState == ItemState::MoveInven)
	{

	}

}

void Item::Render()
{
	_DXRenderer->FillRectangle(this->_mainRect, DefaultBrush::yello, false);
}
