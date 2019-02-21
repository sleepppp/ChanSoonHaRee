#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	speed = 100.0f;
}


Player::~Player()
{
}

void Player::Init()
{
	this->name = "Player";
	this->position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->size = Vector2(50, 50);
	this->pivot = Pivot::CENTER;
	this->UpdateRect();
}

void Player::Release()
{
}

void Player::Update()
{
	if (_Input->GetKey('A'))
	{
		this->Move(Vector2(-speed, 0.f));
	}
	if (_Input->GetKey('D'))
	{
		this->Move(Vector2(speed, 0.f));
	}

	GameObject* enemy = _ObjectManager->FindObject("Enemy");
	if (enemy != nullptr)
	{
		RECT temp;
		if (IntersectRect(&temp, &enemy->GetRect(), &this->rc))
		{
			enemy->SetIsLive(false);
		}
	}
}

void Player::Render()
{
	_DXRenderer->DrawRectangle(rc, DefaultBrush::blue, true);
}

void Player::Move(Vector2 moveValue)
{
	this->position += moveValue * _Time->DeltaTime();
	this->UpdateRect();
}
